#include "engine.h"

/*****************************************************
 * ENUMERATIONS
 *****************************************************/

/*****************************************************
 * TYPE DECLARATIONS
 *****************************************************/

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

SORBET_T* sorbet__create()
{
	SORBET_T* sorbet = malloc(sizeof(SORBET_T));
	if(!sorbet)
	{
		return NULL;
	}

	sorbet->time = malloc(sizeof(SORBET_TIME_T));
	if(!sorbet->time)
	{
		return NULL;
	}

	sorbet->time->last = 0;
	sorbet->time->current = 0;
	sorbet->time->delta = 0;

	sorbet->options = NULL;
	sorbet->window = NULL;
	sorbet->exit = false;

	return sorbet;
} // sorbet__create()

void sorbet__destory(SORBET_T* sorbet)
{
	if(sorbet)
	{
		if(sorbet->options) { free(sorbet->options); }
		if(sorbet->time) { free(sorbet->time); }
		if(sorbet->window) { glfwDestroyWindow(sorbet->window); }
		free(sorbet);
	}
} // sorbet__destory()

bool sorbet__init(SORBET_T* sorbet, SORBET_OPTIONS_T* options)
{
	sorbet->options = options;
	sorbet->collection = options->collection;
	
    if (!sorbet->options || !glfwInit()) { return false; }
	else
	{
		options->framerate = options->framerate;

   		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    	sorbet->window = glfwCreateWindow(options->width, options->height,
			options->title, NULL, NULL);
		if(!sorbet->window) { return false; }
		sorbet__center_window(sorbet);

		glfwMakeContextCurrent(sorbet->window);
		glfwSwapInterval(1);
	}

	return true;
} // sorbet__init()

GLFWmonitor* sorbet__center_window(SORBET_T* sorbet)
{
	SORBET_OPTIONS_T* options = sorbet->options;
    uint32_t monitor_count;

    GLFWmonitor **monitor_list = glfwGetMonitors(&monitor_count);
	if(!monitor_list || !monitor_count)
	{
		return NULL;
	}

    GLFWmonitor *best_monitor = NULL;
    uint32_t bestArea = 0;

    for (int i = 0; i < monitor_count; i++)
    {
        GLFWmonitor *monitor = monitor_list[i];

        int monitory_x, momnitor_y;
        glfwGetMonitorPos(monitor, &monitory_x, &momnitor_y);

        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        if(!mode) { continue; }

        int areaMinX = max(options->x, monitory_x);
        int areaMinY = max(options->y, momnitor_y);

        int areaMaxX = min(options->x + options->width,
			monitory_x + mode->width);
        int areaMaxY = min(options->x + options->height,
			momnitor_y + mode->height);

        int area = (areaMaxX - areaMinX) * (areaMaxY - areaMinY);

        if (area > bestArea)
        {
            bestArea = area;
            best_monitor = monitor;
        }
    }

    if(!best_monitor) { return NULL; }

    const GLFWvidmode *mode = glfwGetVideoMode(best_monitor);
    if(!mode) { return NULL; }

    int monitorX, monitorY;
    glfwGetMonitorPos(best_monitor, &monitorX, &monitorY);

    int windowWidth, windowHeight;
    glfwGetWindowSize(sorbet->window, &windowWidth, &windowHeight);

    glfwSetWindowPos(sorbet->window,
                     monitorX + (mode->width - windowWidth) / 2,
                     monitorY + (mode->height - windowHeight) / 2);

	return best_monitor;
} // sorbet__center_window()

bool sorbet__exit(SORBET_T* sorbet)
{
	bool success = true;

	sorbet__destory(sorbet);

	glfwTerminate();

	return success;
} // sorbet__exit()

void sorbet__tick(SORBET_T* sorbet)
{
	SORBET_OPTIONS_T* options = sorbet->options;
	SORBET_TIME_T* time = sorbet->time;
	SORBET_LENGTH_T TARGET_TICKS_PER_FRAME
		= 1000.0f / (options->framerate / 1000.0f);
	{
		time->last = time->current;
		time->current = glfwGetTime();

		if((time->current - time->last) < TARGET_TICKS_PER_FRAME)
		{
			uint32_t sleep_time
				= TARGET_TICKS_PER_FRAME - (time->current - time->last);
			usleep(sleep_time);
		}

		time->delta
			= (time->current - time->last) > 0.05f
			? 0.05f
			: (time->current - time->last);

		collection__tick(sorbet, sorbet->collection);

		size_t entity_count = sorbet->collection->entity_count;
		VECTOR_T* entity_list = sorbet->collection->entity_list;

		for(size_t i = 0; i<entity_count; i++)
		{
			ENTITY_T* entity = entity_list->data[i];
			if(entity->tick) { (sorbet, entity); }
		}

		glfwPollEvents();
		if(glfwWindowShouldClose(sorbet->window)) { sorbet->exit = true; }
	}
} // sorbet__tick()

void sorbet__draw(SORBET_T* sorbet)
{
	SORBET_OPTIONS_T *options = sorbet->options;
	
	glViewport(0, 0, options->width, options->height);
	glClear(GL_COLOR_BUFFER_BIT);

	size_t entity_count = sorbet->collection->entity_count;
	VECTOR_T* entity_list = sorbet->collection->entity_list;

	for(size_t i = 0; i<entity_count; i++)
	{
		ENTITY_T* entity = entity_list->data[i];
			if(entity->render) { (sorbet, entity); }
	}

	glfwSwapBuffers(sorbet->window);
} // sorbet__draw()
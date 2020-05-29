#include "game.h"
#include "../ecs.h"

#include <SDL2/SDL_timer.h>

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

void (*sorbet_main)(void) = NULL;

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

SORBET_T* sorbet__create()
{
	SORBET_T* s = malloc(sizeof(SORBET_T));
	if(!s) {
		// TODO: logging
		return NULL;
	}

	s->quit = false;

	s->options = NULL;

	s->window = NULL;
	s->surface = NULL;
	s->renderer = NULL;

	return s;
} // SORBET_T* sorbet__create()

void sorbet__init(SORBET_T* s, s_options_t *options)
{
    if(SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO
		| SDL_INIT_VIDEO) < 0)
    {
		// TODO: logging
        printf("SDL2 was unable to initalize! Error: %s\n",
			SDL_GetError());
    }
    else
    {

        s->window = SDL_CreateWindow(options->title,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			options->width, options->height, options->flags);
        if(s->window)
        {
			s->renderer = SDL_CreateRenderer(s->window, -1, SDL_RENDERER_ACCELERATED);
			if(!s->renderer)
			{
				// TODO: logging
				printf("Renderer could not be created! Error: %s\n",
					SDL_GetError());
			}

			s->surface = SDL_GetWindowSurface(s->window);
			if(!s->surface)
			{
				// TODO: logging
				printf("Surface could not be created! Error: %s\n",
					SDL_GetError());
			}
			
			int img_flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP;
			if(!(IMG_Init(img_flags) & img_flags))
			{
				// TODO: logging
				printf("SDL_image could not initialize! Error: %s\n",
					IMG_GetError());
			}

			if(TTF_Init() == -1)
			{
				// TODO: logging
				printf("SDL_ttf c ould not initialize! Error: %s\n",
					TTF_GetError());
			}
		}
		else
		{
			// TODO: logging
            printf("Window could not be created! Error: %s\n",
				SDL_GetError());
		}
    }

	s->options = options;
} // sorbet__init()


void sorbet__run(SORBET_T* s)
{
	// TODO: logging
	SDL_Event e;
	COLLECTION_T* c = s->options->collection;

	unsigned long last = 0, time = 0, delta = 0;
	unsigned long frame = 0, ticks = 0;

	while (!s->quit)
	{
		const unsigned long FPS = 60;
		const unsigned long TICKS_PER_FRAME = 1000 / FPS;
		
		time = SDL_GetTicks();
		delta =  time - last;

		if(last < time) {
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT) { s->quit = true; }

				for(ECS__COLLECTION_SIZE_T i = 0; i<c->system_count; i++) {
					SYSTEM_T* system = c->systems[i];
					
					for(ECS__COLLECTION_SIZE_T j = 0;
						j<ECS__COLLECTION_MAX; j++) {

						ENTITY_T* entity = system->table[j];
						if(entity) { system->func(&e, entity, system->table); }
					}
				}

				sorbet_main ? sorbet_main() : NULL;
			}


			ticks+=delta;
			frame++;
			if(frame > TICKS_PER_FRAME) {
				frame = 1;
				ticks = delta;
			}
		}else {
			if(delta < TICKS_PER_FRAME){ SDL_Delay(TICKS_PER_FRAME - delta); }
 		}

		last = time;
	}
	
	sorbet__exit(s);
	// TODO: logging
} // void sorbet__run()

void sorbet__exit(SORBET_T* s)
{
	// TODO: logging
	// deallocate surface
	SDL_FreeSurface(s->surface);
	s->surface = NULL;

	// destroy renderer
	SDL_DestroyRenderer(s->renderer);
	s->renderer = NULL;

	// destroy window
	SDL_DestroyWindow(s->window);
	s->window = NULL;

    TTF_Quit();
    IMG_Quit();
 
	// quit SDL subsystems
	SDL_Quit();

	// TODO: logging
} // void sorbet__exit()

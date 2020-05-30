#ifndef ECS_TYPES_H
#define ECS_TYPES_H

/** type used to define ID numbers */
typedef unsigned long int ID_T;

/** type used to define lengths of time */
typedef unsigned long SORBET_LENGTH_T;

#ifndef ECS__ENTITIES_MAX
#define ECS__ENTITIES_MAX ((ID_T)1) << 20 // MAX # of entities
#endif

#ifndef ECS__COMPONENTS_MAX
#define ECS__COMPONENTS_MAX ((ID_T)1) << 7 // MAX # of components
#endif

/** defines the status of an entity/component */
typedef enum STATUS {
	/** interaction not allowed (exists on system) */
	DISABLED,
	/** interaction allowed (assumes linked) */
	ENABLED,
	/** is queued to be removed from it's system */
	EXPUNGE,
	/** does not exist on it's system*/
	UNLINKED
} STATUS_T;

#endif
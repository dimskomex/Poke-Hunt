#include <stdlib.h>
#include <time.h>

#include "ADTVector.h"
#include "ADTList.h"
#include "state.h"
#include "updates.h"

#define MIN_HEIGHT (SCREEN_HEIGHT - 45)

// The complete game state information.
// The State type is a pointer to this struct, but the struct itself
// not visible to the user.

struct state 
{
	Vector objects;			 	// contains elements Object (Platforms, Pokemon)
	struct state_info info; 	// General information about the state of the game
	float speed_factor; 		// Speed multiplier (1 = normal speed, 2 = double, etc)
};

static bool is_legendary(Pokemon pokemon)
{
	return pokemon == ZEKROM || pokemon == RESHIRAM || pokemon == ARCEUS || pokemon == REYQUAZA;
}

// Creates and returns an object
static Object create_object(ObjectType type, float x, float y, float width, float height, VerticalMovement vert_mov, float speed, bool unstable, Pokemon pokemon, Pokeball pokeball) 
{
	Object obj = malloc(sizeof(*obj));
	obj->type = type;
	obj->rect.x = x;
	obj->rect.y = y;
	obj->rect.width = width;
	obj->rect.height = height;
	obj->vert_mov = vert_mov;
	obj->vert_speed = speed;
	obj->unstable = unstable;
	obj->pokemon = pokemon;
	obj->pokeball = pokeball;
	return obj;
}

// Adds objects to the track (which may already contain objects).
// Objects start at x = start_x, and expand to the right.
//
// ATTENTION: all objects have x,y coordinates of one
// cartesian plane.
// - On the x-axis 0 is the start of the track and the coordinates
// grow to the right.
//
// - On the y-axis 0 is the top of the track, and the coordinates are increasing
//   downwards_. The track has a fixed height, so all the
// y coordinates are between 0 and SCREEN_HEIGHT.
//
// In addition to the coordinates, we also store the dimensions width,height
// of each object. x,y,width,height define a rectangle, so
// can be stored all together in obj->rect of type Rectangle (defined
// in include/raylib.h). x,y refer to the top-left corner of the Rectangle.
static void add_objects(State state, float start_x) 
{
	srand(time(NULL));
	// Add PLATFORM_NUM platforms, with random attributes.
	for (int i = 0; i < PLATFORM_NUM; i++) 
	{
		Object platform = create_object
		(
			PLATFORM,
			start_x + 150 + rand() % 80, 						// x with random distance from previous in interval [150, 230]
			SCREEN_HEIGHT/4 + rand() % SCREEN_HEIGHT/2, 		// y random in the interval [SCREEN_HEIGHT/4, 3*SCREEN_HEIGHT/4]
			i == 0 ? 250 : 50 + rand()%200, 					// width randomly in the interval [50, 250] (first always 250)
			20, 												// height
			i < 3 || rand() % 2 == 0 ? MOVING_UP : MOVING_DOWN, // random initial move (first 3 always up)
			0.6 + 3*(rand()%100)/100, 							// speed randomly in the interval [0.6, 3.6]
			i > 0 && (rand() % 10) == 0, 						// 10% (random) platforms are unstable (except the first one)
			NOTHING,											// is not pokemon
			NO_POKEBALL											// is not pokeball
		);
		vector_insert_last(state->objects, platform);

		// On 50% of the platforms (random), except the first one, we add pokemon
		if(i != 0 && rand() % 2 == 0) 
		{
			Object pokemon = create_object
			(
				POKEMON,
				start_x + 200 + rand() % 60, 					// x with a random distance from the previous platform in the interval [200,260]
				SCREEN_HEIGHT/8 + rand() % SCREEN_HEIGHT/2, 	// y random in the interval [SCREEN_HEIGHT/8, 5*SCREEN_HEIGHT/8]
				30, 30, 										// width, height
				IDLE, 											// no movement
				0, 												// speed 0
				false, 											// 'unstable' always false for stars
				rand() % 16,									// one of the 15 pokemons (random)
				NO_POKEBALL
			);
			vector_insert_last(state->objects, pokemon);
		}

		start_x = platform->rect.x + platform->rect.width;		// move next items to the right
	}
}

static void game_over(StateInfo info)
{
	info->playing = false;
	info->paused = true;
}

static void new_state(State state)
{
	state->info.playing = true;
	state_destroy(state);
	state = state_create();
}

static Object find_max_platform(State state)
{
	Object max = vector_get_at(state->objects, 0);
	for (int i = 1; i < vector_size(state->objects); i++)
	{
		Object obj = vector_get_at(state->objects, i);
		if (obj->rect.x > max->rect.x && obj->type == PLATFORM)
			max = obj;
	}

	return max;
}

static bool collision_success(Pokeball pokeball)
{
	return pokeball == POKEBALL ? rand() % 40 == 0 : pokeball == ULTRABALL ? rand() % 30 == 0 : true;
}

static Pokeball upgrade_pokeball(int score)
{
	return score <= 35 ? POKEBALL : score <= 95 ? ULTRABALL : MASTERBALL;
}

State state_create() 
{
	// Create the state
	State state = malloc(sizeof(*state));

	// General informations
	state->info.playing = true; 	// The game starts immediately
	state->info.paused = false; 	// Without being paused.
	state->speed_factor = 1; 		// Normal speed
	state->info.score = 0; 			// Initial score 0

	// Create the vector of objects, and add objects
	// starting at x = 0.
	state->objects = vector_create(0, NULL);
	add_objects(state, 0);

	// Create the ball by placing it on the first platform
	Object first_platform = vector_get_at(state->objects, 0);
	state->info.ball = create_object
	(
		BALL,
		first_platform->rect.x, 		// x at the beginning of the platform
		first_platform->rect.y - 40, 	// y on platform
		45, 45, 						// width, height
		IDLE, 							// no initial vertical movement
		0, 								// initial speed 0
		false, 							// "unstable" always false for ball
		NOTHING,						// is not pokemon
		POKEBALL
	);

	return state;
}


StateInfo state_info(State state) 
{
	return &state->info;
}

List state_objects(State state, float x_from, float x_to) 
{
	List result;

	result = list_create(NULL);
	for (int i = 0; i < vector_size(state->objects); i++)
	{
		Object obj = vector_get_at(state->objects, i);
		if (obj->rect.x >= x_from && obj->rect.x <= x_to)
			list_insert_next(result, LIST_BOF, obj);
	}

	return result;
}

static bool is_paused(bool paused, KeyState keys)
{
	return (!paused || (keys->n && paused));
}

void state_update(State state, KeyState keys)
{	

	if (!is_paused(state->info.playing, keys)) 
	{
		Object last_platform = find_max_platform(state);
		update_ball(state->info.ball, keys, state->speed_factor);

		// in each frame the falling state is made so that a collision can occur
		if (state->info.ball->vert_mov == IDLE)
		{
			state->info.ball->vert_mov = FALLING;
			state->info.ball->vert_speed = 1.5;
		}

		for (int i = 0; i < vector_size(state->objects); i++)
		{
			Object obj = vector_get_at(state->objects, i);
			if (obj->type == PLATFORM)
				update_platform(obj, state->info.ball, state->speed_factor);

			if (CheckCollisionRecs(obj->rect, state->info.ball->rect))
			{
				if (obj->type == POKEMON)
				{
					bool success = collision_success(state->info.ball->pokeball);

					if (success)
					{
						state->info.score += is_legendary(obj->pokemon) ? 15 : 10;
						vector_remove(state->objects, i);	
					}
							
					state->info.ball->pokeball = upgrade_pokeball(state->info.score);				
				}
				else if (obj->type == PLATFORM && state->info.ball->vert_mov != JUMPING && state->info.ball->rect.y < (obj->rect.y - obj->rect.height))
				{
					state->info.ball->rect.y = obj->rect.y - state->info.ball->rect.height + 2;
					state->info.ball->vert_mov = IDLE;
				}
			}
		}

		if (last_platform->rect.x - state->info.ball->rect.x < SCREEN_WIDTH)
		{
			add_objects(state, last_platform->rect.x + 100);
			state->speed_factor *=  1.1;
		} 

		if(!(state->info.ball->rect.y < MIN_HEIGHT)) 
			game_over(&state->info);
	}
	
	if (!state->info.playing && keys->enter)
		new_state(state);

	if (keys->p)
		state->info.paused = !state->info.paused;
}

void state_destroy(State state)
{
	vector_destroy(state->objects);
	free(state);
}

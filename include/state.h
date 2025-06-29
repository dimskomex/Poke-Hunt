#pragma once

#include "ADTList.h"
#include <raylib.h>

#define PLATFORM_NUM 20   // how many platforms are created on the track
#define SCREEN_WIDTH 900  // Width of the screen
#define SCREEN_HEIGHT 450 // Height of the screen

#define NO_POKEMON 0
#define NO_POKEBALL 0

typedef enum { POKEBALL, PLATFORM, POKEMON } ObjectType;

typedef enum {
  IDLE,
  JUMPING,
  FALLING,
  MOVING_UP,
  MOVING_DOWN
} VerticalMovement;

typedef enum {
  // classic
  STARYU = 1,
  HYPNO,
  STARMIE,
  GENGAR,
  SNORLAX,
  TORTERRA,
  WOBBUFFET,
  AZUMARILL,

  // iconic
  GYARADOS,
  BULBASAUR,
  CHARMANDER,
  PICACHU,
  SQUIRTLE,
  EEVEE,
  LUCARIO,

  // legendary
  MEWTWO,
  RESHIRAM,
  ARCEUS,
  REYQUAZA,
  ZEKROM
} Pokemon;

typedef enum {
  CLASSIC_POKEBALL = 1,
  GREAT_BALL,
  ULTRABALL,
  MASTERBALL
} Pokeball;

// Information about each object
struct object {
  ObjectType type; // Type (Ball, Platform, Pokemon)
  Rectangle rect;  // Position and size of the object. Rectangle is defined in
                   // include/raylib.h, line 213
  VerticalMovement vert_mov; // Type of vertical movement
  float vert_speed;          // Vertical velocity
  bool unstable;             // (platforms only) true if unstable
  Pokemon pokemon;           // What pokemon is it
  Pokeball pokeball;         // What type of pokeball is it
};

typedef struct object *Object;

// General information about the state of the game
struct state_info {
  Object ball;  // information about the ball
  bool playing; // true if game is active (false after game over)
  bool paused;  // true if the game is paused
  int score;    // the current score
};

typedef struct state_info *StateInfo;

// Information about which keys are pressed
struct key_state {
  bool up; // true if the corresponding key is pressed
  bool left;
  bool right;
  bool enter;
  bool n;
  bool p;
};

typedef struct key_state *KeyState;

// The game state (handle)
typedef struct state *State;

// Creates and returns the initial state of the game
State state_create(void);

// Returns basic game information in state
StateInfo state_info(State state);

// Returns a list of all game objects in state,
// whose x coordinate is between x_from and x_to.
List state_objects(State state, float x_from, float x_to);

// Updates the game state after 1 frame has passed.
// keys contains the keys that were pressed during this frame.
void state_update(State state, KeyState keys);

// Destroys state by freeing the allocated memory.
void state_destroy(State state);

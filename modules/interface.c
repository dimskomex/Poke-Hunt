#include <time.h>
#include <stdlib.h>

#include "raylib.h"
#include "state.h"
#include "interface.h"

// Photos
Texture pokeball_img, greatball_img, ultraball_img, timerball_img, masterball_img;
Texture mewtwo_img, arceus_img, reyquaza_img, zekrom_img, reshiram_img; 
Texture staryu_img, starmie_img, bulbasaur_img, charmander_img, picachu_img, gengar_img;
Texture torterra_img, eevee_img, snorlax_img, squirtle_img, lucario_img, hypno_img, wobbuffet_img;
Texture azumarill_img, gyarados_img;

// Sounds
Sound music;
Sound coin_sound;

static Texture2D draw_pokemon(Pokemon pokemon)
{
	return pokemon == STARYU ? staryu_img : pokemon == STARMIE ? starmie_img : pokemon == BULBASAUR ? bulbasaur_img :
	pokemon == CHARMANDER ? charmander_img : pokemon == PICACHU ? picachu_img : pokemon == ZEKROM ? zekrom_img : pokemon == RESHIRAM ? 
	reshiram_img : pokemon == ARCEUS ? arceus_img : pokemon == REYQUAZA ? reyquaza_img : pokemon == SNORLAX ? snorlax_img : pokemon == EEVEE ? eevee_img :
	pokemon == TORTERRA ? torterra_img : pokemon == SQUIRTLE ? squirtle_img : pokemon == GENGAR ? gengar_img : pokemon == MEWTWO ? mewtwo_img :
	pokemon == HYPNO ? hypno_img : pokemon == LUCARIO ? lucario_img : pokemon == AZUMARILL ? azumarill_img : pokemon == WOBBUFFET ? wobbuffet_img : gyarados_img;
}

static Texture draw_pokeball(StateInfo info)
{
	return info->ball->pokeball == 	CLASSIC_POKEBALL ? pokeball_img : info->ball->pokeball == GREAT_BALL ? greatball_img : 
									info->ball->pokeball == ULTRABALL ? ultraball_img : info->ball->pokeball == TIMERBALL ? timerball_img:  masterball_img; 
}

void interface_init() 
{
	// Initialize the window
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Poke-Hunt");
	SetTargetFPS(60);
    InitAudioDevice();

	// Load images
	pokeball_img = LoadTextureFromImage(LoadImage("photos/pokeball.png"));
	greatball_img = LoadTextureFromImage(LoadImage("photos/greatball.png"));
	ultraball_img = LoadTextureFromImage(LoadImage("photos/ultraball.png"));
	timerball_img = LoadTextureFromImage(LoadImage("photos/timerball.png"));
	masterball_img = LoadTextureFromImage(LoadImage("photos/masterball.png"));

	staryu_img = LoadTextureFromImage(LoadImage("photos/staryu.png"));
	starmie_img = LoadTextureFromImage(LoadImage("photos/starmie.png"));
	bulbasaur_img = LoadTextureFromImage(LoadImage("photos/bulbasaur.png"));
	charmander_img = LoadTextureFromImage(LoadImage("photos/charmander.png"));
	picachu_img = LoadTextureFromImage(LoadImage("photos/picachu.png"));
	zekrom_img = LoadTextureFromImage(LoadImage("photos/zekrom.png"));
	reshiram_img = LoadTextureFromImage(LoadImage("photos/reshiram.png"));
	arceus_img = LoadTextureFromImage(LoadImage("photos/arceus.png"));
	reyquaza_img = LoadTextureFromImage(LoadImage("photos/reyquaza.png"));
	snorlax_img = LoadTextureFromImage(LoadImage("photos/snorlax.png"));
	eevee_img = LoadTextureFromImage(LoadImage("photos/eevee.png"));
	torterra_img = LoadTextureFromImage(LoadImage("photos/torterra.png"));
	squirtle_img = LoadTextureFromImage(LoadImage("photos/squirtle.png"));
	gengar_img = LoadTextureFromImage(LoadImage("photos/gengar.png"));
	lucario_img = LoadTextureFromImage(LoadImage("photos/lucario.png"));
	mewtwo_img = LoadTextureFromImage(LoadImage("photos/mewtwo.png"));
	hypno_img = LoadTextureFromImage(LoadImage("photos/hypno.png"));
	gyarados_img = LoadTextureFromImage(LoadImage("photos/gyarados.png"));
	wobbuffet_img = LoadTextureFromImage(LoadImage("photos/wobbuffet.png"));
	azumarill_img = LoadTextureFromImage(LoadImage("photos/azumarill.png"));


	// Load sounds
	music = LoadSound("sounds/Pokémon_Black_and_White_2.mp3");
	PlaySound(music);
	SetSoundVolume(music, 0.25);

	coin_sound = LoadSound("sounds/coin_sound.mp3");
}

void interface_close() 
{
	CloseAudioDevice();
	CloseWindow();
}

// Draw game (one frame)
void interface_draw_frame(State state) 
{
	BeginDrawing();

	// Cleanup, we'll draw everything from scratch
	ClearBackground(BLACK);

	// Draw the ball
     StateInfo info = state_info(state);
	float x_offset;

	x_offset = SCREEN_WIDTH - 193 - info->ball->rect.x;

	DrawTexture(draw_pokeball(info), SCREEN_WIDTH / 4, info->ball->rect.y, WHITE);

	List objs;

	objs = state_objects(state, info->ball->rect.x - SCREEN_WIDTH, info->ball->rect.x + SCREEN_WIDTH);

	Object obj;
	for (ListNode node = list_first(objs); node != LIST_EOF; node = list_next(objs, node))
	{
		obj = list_node_value(objs, node);

		obj->type == PLATFORM ? DrawRectangle(obj->rect.x + x_offset - 450, obj->rect.y, obj->rect.width, obj->rect.height, obj->unstable ? RED : WHITE) : 
								DrawTexture(draw_pokemon(obj->pokemon), obj->rect.x + x_offset - 450, obj->rect.y, WHITE);
	}

	// Plot the score and FPS counter
	DrawText(TextFormat("%04i", info->score), 20, 20, 40, GRAY);
	DrawFPS(SCREEN_WIDTH - 80, 0);

	// If the game is over, draw the message to restart it
	if (!info->playing) 
	{
		DrawText
		(
			"PRESS [ENTER] TO CATCH MORE POKEMON",
			 GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO CATCH MORE POKEMON", 20) / 2,
			 GetScreenHeight() / 2 - 50, 20, GRAY
		);
	}

	EndDrawing();
}

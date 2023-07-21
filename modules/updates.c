#include "updates.h"

void update_pokeball(Object pokeball, KeyState keys, float speed_factor, int score)
{
	pokeball->rect.x += keys->right ? 6 : keys->left ? 0.8 : 4; 

	if (pokeball->vert_mov == JUMPING)
	{
		pokeball->rect.y -= (pokeball->vert_speed * speed_factor); 		// increase upwards => decrease in y 
		pokeball->vert_speed *= 0.85;
		
		if (pokeball->vert_speed <= 0.5) 
			pokeball->vert_mov = FALLING;

		// if he has reached the maximum possible height when jumping, the Pokeball must fall
		if (pokeball->rect.y == SCREEN_HEIGHT) 
			pokeball->vert_mov = FALLING; 

	}
	else if (pokeball->vert_mov == FALLING)
	{
		pokeball->rect.y += (pokeball->vert_speed * speed_factor);	 	// decrease downwards => increase in y
		pokeball->vert_speed *= 1.1;

		if (pokeball->vert_speed > 7)
			pokeball->vert_speed = 7;

	}
	else if (pokeball->vert_mov == IDLE && keys->up)
	{
		pokeball->vert_mov = JUMPING;
		pokeball->vert_speed = 17;
	}

	pokeball->pokeball = score <= 35 ? POKEBALL : score <= 95 ? ULTRABALL : MASTERBALL;
}

void update_platform(Object platform, float speed_factor)
{
	if (platform->vert_mov == MOVING_UP)
	{
		platform->rect.y -= (platform->vert_speed * speed_factor);

		if (platform->rect.y < SCREEN_HEIGHT / 4)
			platform->vert_mov = MOVING_DOWN;

	}
	else if (platform->vert_mov == MOVING_DOWN)
	{
		platform->rect.y += (platform->vert_speed * speed_factor);

		if (platform->rect.y > 3 * SCREEN_HEIGHT / 4)
			platform->vert_mov = MOVING_UP;

	}
	else if (platform->vert_mov == FALLING)
		platform->rect.y += 4;
}

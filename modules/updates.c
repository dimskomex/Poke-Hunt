#include "state.h"

void update_ball(Object ball, KeyState keys, float speed_factor)
{
	ball->rect.x += keys->right ? 6 : keys->left ? 1 : 4; 

	if (ball->vert_mov == JUMPING)
	{
		ball->rect.y -= (ball->vert_speed * speed_factor); // αύξηση προς τα πάνω => μείωση του y 
		ball->vert_speed *= 0.85;
		
		if (ball->vert_speed <= 0.5) 
			ball->vert_mov = FALLING;

		if (ball->rect.y == SCREEN_HEIGHT) // δεν αναφέρεται κάπου, αλλά άμα έχει φτάσει στο μέγιστο δυνατό ύψος όταν κανει jump, πρέπει να πέφτει η μπάλα
			ball->vert_mov = FALLING; 

	}
	else if (ball->vert_mov == FALLING)
	{
		ball->rect.y += (ball->vert_speed * speed_factor); // μείωση προς τα κάτω => αύξηση του y
		ball->vert_speed *= 1.1;

		if (ball->vert_speed > 7)
			ball->vert_speed = 7;

	}
	else if (ball->vert_mov == IDLE && keys->up)
	{
		ball->vert_mov = JUMPING;
		ball->vert_speed = 17;
	}
}

void update_platform(Object platform, Object ball, float speed_factor)
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

	if (platform->unstable && CheckCollisionRecs(ball->rect, platform->rect))
	{
		platform->vert_mov = FALLING;
		platform->rect.y += 4;
		ball->rect.y += 4;
	}
}
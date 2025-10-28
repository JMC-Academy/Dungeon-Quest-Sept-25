#include "Player.h"

void Player::Move(int dir, int dist)
{
	if (dir == 1)
		GetRect()->y -= dist;
	if (dir == 2)
		GetRect()->x += dist;
	if (dir == 3)
		GetRect()->y += dist;
	if (dir == 4)
		GetRect()->x -= dist;
}

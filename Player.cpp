#include "Player.h"

void Player::Move(Direction dir, int dist)
{
	if (dir == Direction::North)
		Rect.y -= dist;
	if (dir == Direction::East)
		Rect.x += dist;
	if (dir == Direction::South)
		Rect.y += dist;
	if (dir == Direction::West)
		Rect.x -= dist;
}

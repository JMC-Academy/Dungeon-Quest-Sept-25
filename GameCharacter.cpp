#include "GameCharacter.h"
#include "Enums.h"

GameCharacter::GameCharacter()
{
}

GameCharacter::~GameCharacter()
{
}

void GameCharacter::Move(Direction dir, int dist)
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

void GameCharacter::Attack(GameCharacter& other)
{
}

void GameCharacter::Killed()
{
}

void GameCharacter::Update(float dt)
{
}

void GameCharacter::Collect(Pickup& pickup)
{
}

bool GameCharacter::CanMoveBetweenRooms()
{
	return false;
}

bool GameCharacter::GetIsAlive()
{
	return false;
}

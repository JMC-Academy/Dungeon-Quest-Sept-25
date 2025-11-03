#pragma once
#include "Pickup.h";
#include <SDL3_image/SDL_image.h>
class GameCharacter
{
public:
	GameCharacter();	//constructor, called when created
	~GameCharacter();	//destructor, called when destroyed
	virtual void Attack(GameCharacter& other);
	virtual void Killed();
	virtual void Update(float dt);	//for anything time-related
	virtual void Collect(Pickup& pickup);
	virtual bool CanMoveBetweenRooms();	//false by default
	bool GetIsAlive();
	SDL_Texture* Texture;
	SDL_FRect Rect;

private:
	bool isAlive = true;
	
};
#include "Tile.h"

bool Tile::CompareColours(SDL_Color& col1, SDL_Color& col2)
{
	return col1.r == col2.r && col1.g == col2.g && col1.b == col2.b;
}

void Tile::Configure(SDL_Color& color, float x, float y, float size, SDL_Texture* textures[])
{
	SDL_Color black = { 0, 0, 0, 255 };
	if (CompareColours(color, black))
	{
		Walkable = false;
		this->Texture = nullptr;
	}
	else
	{
		Walkable = true;
		this->Texture = textures[1];
	}

	//this->Rect = { x * size, y * size, size, size };
	SDL_FRect rect;
	rect.x = x * size;
	rect.y = y * size;
	rect.w = size;
	rect.h = size;
	this->Rect = rect;
}

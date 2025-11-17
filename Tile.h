#pragma once
#include <list>
#include "Enums.h"
#include <SDL3/SDL.h>
#include <iostream>
class Tile
{
	static bool CompareColours(SDL_Color& col1, SDL_Color& col2);

public:

	Tile();
	Tile(int id);
	~Tile();

	int posX; // logical position x
	int posY; // logical position y
	int ID;
	int VisualMaterial;
	SDL_Texture* Texture;
	SDL_FRect Rect;

	void SetPosition(int x, int y);
	void Configure(SDL_Color& color, float x, float y, float size, SDL_Texture* textures[]);

	Tile* GetNeighbour(Direction dir);
	void SetNeighbour(Direction dir, Tile& newNeighbour, bool reciprocate);
	void AddNeighbour(Tile& neighbour, bool reciprocate);
	std::list<Tile>* GetAllNeighbours();

	Direction GetIsEdge();
	void SetIsEdge(Direction dir);

	void SetWalkable(bool w);
	bool GetWalkable();

private:
	std::list<Tile> neighbours;
	Tile* neighbourNorth;
	Tile* neighbourSouth;
	Tile* neighbourEast;
	Tile* neighbourWest;
	Direction edge;
	bool walkable;
};


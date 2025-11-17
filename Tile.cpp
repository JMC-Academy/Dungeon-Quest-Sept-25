#include "Tile.h"

Tile::Tile()
{
	neighbourNorth = nullptr;
	neighbourSouth = nullptr;
	neighbourEast = nullptr;
	neighbourWest = nullptr;
	ID = 0;
	posX = 0;
	posY = 0;
	VisualMaterial = -1;
	edge = Direction::Unknown;
}

Tile::Tile(int id)
{
	neighbourNorth = nullptr;
	neighbourSouth = nullptr;
	neighbourEast = nullptr;
	neighbourWest = nullptr;
	ID = id;
	posX = 0;
	posY = 0;
	VisualMaterial = -1;
	edge = Direction::Unknown;
}

Tile::~Tile()
{
	//delete Rect;
}

bool Tile::CompareColours(SDL_Color& col1, SDL_Color& col2)
{
	return col1.r == col2.r && col1.g == col2.g && col1.b == col2.b;
}

void Tile::SetPosition(int x, int y)
{
}

void Tile::Configure(SDL_Color& color, float x, float y, float size, SDL_Texture* textures[])
{
	SDL_Color black = { 0, 0, 0, 255 };
	if (CompareColours(color, black))
	{
		walkable = false;
		this->Texture = nullptr;
	}
	else
	{
		walkable = true;
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

Tile* Tile::GetNeighbour(Direction dir)
{
	switch (dir) {
	case Direction::North:
		return neighbourNorth;
		break;
	case Direction::South:
		return neighbourSouth;
		break;
	case Direction::West:
		return neighbourWest;
		break;
	case Direction::East:
		return neighbourEast;
		break;

	default:
		return nullptr;
	}
}

void Tile::SetNeighbour(Direction dir, Tile& newNeighbour, bool reciprocate)
{
	if (dir == Direction::North) {
		neighbourNorth = &newNeighbour;
	}
	if (dir == Direction::East) {
		neighbourEast = &newNeighbour;
	}
	if (dir == Direction::South) {
		neighbourSouth = &newNeighbour;
	}
	if (dir == Direction::West) {
		neighbourWest = &newNeighbour;
	}


	neighbours.push_back(newNeighbour);

	if (reciprocate)
	{
		Direction op = Opposite(dir);
		newNeighbour.SetNeighbour(op, *this, false);
	}
}

void Tile::AddNeighbour(Tile& neighbour, bool reciprocate)
{
}

std::list<Tile>* Tile::GetAllNeighbours()
{
	return &neighbours;
}

Direction Tile::GetIsEdge()
{
	return edge;
}

void Tile::SetIsEdge(Direction dir)
{
	edge = dir;
}

void Tile::SetWalkable(bool w)
{
	walkable = w;
}

bool Tile::GetWalkable()
{
	return walkable;
}

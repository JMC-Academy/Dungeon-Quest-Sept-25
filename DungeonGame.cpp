#include "DungeonGame.h"
DungeonGame::DungeonGame(float tileSizeX, float tileSizeY)
{
	this->tileSizeX = tileSizeX;
	this->tileSizeY = tileSizeY;
}

DungeonGame::~DungeonGame()
{
	delete this->Hero;
}

void DungeonGame::LoadTextures(SDL_Renderer* renderer)
{
	this->Hero = new Player;

	// Load all textures
	this->Hero->Texture = IMG_LoadTexture(renderer, path_Hero.c_str());
	SDL_SetTextureScaleMode(this->Hero->Texture, SDL_SCALEMODE_NEAREST);    // Disables texture filtering for an old-school look.

	this->Hero->Rect.x = 0;
	this->Hero->Rect.y = 0;
	this->Hero->Rect.w = tileSizeX;
	this->Hero->Rect.h = tileSizeY;

	// Load carpet textures
	for (int n = 0; n < 3; n++)
	{
		this->CarpetTextures[n] = IMG_LoadTexture(renderer, path_Carpet[n].c_str());
		SDL_SetTextureScaleMode(this->CarpetTextures[n], SDL_SCALEMODE_NEAREST);
	}

}

void DungeonGame::LoadRoom(const char* file)
{
	SDL_Surface* surface = SDL_LoadBMP(file);

	const SDL_PixelFormatDetails* pixelDetails = SDL_GetPixelFormatDetails(surface->format);
	const Uint8 bpp = SDL_BYTESPERPIXEL(surface->format);
	SDL_Color col;

	for (int y = 0; y < surface->h; y++) 
	{
		for (int x = 0; x < surface->w; x++)
		{
			Uint8* pixel = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * bpp;
			SDL_GetRGB(*reinterpret_cast<Uint32*>(pixel), pixelDetails, NULL, &col.r, &col.g, &col.b);

			// col contains pixel color at position x, y
			// Now configure the tile at x,y with col
			this->Tiles[x][y].Configure(col, x, y, tileSizeX, this->CarpetTextures);
		}
	}

}

void DungeonGame::LoadRoom(int x, int y, bool firstTime, int spawnX, int spawnY)
{
}

void DungeonGame::EnterNewRoom(Direction headingDirection)
{
	int posX = Hero->CurrentTile->posX;
	int posY = Hero->CurrentTile->posY;

	bool doLoad = false;
	if (headingDirection == Direction::West)
	{
		if (currentOverlandX > 0)
		{
			doLoad = true;
			currentOverlandX--;
			posX = gridWidth - 1;
			std::cout << "went west" << std::endl;
		}
	}
	else if (headingDirection == Direction::East)
	{
		if (currentOverlandX < overlandWidth - 1)
		{
			doLoad = true;
			currentOverlandX++;
			posX = 0;
			std::cout << "went east" << std::endl;
		}
	}
	else if (headingDirection == Direction::South)
	{
		if (currentOverlandY < overlandHeight - 1)
		{
			doLoad = true;
			currentOverlandY++;
			posY = 0;
			std::cout << "went south" << std::endl;
		}
	}
	else if (headingDirection == Direction::North)
	{
		if (currentOverlandY > 0)
		{
			doLoad = true;
			currentOverlandY--;
			posY = gridHeight - 1;
			std::cout << "went north" << std::endl;
		}
	}

	if (doLoad)
	{
		LoadRoom(currentOverlandX, currentOverlandY, false, posX, posY);
	}
}

void DungeonGame::InitGrid()
{
	int index = 0;
	// instantiate nodes
	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight; y++)
		{
			Tile* tile = &Tiles[x][y];
			tile->ID = index;
			tile->SetPosition(x, y);

			// set if the node is an edge
			if (x == 0)
			{
				tile->SetIsEdge(Direction::West);
			}
			else if (x == gridWidth - 1)
			{
				tile->SetIsEdge(Direction::East);
			}
			if (y == 0)
			{
				tile->SetIsEdge(Direction::North);
			}
			else if (y == gridHeight - 1)
			{
				tile->SetIsEdge(Direction::South);
			}

			// create a rect to represent the node
			SDL_FRect r;
			r.x = x * tileSizeX;
			r.y = y * tileSizeY;
			r.w = tileSizeX;
			r.h = tileSizeY;

			//rects[index] = r;
			tile->Rect = r;

			index++;
		}
	}

	// connect neighbours
	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight; y++)
		{
			// north: y-1
			if (y > 0)
			{
				Tile* northNeighbour = &Tiles[x][y - 1];
				Tiles[x][y].SetNeighbour(Direction::North, *northNeighbour, false);
			}
			// south: y+1
			if (y < gridHeight - 1)
			{
				Tile* southNeighbour = &Tiles[x][y + 1];
				Tiles[x][y].SetNeighbour(Direction::South, *southNeighbour, false);
			}

			// east: x+1
			if (x < gridWidth - 1)
			{
				Tile* eastNeighbour = &Tiles[x + 1][y];
				Tiles[x][y].SetNeighbour(Direction::East, *eastNeighbour, false);
			}

			//west: x-1
			if (x > 0)
			{
				Tile* westNeighbour = &Tiles[x - 1][y];
				Tiles[x][y].SetNeighbour(Direction::West, *westNeighbour, false);
			}
		}
	}
}

void DungeonGame::InitializeOverland()
{
	for (int x = 0; x < overlandWidth; x++)
	{
		for (int y = 0; y < overlandHeight; y++)
		{
			// choose a random to select a room
			int roomMax = std::size(roomFiles);
			int randomIndex = rand() % roomMax;
			overland[x][y] = randomIndex;
		}
	}
}

void DungeonGame::RefreshVisuals()
{
	// run through the grid and udpate the rects list to reflect 

	int index = 0;
	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight; y++)
		{
			if (Tiles[x][y].GetWalkable())   // is walkable, so pick a random tile texture for this node.
			{
				// Rects[x][y] = 
				int texMax = 3;// std::size(tileSetB);		// TODO pick from different tilesets , eg. read from data file pixel colour.
				int randomIndex = rand() % texMax;


				if (rand() % 10 <= 2)
				{
					Tiles[x][y].Texture = tileSetB[randomIndex];
				}
				else
				{
					Tiles[x][y].Texture = tileSetB[0];
				}



			}
			else // not walkable, use the unwalkable texture.            
			{
				//nodeGrid[x][y].Tex = texture_unwalkable;
				//textureGrid[index] = texture_unwalkable;
				Tiles[x][y].Texture = texture_unwalkable;
			}

			index++;

		}
	}
}

Tile* DungeonGame::FindNeighbour(int x, int y, Direction dir)
{
	if (dir == Direction::North)
	{
		if (y > 0)
		{
			return &Tiles[x][y - 1];
		}
	}
	else if (dir == Direction::South)
	{
		if (y < gridHeight - 1)
		{
			return &Tiles[x][y + 1];
		}
	}
	else if (dir == Direction::East)
	{
		if (x < gridWidth - 1)
		{
			return &Tiles[x + 1][y];
		}
	}
	else if (dir == Direction::West)
	{
		if (x > 0)
		{
			return &Tiles[x - 1][y];
		}
	}

	return nullptr;
}

bool DungeonGame::IsTileVacant(Tile& tile)
{
	return false;
}

MoveResult DungeonGame::TryMove(GameCharacter& character, Direction dir)
{
	return MoveResult();
}

void DungeonGame::HandleMoveDirection(GameCharacter& character, Direction dir)
{
	if (character.CanMoveBetweenRooms()) // only the player can trigger a room transition
	{
		Tile* currentTile = character.CurrentTile;
		if (currentTile->GetIsEdge() == dir)
		{
			// try entering a new room	
			EnterNewRoom(dir);
			return;
		}
	}


	auto result = TryMove(character, dir);

	if (result.GetAction() == MoveResultAction::MoveOK)
	{
		CharacterMovedToTile(character, *result.GetTile());
	}
	else if (result.GetAction() == MoveResultAction::Fight)
	{
		// try do a fight.
		//character.Attack(*result.GetFightCharacter());
	}
}

void DungeonGame::CharacterMovedToTile(GameCharacter& character, Tile& tile)
{
	character.Rect.x = tile.posX * tileSizeX;
	character.Rect.y = tile.posY * tileSizeY;
	character.Rect.w = tileSizeX;
	character.Rect.h = tileSizeY;
	character.CurrentTile = &tile;
	//character.PosX = tile.posX;
	//character.PosY = tile.posY;

	// collect any pickups on the tile
	/*auto pickup = tile.GetPickup();
	if (pickup != nullptr)
	{
		bool tryPickup = character.Collect(*pickup);
		if (tryPickup)
		{
			tile.ClearPickup();
		}
	}*/
}

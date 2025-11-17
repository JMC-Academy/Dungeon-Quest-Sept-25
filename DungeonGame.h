#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <list>
#include "GameCharacter.h"
#include "Player.h"
#include "Tile.h"
#include "Enums.h"
#include "MoveResult.h"

const static std::string path_Hero = "Textures/Hero_sword.png";
const static std::string path_Carpet[] = {
										"Textures/Tile_carpet_base.bmp" ,
										"Textures/Tile_carpet_blood_1.bmp",
										"Textures/Tile_carpet_bones.bmp"
};
const static char* roomFiles[]{ "Data/Rooms/Room01.bmp",
								"Data/Rooms/Room02.bmp",
								"Data/Rooms/Room03.bmp",
								"Data/Rooms/Room04.bmp",
								"Data/Rooms/Room05.bmp" };

const static int RoomSize = 10;
const int gridWidth = 10;
const int gridHeight = 10;
const int overlandWidth = 10;
const int overlandHeight = 10;

class DungeonGame
{
public:
	DungeonGame(float tileSizeX, float tileSizeY);
	~DungeonGame();
	void LoadTextures(SDL_Renderer* renderer);
	void LoadRoom(const char* file);
	void LoadRoom(int x, int y, bool firstTime, int spawnX, int spawnY);
	void EnterNewRoom(Direction headingDirection);
	void InitGrid();
	void InitializeOverland();
	void RefreshVisuals();
	Tile* FindNeighbour(int fromX, int fromY, Direction dir);

	Player* Hero;
	Tile Tiles[RoomSize][RoomSize];
	SDL_Texture* CarpetTextures[3];

	bool IsTileVacant(Tile& tile);
	MoveResult TryMove(GameCharacter& character, Direction dir);
	void HandleMoveDirection(GameCharacter& character, Direction dir);
	void CharacterMovedToTile(GameCharacter& character, Tile& tile);

	// overland vars
	int overland[overlandWidth][overlandHeight];
	int currentOverlandX;
	int currentOverlandY;

	SDL_Texture* texture_unwalkable;
	SDL_Texture* texture_hero;

private:
	float tileSizeX;
	float tileSizeY;

	std::vector<SDL_Texture*> tileSetA;     // loaded sdl surfaces.
	std::vector<SDL_Texture*> tileSetB;
	std::vector<SDL_Texture*> tileSetC;
};
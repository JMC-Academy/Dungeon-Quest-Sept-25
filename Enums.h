#pragma once
enum Direction { North, East, South, West, Unknown = -1 };

static Direction Opposite(Direction dir) {
	if (dir == Direction::North) return Direction::South;
	if (dir == Direction::South) return Direction::North;
	if (dir == Direction::West) return Direction::East;
	if (dir == Direction::East) return Direction::West;
}

enum MoveResultAction 
{ 
	Undefined = -1,
	Blocked = 0,
	MoveOK = 1,
	Fight = 2,
	LoadNewRoom = 3
};
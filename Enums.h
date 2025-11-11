#pragma once
enum Direction { North, East, South, West };
enum MoveResultAction 
{ 
	Undefined = -1,
	Blocked = 0,
	MoveOK = 1,
	Fight = 2,
	LoadNewRoom = 3
};
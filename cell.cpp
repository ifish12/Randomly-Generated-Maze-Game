#include "cell.h"  

Cell:: Cell()
{
	for(int i = 0; i<4; i++)
	{
		sides[i]=true;
	}
	visited = false;
}
  

void Cell:: SetVisited()
{
	visited = true;
}


bool Cell:: GetVisited()
{
	return visited;
}

void Cell::SetSide(bool theSides, int side)
{
	sides[side] = theSides;
}

bool Cell::GetSide(int side)
{
	return sides[side];
}

void Cell::SetLocation(int xL, int yL)
{
	x = xL;
	y = yL;
}

int Cell::GetX()
{
	return x;
}

int Cell::GetY()
{
	return y;
}

bool Cell:: operator==(Cell aCell)
{
	if (x == aCell.x && y == aCell.y)
		return true;

	return false;
}


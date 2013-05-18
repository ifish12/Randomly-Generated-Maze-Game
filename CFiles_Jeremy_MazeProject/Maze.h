#ifndef _MAZE_
#define _MAZE_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <cstdio>
#include <windows.h>
#include "Cell.h"

class Maze
{
 private:
  Cell **maze;

 public:
  // Default Constructor
  Maze();

  Cell** CreateMaze(Cell **, int);
	void DeleteMaze(Cell **, int);
	Cell** GenerateMaze(Cell**, int);
	void Print(Cell **, int, Cell &, Cell);
	void PrintHidden(Cell **, int, Cell &, Cell);
	Cell Move(Cell **, int, Cell &);
	void Rave();
	void Play();

};

#endif




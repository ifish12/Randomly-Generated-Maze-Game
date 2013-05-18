
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <cstdio>
#include <windows.h>
#include "Cell.h"
#include "maze.h"


using namespace std;




Maze::Maze()
{

}

void Maze::Play()
{
	Cell **maze;
	int  size;
	int mode;
	Cell cPos;
	Cell endPos;

	srand (time(NULL));

	do
	{
		while(cout << "Please enter a size(5 to 20): " && !(cin  >> size))
		{
			cin.sync();
			cin.clear();
			cout << "Only numbers allowed" << endl;
		}
		cin.sync();
		cin.clear();
	}
	while(size < 5 || size > 20);
	do
	{
		while(cout << "Choose Game Mode(1 for Normal, 2 for Hidden...) " && !(cin  >> mode))
		{
			cin.sync();
			cin.clear();
			cout << "Enter Yes or No" << endl;
		}
		cin.sync();
		cin.clear();
		toupper(mode);
	}
	while(mode < 1 || mode > 2);

	maze = new Cell* [size];
	for(int i = 0; i < size; i++)
	{
		maze[i] = new Cell[size];
	}

	cPos.SetLocation(0,0);
	endPos.SetLocation(size-1,size-1);

	maze = CreateMaze(maze, size);
	maze = GenerateMaze(maze, size);
	while(!(cPos == endPos))
	{
		if ((mode == 1))
			Print(maze, size, cPos, endPos);
		if(mode == 2)
			PrintHidden(maze, size, cPos, endPos);
		cPos = Move(maze, size, cPos);
	}

	system("cls");
	
	cout << "YOU WIN!!";

	DeleteMaze(maze, size);
	while(true)
	{
		Rave();
	}
}

Cell** Maze::CreateMaze(Cell **maze, int size)
{

	for(int a = 0; a < size; a++)
	{
		for(int b = 0; b < size; b++)
		{
			maze[a][b].SetLocation(a,b);
		}
	}

	return maze;
}

void Maze::DeleteMaze(Cell **maze, int size)
{
	for (int i = 0; i < size; i++)
          {
            delete [] maze[i];
          }
          delete [] maze;
}

Cell** Maze::GenerateMaze(Cell **maze, int size)
{
	Cell *cp;
 	cp = new Cell [size*size];
	
	int totalCells = size*size;
	int currentCell = 1;
	int cellsVisited = 1;

	maze[0][0].SetVisited();
	cp[0] = maze[0][0];

	bool unVisited[4] = {true};
	int nUN = 0;
	int r;


	// 0= top, 1= right, 2= bot, 3= left
	while(cellsVisited < totalCells)
	{
		for(int i =0; i <4; i++)
		{
			unVisited[i] = true;
		}
		nUN = 0;

		if (cp[currentCell - 1].GetY() > 0)
			if(!maze[cp[currentCell-1].GetX()][cp[currentCell-1].GetY() -1].GetVisited())
			{
				unVisited[0] = false;
				nUN++;
			}

		if(cp[currentCell - 1].GetX() < (size -1))
			if(!maze[cp[currentCell-1].GetX()+1][cp[currentCell-1].GetY()].GetVisited())
			{
				unVisited[1] = false;
				nUN++;
			}

		if (cp[currentCell - 1].GetY() < (size -1))
			if(!maze[cp[currentCell-1].GetX()][cp[currentCell-1].GetY()+1].GetVisited())
			{
				unVisited[2] = false;
				nUN++;
			}

		if(cp[currentCell - 1].GetX() > 0)
			if(!maze[cp[currentCell-1].GetX()-1][cp[currentCell-1].GetY()].GetVisited())
			{
				unVisited[3] = false;
				nUN++;
			}

			if (nUN >0)
			{
				do
				{
					
					r = rand() %4;
				}
				while(unVisited[r]);
				
				if (r == 0)
				{
					maze[cp[currentCell-1].GetX()][cp[currentCell-1].GetY() -1].SetVisited();
					cp[currentCell] = maze[cp[currentCell-1].GetX()][cp[currentCell-1].GetY() -1];
					maze[cp[currentCell-1].GetX()][cp[currentCell-1].GetY()].SetSide(false, 0);
					maze[cp[currentCell].GetX()][cp[currentCell].GetY()].SetSide(false, 2);
				}
				else if (r == 1)
				{
					maze[cp[currentCell-1].GetX()+1][cp[currentCell-1].GetY()].SetVisited();
					cp[currentCell] = maze[cp[currentCell-1].GetX()+1][cp[currentCell-1].GetY()];					
					maze[cp[currentCell-1].GetX()][cp[currentCell-1].GetY()].SetSide(false, 1);
					maze[cp[currentCell].GetX()][cp[currentCell].GetY()].SetSide(false, 3);
				}
				else if (r == 2)
				{
					maze[cp[currentCell-1].GetX()][cp[currentCell-1].GetY()+1].SetVisited();
					cp[currentCell] = maze[cp[currentCell-1].GetX()][cp[currentCell-1].GetY()+1];
					maze[cp[currentCell-1].GetX()][cp[currentCell-1].GetY()].SetSide(false, 2);
					maze[cp[currentCell].GetX()][cp[currentCell].GetY()].SetSide(false, 0);
				}
				else if (r == 3)
				{
					maze[cp[currentCell-1].GetX()-1][cp[currentCell-1].GetY()].SetVisited();
					cp[currentCell] = maze[cp[currentCell-1].GetX()-1][cp[currentCell-1].GetY()];
					maze[cp[currentCell-1].GetX()][cp[currentCell-1].GetY()].SetSide(false, 3);
					maze[cp[currentCell].GetX()][cp[currentCell].GetY()].SetSide(false, 1);
				}
				
				
				currentCell++;
				cellsVisited++;
			}
			else
			{
				currentCell--;
			}

	}
		delete []cp;
		return maze;
}

void Maze::Print(Cell **maze, int size, Cell &cPos, Cell endPos)
{
	system("cls");
	char **walls;
	walls = new char* [size*2+1];
	for(int i = 0; i < size*2+1; i++)
	{
		walls[i] = new char[size*2+1];
	}

	for (int x = 0; x < size*2+1; x++)
		for (int y = 0; y < size*2+1; y++)
		{
			if(x % 2 == 0 && y % 2 == 0)
				walls[x][y] = '+';
			if(x % 2 == 1 && y % 2 == 1)
				walls[x][y] = ' ';
			if(x == 0 && y % 2 == 1)
				walls[x][y] = '-';
			if(y == 0 && x % 2 == 1)
				walls[x][y] = '|';
			if(x == size*2 && y % 2 == 1)
				walls[x][y] = '-';
			if(y == size*2 && x % 2 == 1)
				walls[x][y] = '|';
		}

	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
		{
			if(maze[x][y].GetSide(2))
			{
				walls[x*2+1][y*2+2] = '|';
			}
			else
			{
				walls[x*2+1][y*2+2] = ' ';
			}

			if(maze[x][y].GetSide(1))
			{
				walls[x*2+2][y*2+1] = '-';
			}
			else
			{
				walls[x*2+2][y*2+1] = ' ';
			}
		}

		walls[cPos.GetX()*2+1][cPos.GetY()*2+1] = 'X';
		walls[endPos.GetX()*2+1][endPos.GetY()*2+1] = 'G';

		for (int x = 0; x < size*2+1; x++)
		{
			for (int y = 0; y < size*2+1; y++)
			{
				cout << walls[x][y];
			}
			cout << endl;
		}
		
		for (int i = 0; i < size*2+1; i++)
          {
            delete [] walls[i];
          }
          delete [] walls;
}

Cell Maze::Move(Cell **maze, int size, Cell &cPos)
{

	int ch;

      ch = _getch();
  
      if ( ch == 80 )
	  {
			
		 if (!maze[cPos.GetX()][cPos.GetY()].GetSide(1))
			 {
			 cPos.SetLocation(cPos.GetX() + 1,cPos.GetY());
			 
			 return cPos;
			 }
			 return cPos;

		

	  }
      else if ( ch == 77 )
	  {
         
		
			 if (!maze[cPos.GetX()][cPos.GetY()].GetSide(2))
			 {
			 cPos.SetLocation(cPos.GetX(),cPos.GetY() + 1);
			 
			 return cPos;
			 }
			 return cPos;
	}
	  
	  else if ( ch == 75 )
	  {

		 if (!maze[cPos.GetX()][cPos.GetY()].GetSide(0))
			 {
			 cPos.SetLocation(cPos.GetX(),cPos.GetY() -1);
			  
			 return cPos;
			 }
			 return cPos;
		 
	  }
      else if ( ch == 72)
	  {
		
		 if (!maze[cPos.GetX()][cPos.GetY()].GetSide(3))
			 {
			 cPos.SetLocation(cPos.GetX() - 1,cPos.GetY());

			 return cPos;
			 }
			 return cPos;
	  }
 
   return cPos;


}

void Maze::PrintHidden(Cell **maze, int size, Cell &cPos, Cell endPos)
{
	int hide = 4;
	system("cls");
	char **walls;
	walls = new char* [size*2+1];
	for(int i = 0; i < size*2+1; i++)
	{
		walls[i] = new char[size*2+1];
	}

	for (int x = 0; x < size*2+1; x++)
		for (int y = 0; y < size*2+1; y++)
		{
			if(x % 2 == 0 && y % 2 == 0)
				walls[x][y] = '+';
			if(x % 2 == 1 && y % 2 == 1)
				walls[x][y] = ' ';
			if(x == 0 && y % 2 == 1)
				walls[x][y] = '-';
			if(y == 0 && x % 2 == 1)
				walls[x][y] = '|';
			if(x == size*2 && y % 2 == 1)
				walls[x][y] = '-';
			if(y == size*2 && x % 2 == 1)
				walls[x][y] = '|';
		}

	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
		{
			if(maze[x][y].GetSide(2))
			{
				walls[x*2+1][y*2+2] = '|';
			}
			else
			{
				walls[x*2+1][y*2+2] = ' ';
			}

			if(maze[x][y].GetSide(1))
			{
				walls[x*2+2][y*2+1] = '-';
			}
			else
			{
				walls[x*2+2][y*2+1] = ' ';
			}
		}

		walls[cPos.GetX()*2+1][cPos.GetY()*2+1] = 'X';
		walls[endPos.GetX()*2+1][endPos.GetY()*2+1] = 'G';

		for (int x = 0; x < size*2+1; x++)
		{
			for (int y = 0; y < size*2+1; y++)
			{
				
					if(((x < cPos.GetX()*2+1 + hide && x > cPos.GetX()*2+1 - hide) && (y > cPos.GetY()*2+1 - hide && y < cPos.GetY()*2+1 + hide)) || (x == endPos.GetX()*2+1 && y == endPos.GetY()*2+1))
					{
						cout << walls[x][y];
					}
					else
					{
						cout << " ";
					}
				
			}
			cout << endl;
		}
		
		for (int i = 0; i < size*2+1; i++)
          {
            delete [] walls[i];
          }
          delete [] walls;
}

void Maze::Rave()
{
	int r = rand() %12;

	switch(r)
	{
		
	case 1: system("color 1A");
		break;

	case 2: system("color 2B");
		break;

	case 3: system("color 3C");
		break;

	case 4: system("color 4D");
		break;

	case 5: system("color 5E");
		break;

	case 6: system("color 6F");
		break;

	case 7: system("color A1");
		break;

	case 8: system("color B2");
		break;

	case 9: system("color C3");
		break;

	case 10: system("color D4");
		break;

	case 11: system("color E5");
		break;

	case 0: system("color F6");
		break;
	}


}


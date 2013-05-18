#ifndef _CELL_
#define _CELL_

// 0= top, 1= right, 2= bot, 3= left

class Cell
{
 private:
  bool visited;
  bool sides[4];
  int x;
  int y;

 public:
  // Default Constructor
  Cell();

  void SetVisited();
  bool GetVisited();

  bool operator==(Cell);

  void SetSide(bool, int);
  bool GetSide(int);

  void SetLocation(int, int);
  int GetX();
  int GetY();

};

#endif

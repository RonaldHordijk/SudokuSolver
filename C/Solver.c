#include <stdio.h>
#include <stdbool.h>

int map[81] = {
5, 3, 0, 0, 7, 0, 0, 0, 0,
6, 0, 0, 1, 9, 5, 0, 0, 0,
0, 9, 8, 0, 0, 0, 0, 6, 0,
8, 0, 0, 0, 6, 0, 0, 0, 3,
4, 0, 0, 8, 0, 3, 0, 0, 1,
7, 0, 0, 0, 2, 0, 0, 0, 6,
0, 6, 0, 0, 0, 0, 2, 8, 0,
0, 0, 0, 4, 1, 9, 0, 0, 5,
0, 0, 0, 0, 8, 0, 0, 7, 9};

int Index(int x, int y) 
{
  return x + 9 * y;
}

void PrintSudoku(int m[])
{
  for (int y = 0; y < 9; y++)
  {
    for (int x = 0; x < 9; x++)
    {
      int v = m[Index(x, y)];
      if (v == 0)
      {
        printf(".");
      }
      else
      {
        printf("%d", v);
      }
    }
    printf("\n") ;
  }
}

bool colValueExists(int m[], int col, int value)
{
  for (int x = 0; x < 9; x++) {
    if (m[Index(x, col)] == value)
    {
      return true;
    }
  }

  return false;
}

bool rowValueExists(int m[], int row, int value)
{
  for (int y = 0; y < 9; y++) {
    if (m[Index(row, y)] == value)
    {
      return true;
    }
  }

  return false;
}

bool blockValueExists(int m[], int x, int y, int value)
{
  int xstart = x - (x % 3);
  int ystart = y - (y % 3);
  
  for (int y = ystart; y < ystart + 3; y++)
  {
    for (int x = xstart; x < xstart + 3; x++)
    {
      if (m[Index(x, y)] == value)
      {
        return true;
      }
    }
  }

  return false;
}


int getNextPossibleValue(int m[], int x, int y)
{
  int start = m[Index(x,y)];
  for( int v = start +1 ; v <= 9; v++)
  {
    if (colValueExists(m, y, v))
      continue;
    if (rowValueExists(m, x, v))
      continue;
    if (blockValueExists(m, x, y, v))
      continue;

    return v;
  }

  return -1; //no solution found
}

void Solve(int m[])
{
  int empties[2 * 81];
  int countEmpties = 0;

  for (int y = 0; y < 9; y++)
  {
    for (int x = 0; x < 9; x++)
    {
      int v = m[Index(x, y)];
      if (v == 0)
      {
        empties[2 * countEmpties] = x;
        empties[2 * countEmpties + 1] = y;
        countEmpties++;
      }
    }
  }

  int pos = 0;
  while (true) {
    int x = empties[2 * pos];
    int y = empties[2 * pos + 1];

    int val = getNextPossibleValue(m, x, y);

    if (val < 0) {
      m[Index(x,y)] = 0;
      pos--;
    } else {
      m[Index(x, y)] = val;
      pos++;
    }

    if (pos < 0) {
      printf("No solution found");
      return;
    }

    if (pos == countEmpties) {
      printf("Solution:\n");
      PrintSudoku(m);
      return;
    }
  }
}


int main()
{
  PrintSudoku(map);
  printf("\n");
  Solve(map);
}
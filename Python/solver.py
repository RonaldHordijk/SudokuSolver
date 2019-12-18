map = [[5,3,0,0,7,0,0,0,0],
[6,0,0,1,9,5,0,0,0],
[0,9,8,0,0,0,0,6,0],
[8,0,0,0,6,0,0,0,3],
[4,0,0,8,0,3,0,0,1],
[7,0,0,0,2,0,0,0,6],
[0,6,0,0,0,0,2,8,0],
[0,0,0,4,1,9,0,0,5],
[0,0,0,0,8,0,0,7,9]]


def print_sudoku(m):
  for x in range(9):
    s = ""
    for y in range(9):
      s += "." if (m[x][y] == 0) else str(m[x][y])
    print(s)


def get_empties(m):
  result = []
  for x in range(9):
    for y in range(9):
      if m[x][y] == 0:
        result.append((x,y))
  return result

def row_value_exists(m, row, value):
  for y in range(9):
    if m[row][y] == value:
      return True
  return False

def col_value_exists(m, col, value):
  for x in range(9):
    if m[x][col] == value:
      return True
  return False

def block_value_exists(m, x, y, value):
  xstart = x - (x % 3)
  ystart = y - (y % 3)
  for x in range(xstart, xstart + 3):
    for y in range(ystart, ystart + 3):
      if m[x][y] == value:
        return True
  return False

def get_next_possible_value(m, x, y):
  start = map[x][y]
  for v in range(start + 1, 10):
    if col_value_exists(m, y, v):
      continue
    if row_value_exists(m, x, v):
      continue
    if block_value_exists(m, x, y, v):
      continue
    return v

  return -1 # no solution found


def solve(m, empties):
  pos = 0
  while True:
    (x,y) = empties[pos]
    value = get_next_possible_value(m, x, y)
    if value < 0:
      map[x][y] = 0
      pos -= 1
    else:
      map[x][y] = value
      pos += 1

#    print(f"{pos}")
#    print_sudoku(map)

    if pos < 0:
      print("No solution found")
      return

    if pos == len(empties):
      print("Solution:")
      print_sudoku(map)
      return

def main():
  print_sudoku(map)
  empties = get_empties(map)
  solve(map, empties)

if __name__ == "__main__":
  main()
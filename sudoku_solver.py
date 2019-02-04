#!/nfs/site/disks/ch_icf_fdk_rcx_003/dkalra/virtual_env/pyenv/bin/python3.6.3a
import pycosat
import itertools
import argparse
import re
import pprint

def read_input(file):
  file = open(file, "r")
  board = []
  for line in file:
    line = line.rstrip()
    if (re.search(r'^\#', line) or len(line.strip()) == 0):
      continue
    line = [list(l) for l in line.split()]
    flat = [y for x in line for y in x]
    flat = [w.replace('-', '0') for w in flat]
    flat = [int(w) for w in flat]
    board.append(flat)
  return board

def print_sol(board,sol):
  sol = [x for x in sol if x > 0]
  for elem in sol:
    m = (elem%81)
    if m==0:
      n = int(elem/81)
      x = y = 8
    else:
      n = int(elem/81) + 1
      m = m -1
      x = int(m/9)
      y = m%9
    board[x][y] = n
    
def at_least_one(xs):
  return [xs]

def at_most_one(xs):
  minus_xs = [-x for x in xs]
  return list(itertools.combinations(minus_xs,2))

def all_of(xs):
  a = [[x] for x in xs]
  return a

def make_cell(x, y, n):
  cell = 9*x + y +1 +(n-1)*81
  return cell

def make_cnf(board): # n is the number for which building constraints
  cnf = []
  for n in range(1,10):
##Handling at_least_one and at_most one of 'n' in each row
    for j in range(9):
      row_j = [make_cell(j,i,n) for i in range(9)]
      cnf.extend(at_least_one(row_j))
      cnf.extend(at_most_one(row_j))

##Handling at_least_one and at_most one of 'n' in each column
      col_j = [make_cell(i,j,n) for i in range(9)]
      cnf.extend(at_least_one(col_j))
      cnf.extend(at_most_one(col_j))

##Handling at_least_one and at_most one of 'n' in each region
      reg_j = []
      a = int(j/3)*3
      b = int(j%3)*3
      reg_j = [make_cell(i, k, n) for i in range(a,a+3) for k in range(b,b+3)]
      cnf.extend(at_least_one(reg_j))
      cnf.extend(at_most_one(reg_j))

##Handling condition such that each cell only has one number between 0 and 9  
  for j in range(9):
    for i in range(9):
      cell = [make_cell(i,j,n+1) for n in range(9)]
      cnf.extend(at_least_one(cell))
      cnf.extend(at_most_one(cell))

##Asserting pre-populated cells  
  pre = [9*x + y + 1 + (board[x][y]-1)*81 for x in range(9) for y in range(9) if board[x][y] > 0]
  cnf.extend(all_of(pre))
  return cnf

if __name__ == '__main__':
  parser = argparse.ArgumentParser( description="Solves the 9X9 sudoku puzzles")
  parser.add_argument('file', nargs='?', default='easy.sd')
  args = parser.parse_args()
  board = read_input(args.file)
  print("Puzzle")
  pprint.pprint(board)

  cnf = make_cnf(board)
  result = pycosat.solve(cnf)
  print_sol(board,result)
  print("Solution")
  pprint.pprint(board)

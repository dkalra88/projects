board_size=8
board= []
pos_map= {"a":0,"b":1,"c":2,"d":3,"e":4,"f":5,"g":6,"h":7}

def initialize_board ():
	for i in range(0,board_size):
		board.append([0]*board_size)

def print_board (x=8,y=8): # format
  num_digits = len(str(x*y))
  field = '%' + str(num_digits) + 'd'
  print ' ' * (num_digits),
  for xi in range(0,x):
	print '',(pos_map.keys()[pos_map.values().index(xi)]),
  print
  for yi in range(0,y):
    print field % (y-yi),
    for xi in range(0,x):
      print field % board[xi][y-yi-1],
    print

def is_empty(pos):
	if board[pos[0]][pos[1]]==0:
		return True
	else:
		return False

def find_valid_moves(x,y):
	empty_valid_moves=[]
	legal_moves = [(1,2),(2,1),(1,-2),(2,-1),(-1,2),(-2,1),(-1,-2),(-2,-1)]
	for move in legal_moves:
		new_x = x + move[0] 
		new_y = y + move[1]
		if (new_x>board_size-1 or new_x<0 or new_y>board_size-1 or new_y<0):
			continue
		else:
			if is_empty((new_x,new_y)):
				empty_valid_moves.append((new_x,new_y))
	return empty_valid_moves

def move_knight (cur_x, cur_y, skip):
	temp_dict={}
  	all_empty_valid_moves=find_valid_moves(cur_x,cur_y)
	for pos in all_empty_valid_moves:
		temp_dict.update({(pos):len(find_valid_moves(pos[0],pos[1]))})
	sorted_empty_moves = sorted(temp_dict.items(), key = lambda x: x[1])
	for i in range(len(sorted_empty_moves)):
		if i >= skip:
			return sorted_empty_moves[i][0],i
	return (100,100),100 #assign constant as error value or return none,none

def convert_pos_to_cord (cur_pos):
	return pos_map[cur_pos[0]],int(cur_pos[1])-1

def convert_cord_to_pos (x,y):
	pos = (pos_map.keys()[pos_map.values().index(x)],str(y+1))
	return ''.join(pos)
	
if __name__ == '__main__': #less nouns
	skip=0
	total_moves=1
	travel_list=[]
#travel_dict={}
	cur_pos = raw_input('''Enter an alphabet from 'a' to 'h' and a number between 1 and 8. Eg. a1. What is your start position?  ''') # argparse
	if (cur_pos[0] not in pos_map) or (cur_pos[1] not in range(1,9)):
		print("Invalid move")
		print
#sys.exit #exit. Call a function return none or exception
	start_x,start_y=convert_pos_to_cord (cur_pos)
	initialize_board()
	board[start_x][start_y]=total_moves
	travel_list.append((convert_cord_to_pos(start_x,start_y)))
	cur_x,cur_y = start_x,start_y
	while total_moves <= board_size*board_size :
		(new_x,new_y),pos_sort=move_knight(cur_x,cur_y,skip)
		if new_x!=100:
			total_moves+=1
			board[new_x][new_y]=total_moves
			travel_list.append((convert_cord_to_pos(new_x,new_y)))
			cur_x,cur_y=new_x,new_y
			skip=0
		else:
			break

print "Total moves:", total_moves
print travel_list
print_board()

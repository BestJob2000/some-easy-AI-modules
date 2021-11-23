import copy
board=[[0 for i in range(3)] for i in range(3)]    #human=1 pc=2
av_moves=[i for i in range(0,9)]
depth=99
def check(board):
   for i in range(0,3):
      if board[i][0]==board[i][1] and board[i][1]==board[i][2]:   #line
         if board[i][0]==1:
            return 1
         if board[i][0]==2:
            return 2
      if board[0][i]==board[1][i] and board[1][i]==board[2][i]:   #row
         if board[0][i]==1:
            return 1
         if board[0][i]==2:
            return 2
   if board[0][0]==board[1][1] and board[1][1]==board[2][2]:   #dia
         if board[1][1]==1:
            return 1
         if board[1][1]==2:
            return 2
   if board[0][2]==board[1][1] and board[1][1]==board[2][0]:   #anti-dia
         if board[1][1]==1:
            return 1
         if board[1][1]==2:
            return 2
   if isfull(board):
      return 3          #draw
   return 0
def show(board):
   for i in range(0,3):
      print("|",end="")
      for j in range(0,3):
         print(board[i][j],end="|")
      print("")
   print()

def move(board,this_move,player):
   this_board=copy.deepcopy(board)
   i=int(this_move/3)
   j=this_move%3
   this_board[i][j]=player
   return this_board

def eval(board):
   if check(board)==2:
      return 99
   if check(board)==1:
      return -99
   if check(board)==3:
      return 0
   pc_holds=0
   human_holds=0
   for i in range(0,3):    
      tmp_lines=[]         #lines
      tmp_rows=[]          #rows
      tmp_lines.append(board[i][0])
      tmp_lines.append(board[i][1])
      tmp_lines.append(board[i][2])
      tmp_rows.append(board[0][i])
      tmp_rows.append(board[1][i])
      tmp_rows.append(board[2][i])
      if (1 not in tmp_lines) and (2 in tmp_lines):
         pc_holds+=1
      elif (2 not in tmp_lines) and (1 in tmp_lines):
         human_holds+=1
      if (1 not in tmp_rows) and (2 in tmp_rows):
         pc_holds+=1
      elif (2 not in tmp_rows) and (1 in tmp_rows):
         human_holds+=1
   tmp_dia=[board[0][0],board[1][1],board[2][2]]
   tmp_antidia=[board[0][2],board[1][1],board[2][0]]
   if (1 not in tmp_dia) and (2 in tmp_dia):
         pc_holds+=1
   elif (2 not in tmp_dia) and (1 in tmp_dia):
         human_holds+=1
   if (1 not in tmp_antidia) and (2 in tmp_dia):
         pc_holds+=1
   elif (2 not in tmp_antidia) and (1 in tmp_dia):
         human_holds+=1
   return (pc_holds-human_holds)*10

def isfull(board):
   for i in range(0,3):
      for j in range(0,3):
         if board[i][j]==0:
            return False
   return True

def minMax(board,player,layer,av,alpha,beta):
   if check(board)!=0:
      return eval(board)
   if player==1:     #human moves
      for i in av:
         av_1=copy.deepcopy(av)
         av_1.remove(i)
         tmp=minMax(move(board,i,1),2,layer+1,av_1,alpha,beta)
         if tmp<beta:
            beta=tmp
         if beta<=alpha:
            return alpha
      return beta

   if player==2:     #computer moves
      for i in av:
         av_1=copy.deepcopy(av)
         av_1.remove(i)
         tmp=minMax(move(board,i,2),1,layer+1,av_1,alpha,beta)
         if tmp>alpha:
            alpha=tmp
         if alpha>=beta:
            return beta
      return alpha

def computer_moves(board):
   pcmoves=-1
   max=-99
   for i in av_moves:
      av_moves_1=copy.deepcopy(av_moves)
      av_moves_1.remove(i)
      tmp=minMax(move(board,i,2),1,0,av_moves_1,-99,99)
      print("choice: "+str(i)+" eval:"+str(tmp))
      if tmp>max:
         pcmoves=i
         max=tmp
   print("eval:"+str(max))
   return pcmoves


#main
print("your moves:")
print("|0|1|2|")
print("|3|4|5|")
print("|6|7|8|")
print("===============")
print("game start")
show(board)
while(check(board)==0):
   human_moves=-1
   while(human_moves not in av_moves):
      print(av_moves)
      human_moves=int(input("Your move:"))
   board=move(board,human_moves,1)
   av_moves.remove(human_moves)
   if check(board)!=0:
      break
   show(board)
   pc_moves=computer_moves(board)
   print("computer choice"+str(pc_moves))
   board=move(board,pc_moves,2)
   av_moves.remove(pc_moves)
   show(board)
show(board)
if check(board)==1:
   print("Player wins")
elif check(board)==2:
   print("Computer wins")
else:
   print("Draw!")



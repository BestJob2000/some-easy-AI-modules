#0 up 1 down 2 left 3 right
First=[[0,0,0,0,0][0,2,0,3,0],[0,1,8,4,0],[0,7,6,5,0],[0,0,0,0,0]]
target=[[0,0,0,0,0][0,1,2,3,0],[0,8,0,4,0],[0,7,6,5,0],[0,0,0,0,0]]
def swap(last,move,pos_x,pos_y):
    if move==0:
      last[pos_x][pos_y]
   else if move==1:
   else if move==2:
   else if move==3: 

def dfs(last,move,pos_x,pos_y):
   if move==0:
      if last[pos_x-1][pos_y]!=0:
         swap(last,0)
   else if move==1:
   else if move==2:
   else if move==3:

   if last==target:
      return True
   else:
         if(move==0):
            if(dfs(last,0,pos_x,pos_y) or dfs(last,2,pos_x,pos_y) or dfs(last,3,pos_x,pos_y)):
               return True
            else: return False
         if(move==0):
            if(dfs(last,0,pos_x,pos_y) or dfs(last,2,pos_x,pos_y) or dfs(last,3,pos_x,pos_y)):
               return True
            else: return False
         if(move==0):
            if(dfs(last,0,pos_x,pos_y) or dfs(last,2,pos_x,pos_y) or dfs(last,3,pos_x,pos_y)):
               return True
            else: return False
         if(move==0):
            if(dfs(last,0,pos_x,pos_y) or dfs(last,2,pos_x,pos_y) or dfs(last,3,pos_x,pos_y)):
               return True
            else: return False


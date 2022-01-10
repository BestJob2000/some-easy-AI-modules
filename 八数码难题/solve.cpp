#include <cstdio>
struct node{ int map[5][5],wi,wj,t; } bfs_queue[1000001]; //x，y位置 t步数
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int target[5][5]={0,0,0,0,0,
            0,1,2,3,0,
            0,8,0,4,0,
            0,7,6,5,0,
            0,0,0,0,0};
int dfs_steps,putin,bfs_steps;
int bfs_back[100];//bfs前序
node dfs_ans[100];//dfs回溯数组
int bfs_ans[100];//bfs回溯数组

bool check(node move){
   for(int i=1;i<=3;i++)
   {
      for(int j=1;j<=3;j++)
      {
            if(move.map[i][j]!=target[i][j])
            {
               return false;
            }
      }
   }
   return true;
}

void bfs()
{
   int head=1,tail=2;
   while(head<tail)
   {
      if(check(bfs_queue[head])==true)
      {
            bfs_steps=bfs_queue[head].t;
            printf("BFS steps %d",bfs_queue[head].t);
            int b=head;
            bfs_ans[bfs_steps]=head;
            for(int m=bfs_steps-1;m>=0;m--){
               bfs_ans[m]=bfs_back[b];
               b=bfs_back[b];
            }
            return ;
      }
      for(int i=0;i<=3;i++)
      {
            int nx=bfs_queue[head].wi+dx[i];
            int ny=bfs_queue[head].wj+dy[i];
            if(nx>=1 && nx<=3 && ny>=1 && ny<=3) //交换点位置合规
            {
               for(int j=1;j<=3;j++)
               {
                  for(int k=1;k<=3;k++)
                  {
                        bfs_queue[tail].map[j][k]=bfs_queue[head].map[j][k];
                        bfs_back[tail]=head;
                  }
               }
               bfs_queue[tail].map[bfs_queue[head].wi][bfs_queue[head].wj]=bfs_queue[head].map[nx][ny];
               bfs_queue[tail].map[nx][ny]=0;        //空格位置
               bfs_queue[tail].t=bfs_queue[head].t+1;        //步数+1
               bfs_queue[tail].wi=nx;                // 新的x、y位置
               bfs_queue[tail].wj=ny;
               tail++;
            }
      }
      head++;
   }
}

bool dfs(node move)
{
   if(move.t>5) return false;
   if(check(move)==true)
   {
      dfs_steps=move.t;
      putin=move.t;
      for(int j=1;j<=3;j++){
         for(int k=1;k<=3;k++){
               dfs_ans[putin].map[j][k]=move.map[j][k];
         }
      }
      putin--;
      return true;
   }
   node newmove;
   for(int i=0;i<=3;i++)      //不同分支
   {
      int nx=move.wi+dx[i];
      int ny=move.wj+dy[i];
      if(nx>=1 && nx<=3 && ny>=1 && ny<=3) //交换点位置合规
      {
         for(int j=1;j<=3;j++)
         {
            for(int k=1;k<=3;k++)
            {
                  newmove.map[j][k]=move.map[j][k];
            }
         }
         newmove.map[move.wi][move.wj]=move.map[nx][ny];
         newmove.map[nx][ny]=0;        //空格位置
         newmove.t=move.t+1;        //步数
         newmove.wi=nx;                // 新的x、y位置
         newmove.wj=ny;
      }
      if (dfs(newmove)==true){
         for(int j=1;j<=3;j++){
         for(int k=1;k<=3;k++){
               dfs_ans[putin].map[j][k]=move.map[j][k];
         }
         }
         putin--;
         return true;
      }
   }
   return false;
}

int main()
{
   node first_dfs;
   for(int i=1;i<=3;i++)
   {
      for(int j=1;j<=3;j++)
      {
            char ch;
            scanf("%c",&ch);
            bfs_queue[1].map[i][j]=ch-'0';
            first_dfs.map[i][j]=ch-'0';
            if(bfs_queue[1].map[i][j]==0)
            {
               bfs_queue[1].t=0;
               bfs_queue[1].wi=i;
               bfs_queue[1].wj=j;
               first_dfs.t=0;
               first_dfs.wi=i;
               first_dfs.wj=j;
            }
      }
   }
   bfs();                        //bfs
   for(int m=0;m<=bfs_steps;m++){
      printf("\nstep %d\n",m);
      for(int j=1;j<=3;j++){
         for(int k=1;k<=3;k++){
            printf("%d ",bfs_queue[bfs_ans[m]].map[j][k]);
         }
         printf("\n");
      }
      printf("\n\n");
   }


   dfs(first_dfs);                  //dfs
   printf("\ndfs steps %d",dfs_steps);
   for(int i=0;i<=dfs_steps;i++){         //show steps
      printf("\nstep %d\n",i);
      for(int j=1;j<=3;j++){
         for(int k=1;k<=3;k++){
            printf("%d ",dfs_ans[i].map[j][k]);
         }
         printf("\n");
      }
      printf("\n\n");
   }
   return 0;
}
//283104765
//203184765
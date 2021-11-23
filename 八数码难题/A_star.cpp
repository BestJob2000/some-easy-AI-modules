#include <cstdio>
#include<queue>
#include<algorithm>
struct node{ int map[5][5],wi,wj,step,eval,pre; } star_queue[1000001]; //x，y位置 t步数
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int target[5][5]={0,0,0,0,0,
            0,1,2,3,0,
            0,8,0,4,0,
            0,7,6,5,0,
            0,0,0,0,0};
int star_steps;
int star_ans[100];//bfs回溯数组

bool check(node move){
   for(int i=1;i<=3;i++){for(int j=1;j<=3;j++){
      if(move.map[i][j]!=target[i][j]) return false;
      }}
   return true;
}

int h1(int move[5][5]){
   int result=0;
   for(int i=1;i<=3;i++){for(int j=1;j<=3;j++){
      if(move[i][j]!=target[i][j]) result++;
   }}
   return result;
}

int h2(int move[5][5]){
   int result=0;
   for(int i=1;i<=3;i++){for(int j=1;j<=3;j++){
      if(move[i][j]!=target[i][j]) {
			switch(move[i][j]){
			case 1: result+=abs(i-1)+abs(j-1);break;
			case 2: result+=abs(i-1)+abs(j-2);break;
			case 3: result+=abs(i-1)+abs(j-3);break;
			case 4: result+=abs(i-2)+abs(j-1);break;
			case 5: result+=abs(i-2)+abs(j-3);break;
			case 6: result+=abs(i-3)+abs(j-1);break;
			case 7: result+=abs(i-3)+abs(j-2);break;
			case 8: result+=abs(i-3)+abs(j-3);break;
			}76y7
		}
   }}
   return result;
}

void order(node queue[1000001],int head,int tail){
	int min_eval=999;
	int min_pos=head;
	for(int i=head;i<tail;i++)
		if(queue[i].eval<min_eval){
			min_eval=queue[i].eval;
			min_pos=i;
		}
	node tmp;
	for(int i=1;i<=3;i++){for(int j=1;j<=3;j++){
      tmp.map[i][j]=queue[head].map[i][j];
   }}
	tmp.eval=queue[head].eval;
	tmp.step=queue[head].step;
	tmp.wi=queue[head].wi;
	tmp.wj=queue[head].wj;
	tmp.pre=queue[head].pre;

	for(int i=1;i<=3;i++){for(int j=1;j<=3;j++){
      queue[head].map[i][j]=queue[min_pos].map[i][j];
   }}
	queue[head].eval=queue[min_pos].eval;
	queue[head].step=queue[min_pos].step;
	queue[head].wi=queue[min_pos].wi;
	queue[head].wj=queue[min_pos].wj;
	queue[head].pre=queue[min_pos].pre;

	for(int i=1;i<=3;i++){for(int j=1;j<=3;j++){
      queue[min_pos].map[i][j]=tmp.map[i][j];
   }}
	queue[min_pos].eval=tmp.eval;
	queue[min_pos].step=tmp.step;
	queue[min_pos].wi=tmp.wi;
	queue[min_pos].wj=tmp.wj;
	queue[min_pos].pre=tmp.pre;
}

void A_star()
{
   int head=1,tail=2;
   while(head<tail)
   {
      if(check(star_queue[head])==true)
      {
            star_steps=star_queue[head].step;
            printf("A Star steps %d",star_queue[head].step);
            int b=head;
            star_ans[star_steps]=head;
            for(int m=star_steps-1;m>=0;m--){
               star_ans[m]=star_queue[star_ans[m+1]].pre;
            }
            return ;
      }
      for(int i=0;i<=3;i++)
      {
            int nx=star_queue[head].wi+dx[i];
            int ny=star_queue[head].wj+dy[i];
            if(nx>=1 && nx<=3 && ny>=1 && ny<=3) //交换点位置合规
            {
					int newnode[5][5];
               for(int j=1;j<=3;j++){for(int k=1;k<=3;k++){
                  newnode[j][k]=star_queue[head].map[j][k];
               }}
					newnode[star_queue[head].wi][star_queue[head].wj]=star_queue[head].map[nx][ny];
					newnode[nx][ny]=0;
               if(h2(newnode)+star_queue[head].step<star_queue[head].eval){
						for(int j=1;j<=3;j++){for(int k=1;k<=3;k++){
						star_queue[tail].map[j][k]=newnode[j][k];}}
						star_queue[tail].step=star_queue[head].step+1;
						star_queue[tail].eval=h2(newnode)+star_queue[head].step+1;
						star_queue[tail].wi=nx;                // 新的x、y位置
                  star_queue[tail].wj=ny;
						star_queue[tail].pre=head;
						tail++;
					}
            }
      }
      head++;
		order(star_queue,head,tail);
   }
	printf("NO ANSWER %d %d\n",head,tail);
}

int main()
{
   for(int i=1;i<=3;i++)
   {
      for(int j=1;j<=3;j++)
      {
            char ch;
            scanf("%c",&ch);
            star_queue[1].map[i][j]=ch-'0';
            if(star_queue[1].map[i][j]==0)
            {
               star_queue[1].step=0;
               star_queue[1].wi=i;
               star_queue[1].wj=j;
					star_queue[1].eval=h2(star_queue[1].map);
					star_queue[1].pre=0;
            }
      }
   }
   A_star();                        //A star
   for(int m=0;m<=star_steps;m++){
      printf("\nstep %d\n",m);
      for(int j=1;j<=3;j++){
         for(int k=1;k<=3;k++){
            printf("%d ",star_queue[star_ans[m]].map[j][k]);
         }
         printf("\n");
      }
      printf("\n");
   }
   return 0;
}
//283104765
//203184765
//867254301
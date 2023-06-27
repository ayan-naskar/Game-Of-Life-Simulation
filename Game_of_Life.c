#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>
#include<windows.h>
#include<math.h>
#include<time.h>

#define N 100
typedef struct world wor;

struct world{
	int wd[N][N],size;
};

wor* initialize(int n){
	int i,j;
	wor *p=(wor*)malloc(sizeof(wor));
	p->size=n;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			p->wd[i][j]=0;
	return p;
}

void fillRandomPoints(wor *p){
	int n=p->size,i,j;
	srand(time(NULL));
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(rand()%3==1)
				p->wd[i][j]=1;
}

int countneighbours(wor *p,int a, int b){
	int c=0,i=a-1,j=b-1,n=p->size,x,y;
	for(;i<=a+1;i++){
		for(j=b-1;j<=b+1;j++){
			x=i;y=j;
			if(x==-1)x=n-1;
			if(x==n)x=0;
			if(y==-1)y=n-1;
			if(y==n)y=0;

			if(p->wd[x][y]==1){
				c++;
			}
		}
	}
	if(p->wd[a][b])
		c--;
	//if(c==-1) printf("\npab=%d\n",p->wd[a][b]);
	return c;
}

wor* findNextGen(wor *p){
	int n=p->size,i,j,count;
	wor *nextgen=initialize(n);
	puts("");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			count=countneighbours(p,i,j);
			//printf("%d ",count);
			//nextgen->wd[i][j]=count;
			if(   ((count==2 || count==3) && p->wd[i][j])   ||   (count==3 && !p->wd[i][j])   )
				nextgen->wd[i][j]=1;
		}
		puts("");
	}
	return nextgen;
}

void show(wor *p){
	int n=p->size,i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			if(p->wd[i][j])
				printf("x ");//,p->wd[i][j]);
			else printf("  ");
		puts("");
	}
}

void simulate(wor *p){
	wor *nextgen;
	while(1){
		nextgen=findNextGen(p);

		system("cls");
		//puts("\n");
		show(nextgen);
		Sleep(200);

		free(p);
		p=nextgen;
		//getch();
	}
}

void fillspaceship(wor *p){
	p->wd[6][6+10]=p->wd[7][7+10]=p->wd[7][8+10]=p->wd[8][6+10]=p->wd[8][7+10]=1;
}

int main(){
	int n=20;
	wor* p=initialize(n);
	//fillRandomPoints(p);
	fillspaceship(p);

	show(p);
	Sleep(200);
	//getch();
	simulate(p);
}
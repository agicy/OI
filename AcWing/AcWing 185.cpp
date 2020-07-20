#include<bits/stdc++.h>
using namespace std;
#define reg register

struct Operation{
	int x,y,dir;
	inline Operation(void){
		x=y=dir=0;
		return;
	}
	inline Operation(reg int a,reg int b,reg int c){
		x=a,y=b,dir=c;
		return;
	}
	inline void Print(void){
		printf("%d %d %d\n",x,y,dir);
		return;
	}
	inline bool operator==(const Operation& a)const{
		return x==a.x&&y==a.y&&dir==a.dir;
	}
};

struct Chess{
	int M[7+10][5+10];
	bool d[7+10][5+10];
	inline void Print(void){
		for(reg int i=1;i<=7;++i)
			for(reg int j=1;j<=5;++j)
				printf("%d%c",M[i][j],j==5?'\n':' ');
		putchar('\n');
		return;
	}
	inline void Grav(void){
		for(reg int i=6;i>=1;--i)
			for(reg int j=1;j<=5;++j)
				if(M[i][j]&&M[i+1][j]==0){
					reg int pos=i;
					while(pos<=6&&M[pos+1][j]==0){
						swap(M[pos][j],M[pos+1][j]);
						++pos;
					}
				}
		return;
	}
	inline bool Del(void){
		reg bool flag=false;
		for(reg int i=1;i<=7;++i)
			for(reg int j=1;j<=5;++j){
				if(M[i][j]&&i-1>=1&&i+1<=7&&M[i-1][j]==M[i][j]&&M[i+1][j]==M[i][j])
					flag=d[i-1][j]=d[i][j]=d[i+1][j]=true;
				if(M[i][j]&&j-1>=1&&j+1<=5&&M[i][j-1]==M[i][j]&&M[i][j+1]==M[i][j])
					flag=d[i][j-1]=d[i][j]=d[i][j+1]=true;
			}
		for(reg int i=1;i<=7;++i)
			for(reg int j=1;j<=5;++j)
				if(d[i][j])
					M[i][j]=d[i][j]=0;
		return flag;
	}
	inline void doOpt(reg int x,reg int y,reg int dir){
		swap(M[x][y+dir],M[x][y]);
		Grav();
		while(Del())
			Grav();
		return;
	}
	inline bool check(void){
		for(reg int i=1;i<=5;++i)
			if(M[7][i])
				return false;
		return true;
	}
};

const int MAXN=5+5;

int n;
Chess st;
Operation A[MAXN];

inline void Print(void);
inline void DFS(Chess,reg int);

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=5;++i){
		reg int pos=7;
		static int temp;
		do{
			scanf("%d",&temp);
			st.M[pos--][i]=temp;
		}while(temp!=0);
	}
	DFS(st,0);
	puts("-1");
	return 0;
}

inline void Print(void){
	for(reg int i=0;i<n;++i)
		A[i].Print();
	return;
}

inline void DFS(Chess now,reg int dep){
	Chess temp;
	if(dep==n){
		if(now.check()){
			Print();
			exit(0);
		}
		return;
	}
	for(reg int x=1;x<=5;++x)
		for(reg int y=1;y<=7;++y){
			reg int i=7-y+1,j=x;
			if(now.M[i][j])
				if(1<=j&&j<=4&&now.M[i][j]!=now.M[i][j+1]){
					temp=now;
					temp.doOpt(i,j,1);
					A[dep]=Operation(x-1,y-1,1);
					DFS(temp,dep+1);
				}
			if(2<=j&&j<=5&&now.M[i][j-1]==0){
				temp=now;
				temp.doOpt(i,j,-1);
				A[dep]=Operation(x-1,y-1,-1);
				DFS(temp,dep+1);
			}
		}
	return;
}

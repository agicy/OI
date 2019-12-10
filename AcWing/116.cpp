#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=4+5;

int ans=MAXSIZE*MAXSIZE;
bool ansq[MAXSIZE][MAXSIZE];
bool vis[MAXSIZE][MAXSIZE];
bool M[MAXSIZE][MAXSIZE];
bool temp[MAXSIZE][MAXSIZE];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	for(reg int i=1;i<=4;++i)
		for(reg int j=1;j<=4;++j){
			static char x;
			cin>>x;
			M[i][j]=(x=='+');
		}
	return;
}

inline void Update(reg int x,reg int y){
	for(reg int i=1;i<=4;++i){
		temp[x][i]=!temp[x][i];
		temp[i][y]=!temp[i][y];
	}
	temp[x][y]=!temp[x][y];
	return;
}

inline void Work(void){
	for(reg int i=0;i<(1<<16);++i){
		int res=0;
		memset(vis,false,sizeof(vis));
		memcpy(temp,M,sizeof(M));
		int q=1,p=0;
		for(reg int j=0;j<16;++j){
			++p;
			if(p==5)
				++q,p=1;
			if(i>>j&1)
				vis[q][p]=true;
		}
		for(reg int i=1;i<=4;++i)
			for(reg int j=1;j<=4;++j)
				if(vis[i][j]){
					++res;
					Update(i,j);
				}
		reg bool flag=true;
		for(reg int i=1;i<=4&&flag;++i)
			for(reg int j=1;j<=4&&flag;++j)
				if(temp[i][j])
					flag=false;
		if(flag&&res<ans){
			ans=res;
			memcpy(ansq,vis,sizeof(vis));
		}
	}
	printf("%d\n",ans);
	for(reg int i=1;i<=4;++i)
		for(reg int j=1;j<=4;++j)
			if(ansq[i][j])
				printf("%d %d\n",i,j);
	return;
}

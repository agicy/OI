#pragma GCC optimize (2)
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define lowbit(x) ( (x) & ( - (x) ) )

const int SIZE=16;
const int CSIZE=4;

int cnt[1<<SIZE];
int GetLog[1<<SIZE];

inline void Init(void){
	for(reg int i=0;i<(1<<SIZE);++i)
		for(reg int j=i;j;j-=lowbit(j))
			++cnt[i];
	for(reg int i=0;i<SIZE;++i)
		GetLog[1<<i]=i;
	return;
}

struct Node{
	int num[SIZE][SIZE];
	int l[SIZE],r[SIZE],ch[SIZE];
	int L[SIZE],R[SIZE],CH[SIZE];
	inline int GetID(reg int a,reg int b){
		return a/CSIZE*CSIZE+b/CSIZE;
	}
	inline void Change(reg int i,reg int j,reg int x){
		l[i]^=(1<<x);
		r[j]^=(1<<x);
		ch[GetID(i,j)]^=(1<<x);
		L[i]^=(1<<x);
		R[j]^=(1<<x);
		CH[GetID(i,j)]^=(1<<x);
		return;
	}
	inline int GetCan(reg int i,reg int j){
		return l[i]&r[j]&ch[GetID(i,j)];
	}
	inline int GetCnt(reg int i,reg int j){
		if(num[i][j]!=-1)
			return SIZE;
		else
			return cnt[GetCan(i,j)];
	}
	inline void draw(reg int i,reg int j,reg int x){
		num[i][j]=x;
		Change(i,j,x);
		return;
	}
	inline int Read(void){
		reg int res=0;
		for(reg int i=0;i<SIZE;++i){
			l[i]=r[i]=ch[i]=(1<<SIZE)-1;
			L[i]=R[i]=CH[i]=0;
		}
		static char str[SIZE+SIZE];
		for(reg int i=0;i<SIZE;++i){
			if(scanf("%s",str)==EOF)
				exit(0);
			for(reg int j=0;j<SIZE;++j){
				switch(str[j]){
					case '-':
						++res;
						num[i][j]=-1;
						break;
					default:
						num[i][j]=str[j]-'A';
						Change(i,j,num[i][j]);
						break;
				}
			}
		}
		return res;
	}
	inline void Print(void){
		for(reg int i=0;i<SIZE;++i,putchar('\n'))
			for(reg int j=0;j<SIZE;++j)
				putchar(num[i][j]+'A');
		putchar('\n');
		return;
	}
};

int n;
Node a;

inline bool DFS(reg int dep,Node a){
	if(dep==0){
		a.Print();
		return true;
	}
	for(reg int i=0;i<SIZE;++i)
		for(reg int j=0;j<SIZE;++j){
			if(a.GetCnt(i,j)==0&&a.num[i][j]==-1)
				return false;
			if(a.GetCnt(i,j)==1){
				a.draw(i,j,GetLog[a.GetCan(i,j)]);
			}
		}
	for(reg int i=0;i<SIZE;++i){
		for(reg int j=0;j<SIZE;++j){
			if((a.L[i]&(1<<j))==0&&((1<<j)&a.l[i])==0){
				return false;
			}
		}
	}
	for(reg int i=0;i<SIZE;++i){
		for(reg int j=0;j<SIZE;++j){
			if((a.R[i]&(1<<j))==0&&((1<<j)&a.r[i])==0){
				return false;
			}
		}
	}
	for(reg int i=0;i<SIZE;++i){
		for(reg int j=0;j<SIZE;++j){
			if((a.CH[i]&(1<<j))==0&&((1<<j)&a.ch[i])==0){
				return false;
			}
		}
	}
/*
	for(reg int i=0;i<SIZE;++i)
		for(reg int j=0;j<SIZE;++j)
			if(a.Get(i,j)==0)
				return false;
	for(reg int i=0;i<SIZE;++i)
		for(reg int j=0;j<SIZE;++j)
			if(a.Get(j,i)==0)
				return false;*/
	reg int Min=SIZE,posx=-1,posy=-1;
	for(reg int i=0;i<SIZE;++i)
		for(reg int j=0;j<SIZE;++j){
			if(a.GetCnt(i,j)==0&&a.num[i][j]==-1)
				return false;
			if(a.GetCnt(i,j)<Min){
				Min=a.GetCnt(i,j);
				posx=i,posy=j;
				//a.draw(i,j,GetLog[a.GetCan(i,j)]);
			}
		}
	if(posx==-1&&posy==-1)
		return false;
	reg int k=a.GetCan(posx,posy);
	while(k){
		a.Change(posx,posy,GetLog[lowbit(k)]);
		a.num[posx][posy]=GetLog[lowbit(k)];
		if(DFS(dep-1,a))
			return true;
		a.num[posx][posy]=-1;
		a.Change(posx,posy,GetLog[lowbit(k)]);
		k-=lowbit(k);
	}
	return false;
}

int main(void){
	Init();
	while(true){
		n=a.Read();
		printf("%d\n",n);
		DFS(n,a);
		printf("%d\n",n);
	}
	return 0;
}

#pragma GCC optimize (2)
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define lowbit(x) ( (x) & ( - (x) ) )

const int SIZE=9;
const int CSIZE=3;

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
	inline int GetID(reg int a,reg int b){
		return a/CSIZE*CSIZE+b/CSIZE;
	}
	inline void Change(reg int i,reg int j,reg int x){
		l[i]^=(1<<x);
		r[j]^=(1<<x);
		ch[GetID(i,j)]^=(1<<x);
		return;
	}
	inline int GetC(reg int i,reg int j){
		return l[i]&r[j]&ch[GetID(i,j)];
	}
	inline int Get(reg int i,reg int j){
		if(num[i][j]!=-1)
			return SIZE;
		else
			return cnt[GetC(i,j)];
	}
	inline int Read(void){
		reg int res=0;
		for(reg int i=0;i<SIZE;++i)
			l[i]=r[i]=ch[i]=(1<<SIZE)-1;
		static char str[SIZE*SIZE+SIZE];
		if(scanf("%s",str)==EOF||str[0]=='e')
			exit(0);
		for(reg int i=0;i<SIZE;++i){
			for(reg int j=0;j<SIZE;++j){
				switch(str[i*SIZE+j]){
					case '.':
						++res;
						num[i][j]=-1;
						break;
					default:
						num[i][j]=str[i*SIZE+j]-'0'-1;
						Change(i,j,num[i][j]);
						break;
				}
			}
		}
		return res;
	}
	inline void Print(void){
		for(reg int i=0;i<SIZE;++i)
			for(reg int j=0;j<SIZE;++j)
				putchar('0'+num[i][j]+1);
				//printf("%d",num[i][j]+1);
		putchar('\n');
		return;
	}
};

int n;
Node a;


inline bool DFS(reg int dep,Node &a){
	if(dep==0){
		a.Print();
		return true;
	}
	reg int Min=SIZE,posx=-1,posy=-1;
	for(reg int i=0;i<SIZE;++i)
		for(reg int j=0;j<SIZE;++j){
			if(a.Get(i,j)==0){
				return false;
			}
			if(Min>a.Get(i,j)){
				Min=a.Get(i,j);
				posx=i,posy=j;
			}
		}
	if(posx==-1&&posy==-1)
		return false;
	reg int k=a.GetC(posx,posy);
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
		DFS(n,a);
	}
	return 0;
}

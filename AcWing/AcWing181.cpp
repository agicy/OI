#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=24;

const int M[8]={6,7,8,11,12,15,16,17};
const char ch[]="ABCDEFGH";
const int opps[]={5,4,7,6,1,0,3,2};
const int op[8][7]={
	{ 0, 2, 6,11,15,20,22},
	{ 1, 3, 8,12,17,21,23},
	{10, 9, 8, 7, 6, 5, 4},
	{19,18,17,16,15,14,13},
	{23,21,17,12, 8, 3, 1},
	{22,20,15,11, 6, 2, 0},
	{13,14,15,16,17,18,19},
	{ 4, 5, 6, 7, 8, 9,10}
};

struct Node{
	int a[24];
	inline void read(void){
		scanf("%d",&a[0]);
		if(!a[0])
			exit(0);
		for(reg int i=1;i<24;++i)
			scanf("%d",&a[i]);
		return;
	}
	inline int getVal(void){
		static int T[4];
		T[1]=T[2]=T[3]=0;
		for(reg int i=0;i<8;++i)
			++T[a[M[i]]];
		return 8-max(max(T[1],T[2]),T[3]);
	}
	inline bool check(void){
		return getVal()==0;
	}
};

int itdep;
int last;
char ans[1048576];

inline Node oper(Node a,reg int x){
	reg int tmp=a.a[op[x][0]];
	for(reg int i=1;i<7;++i)
		a.a[op[x][i-1]]=a.a[op[x][i]];
	a.a[op[x][6]]=tmp;
	return a;
}

inline bool dfs(reg int dep,Node a,reg int lastop){
	if(a.getVal()+dep-1>itdep)
		return false;
	if(dep>itdep){
		last=a.a[6];
		return a.check();
	}
	for(reg int i=0;i<8;++i)
		if(opps[i]!=lastop){
			ans[dep]=ch[i];
			if(dfs(dep+1,oper(a,i),i))
				return true;
		}
	return false;
}

int main(void){
	while(true){
		static Node s;
		s.read();
		memset(ans,0,sizeof(ans));
		for(itdep=0;;++itdep)
			if(dfs(1,s,-1)){
				if(itdep==0)
					puts("No moves needed");
				else
					puts(ans+1);
				printf("%d\n",last);
				break;
			}
	}
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bitset<99999999> vis;

struct Node{
	int t;
	int unit[9];
	int pre;
	inline int GetVal(void){
		reg int res=0;
		for(reg int i=0;i<8;++i)
			res=10*res+unit[i];
		return res;
	}
};

const int MAXSIZE=1e6+5;

Node s;
Node Q[MAXSIZE];

inline void dfs(reg int id){
	if(id!=1)
		dfs(Q[id].pre);
	printf("%d %d %d\n%d %d %d\n%d %d %d\n\n",Q[id].unit[0],Q[id].unit[1],Q[id].unit[2],Q[id].unit[3],Q[id].unit[4],Q[id].unit[5],Q[id].unit[6],Q[id].unit[7],Q[id].unit[8]);
}

int main(void){
	s.t=0;
	for(reg int i=0;i<9;++i)
		scanf("%d",&s.unit[i]);
	reg int head,tail;
	Q[head=tail=1]=s;
	while(head<=tail){
		if(Q[head].GetVal()==1234567){
			printf("%d\n",Q[head].t);
			dfs(head);
			exit(0);
		}
		static Node pre;
		pre=Q[head];
		++pre.t;
		pre.pre=head;
		Q[++tail]=pre;
		swap(Q[tail].unit[6],Q[tail].unit[3]);
		swap(Q[tail].unit[7],Q[tail].unit[6]);
		swap(Q[tail].unit[8],Q[tail].unit[7]);
		swap(Q[tail].unit[5],Q[tail].unit[8]);
		swap(Q[tail].unit[2],Q[tail].unit[5]);
		swap(Q[tail].unit[1],Q[tail].unit[2]);
		swap(Q[tail].unit[0],Q[tail].unit[1]);
		reg int val1=Q[tail].GetVal();
		if(vis[val1])
			--tail;
		vis[val1]=true;
		Q[++tail]=pre;
		swap(Q[tail].unit[5],Q[tail].unit[4]);
		swap(Q[tail].unit[4],Q[tail].unit[3]);
		reg int val2=Q[tail].GetVal();
		if(vis[val2])
			--tail;
		vis[val2]=true;
		++head;
	}
	puts("UNSOLVABLE");
	return 0;
}
#include "jumps.h"
#include<bits/stdc++.h>
using namespace std;
#define register
typedef long long ll;

const int MAXN=2e5+5;
const int MAXLOG2N=18+1;
const int inf=0x3f3f3f3f;

int n;
int h[MAXN];
int lef[MAXN][MAXLOG2N],rig[MAXN][MAXLOG2N];

void init(int N,std::vector<int> H) {
	n=N;
	for(int i=0;i<N;++i)
		h[i+1]=H[i];
	h[0]=h[n+1]=inf;
	int top;
	static int S[MAXN];
	top=0;
	S[++top]=0;
	for(int i=1;i<=n;++i){
		while(top&&h[S[top]]<h[i])
			--top;
		lef[i][0]=S[top];
		S[++top]=i;
	}
	top=0;
	S[++top]=n+1;
	for(int i=n;i>=1;--i){
		while(top&&h[S[top]]<h[i])
			--top;
		rig[i][0]=S[top];
		S[++top]=i;
	}
	for(int i=0;i<MAXLOG2N;++i)
		lef[1][i]=lef[0][i]=0,rig[n][i]=rig[n+1][i]=n+1;
	for(int j=2;j<=n;++j)
		for(int i=1;i<MAXLOG2N;++i)
			lef[j][i]=lef[lef[j][i-1]][i-1];
	for(int j=n-1;j>=1;--j)
		for(int i=1;i<MAXLOG2N;++i)
			rig[j][i]=rig[rig[j][i-1]][i-1];
	return;
}

struct Node{
	int id,val;
	inline Node(int id=0,int val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

bool vis[MAXN];
int dis[MAXN];

inline int getPosLef(int x,int k){
	for(int i=MAXLOG2N-1;i>=0;--i)
		if((k>>i)&1)
			x=lef[x][i];
	return x;
}

inline int getPosRig(int x,int k){
	for(int i=MAXLOG2N-1;i>=0;--i)
		if((k>>i)&1)
			x=rig[x][i];
	return x;
}

int minimum_jumps(int A,int B,int C,int D){
	++A,++B,++C,++D;
	int LIM;
	if(A==C)
		return 0;
	if(C<A){
		int _l=1,_r=n,_mid;
		while(_l<_r){
			_mid=(_l+_r)>>1;
			int pos=getPosLef(A,_mid);
			if(pos<=D)
				_r=_mid;
			else
				_l=_mid+1;
		}
		if(getPosLef(A,_l)<C)
			return -1;
		else
			LIM=_l;
	}
	else{
		int _l=1,_r=n,_mid;
		while(_l<_r){
			_mid=(_l+_r)>>1;
			int pos=getPosRig(B,_mid);
			if(pos>=C)
				_r=_mid;
			else
				_l=_mid+1;
		}
		if(getPosRig(B,_l)>D)
			return -1;
		else
			LIM=_l;
	}
	fill(vis+1,vis+n+1,false);
	fill(dis+1,dis+n+1,inf);
	priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
	dis[A]=0,Q.push(Node(A,dis[A]));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		int u=s.id;
		if(vis[u])
			continue;
		vis[u]=true;
		if(u==C)
			return dis[C];
		for(int i=0;i<MAXLOG2N;++i){
			if(dis[u]+(1<<i)>=LIM)
				break;
			int v;
			v=lef[u][i];
			if(v>=1&&dis[v]>dis[u]+(1<<i))
				dis[v]=dis[u]+(1<<i),Q.push(Node(v,dis[v]));
			v=rig[u][i];
			if(v<=n&&dis[v]>dis[u]+(1<<i))
				dis[v]=dis[u]+(1<<i),Q.push(Node(v,dis[v]));
		}
	}
	return LIM;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=20000+5;
const int MAXM=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int c[MAXM],d[MAXM];
vector<int> V[MAXN<<1];

inline void Add_Tube(int u,int v){
	V[u].push_back(v);
	V[v].push_back(u);
	return;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		c[i]=read(),d[i]=read();
		Add_Tube(c[i],d[i]);
	}
	return;
}

int tim,dfn[MAXN<<1],low[MAXN<<1];
stack<int> S;
int fa[MAXN<<1];
int Tarjan_cnt;
vector<int> BCC[MAXN];

inline void Tarjan(int ID,int father){
	dfn[ID]=low[ID]=++tim;
	S.push(ID);
	for(reg int i=0,size=V[ID].size();i<size;++i)
		if(V[ID][i]!=father){
			if(!dfn[V[ID][i]]){
				Tarjan(V[ID][i],ID);
				low[ID]=min(low[ID],low[V[ID][i]]);
				if(low[V[ID][i]]>=dfn[ID]){
					++Tarjan_cnt;
					while(S.top()!=V[ID][i]){
						BCC[Tarjan_cnt].push_back(S.top());
						S.pop();
					}
					BCC[Tarjan_cnt].push_back(S.top());
					S.pop();
					BCC[Tarjan_cnt].push_back(ID);
				}
			}
			else
				low[ID]=min(low[ID],dfn[V[ID][i]]);
		}
	return;
}

int dep[MAXN<<1];
int size[MAXN<<1],son[MAXN<<1];

inline void DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=0;i<(int)V[ID].size();++i)
		if(V[ID][i]!=father){
			DFS1(V[ID][i],ID);
			size[ID]+=size[V[ID][i]];
			if(size[V[ID][i]]>size[son[ID]])
				son[ID]=V[ID][i];
		}
	return;
}

int top[MAXN<<1];

inline void DFS2(reg int ID,reg int father,reg int topf){
	dfn[ID]=++tim;
	top[ID]=topf;
	if(son[ID])
		DFS2(son[ID],ID,topf);
	for(reg int i=0,size=V[ID].size();i<size;++i)
		if(V[ID][i]!=father&&V[ID][i]!=son[ID])
			DFS2(V[ID][i],ID,V[ID][i]);
	return;
}

struct SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int val,tag;
	};
	Node unit[MAXN<<3];
	inline void pushup(reg int k){
		unit[k].val=unit[lson].val+unit[rson].val;
		return;
	}
	inline void Add(reg int k,reg int l,reg int r,reg int val){
		unit[k].val+=(r-l+1)*val;
		unit[k].tag+=val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(unit[k].tag){
			Add(lson,l,mid,unit[k].tag);
			Add(rson,mid+1,r,unit[k].tag);
			unit[k].tag=0;
		}
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			Add(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			Update(lson,l,mid,L,R,val);
		if(R>mid)
			Update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int pos){
		if(l==r&&l==pos){
			return unit[k].val;
		}
		pushdown(k,l,r);
		reg int res=0;
		if(pos<=mid)
			res=Query(lson,l,mid,pos);
		if(pos>mid)
			res=Query(rson,mid+1,r,pos);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
};

SegmentTree T;

inline void Update(int x,int y,reg int val){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		T.Update(1,1,n+Tarjan_cnt,dfn[top[x]],dfn[x],val);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	T.Update(1,1,n+Tarjan_cnt,dfn[x],dfn[y],val);
	return;
}

inline int Query(reg int x){
	return T.Query(1,1,n+Tarjan_cnt,dfn[x]);
}

inline void Work(void){
	Tarjan(1,0);
	for(reg int i=1;i<=n;++i)
		V[i].clear();
	for(reg int i=1;i<=Tarjan_cnt;++i)
		for(reg int j=0;j<(int)BCC[i].size();++j)
			Add_Tube(n+i,BCC[i][j]);
	DFS1(1,0);
	tim=0;
	DFS2(1,0,1);
	reg int Q=read();
	while(Q--){
		static int s,t,m;
		s=read(),t=read(),m=read();
		Update(s,t,1);
		reg int ans=Query(m);
		puts(ans?"yes":"no");
		Update(s,t,-1);
	}
	return;
}

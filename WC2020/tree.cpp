#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e5+5;

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

namespace Subtask0{
	const int MAXN=2e4+5;
	int q;
	bool vis[MAXN];
	int w[MAXN];
	inline int DFS(reg int u,reg int father){
		reg int sum=vis[u];
		for(reg int i=head[u];i;i=Next[i])
			if(to[i]!=father)
				sum+=DFS(to[i],u);
		if(vis[u])
			w[u]=sum;
		else
			w[u]=0;
		return sum;
	}
	inline bool check(reg int ans){
		DFS(1,0);
		reg int a=0;
		for(reg int i=1;i<=n;++i)
			if(w[i]>ans)
				++a;
		return a<=ans;
	}
	inline void Solve(void){
		q=read();
		reg int lastans=0;
		while(q--){
			static int t,v;
			t=read(),v=read();
			switch(t){
				case 1:{
					vis[v]=true;
					if(!check(lastans))
						++lastans;
					break;
				}
				case 2:{
					vis[v]=false;
					if(check(lastans-1))
						--lastans;
					break;
				}
			}
			printf("%d\n",lastans);
		}
		return;
	}
}

namespace SubtaskA{
	const int MAXN=5e5+5;
	bool w[MAXN];
	namespace SegmentTree{
		#define lson ( (k) << 1 )
		#define rson ( (k) << 1 | 1 )
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int cnt;
			int Max,Min;
			int tag;
			#define cnt(x) unit[(x)].cnt
			#define Max(x) unit[(x)].Max
			#define Min(x) unit[(x)].Min
			#define tag(x) unit[(x)].tag
		};
		Node unit[MAXN<<2];
		inline void pushup(reg int k){
			cnt(k)=cnt(lson)+cnt(rson);
			Max(k)=max(Max(lson),Max(rson));
			Min(k)=min(Min(lson),Min(rson));
			return;
		}
		inline void add(reg int k,reg int l,reg int r,reg int val){
			Max(k)+=val,Min(k)+=val;
			tag(k)+=val;
			return;
		}
		inline void pushdown(reg int k,reg int l,reg int r){
			if(tag(k)){
				add(lson,l,mid,tag(k));
				add(rson,mid+1,r,tag(k));
				tag(k)=0;
			}
			return;
		}
		inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
			if(l==r){
				Max(k)=Min(k)=val;
				cnt(k)=(val!=0)?1:0;
				return;
			}
			pushdown(k,l,r);
			if(pos<=mid)
				update(lson,l,mid,pos,val);
			else
				update(rson,mid+1,r,pos,val);
			pushup(k);
			return;
		}
		inline void update_add(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
			if(L<=l&&r<=R){
				add(k,l,r,val);
				return;
			}
			pushdown(k,l,r);
			if(L<=mid)
				update_add(lson,l,mid,L,R,val);
			if(R>mid)
				update_add(rson,mid+1,r,L,R,val);
			pushup(k);
			return;
		}
		inline int querycnt(reg int k,reg int l,reg int r,reg int L,reg int R){
			if(L<=l&&r<=R)
				return cnt(k);
			pushdown(k,l,r);
			reg int res=0;
			if(L<=mid)
				res+=querycnt(lson,l,mid,L,R);
			if(R>mid)
				res+=querycnt(rson,mid+1,r,L,R);
			return res;
		}
		inline int querycnt(reg int k,reg int l,reg int r,reg int val){
			if(Min(k)>val)
				return cnt(k);
			if(Max(k)<=val)
				return 0;
			pushdown(k,l,r);
			return querycnt(lson,l,mid,val)+querycnt(rson,mid+1,r,val);
		}
	}
	inline bool check(reg int ans){
		reg int a=SegmentTree::querycnt(1,1,n,ans);
		return a<=ans;
	}
	int fa[MAXN],dep[MAXN];
	int size[MAXN],son[MAXN];
	inline void DFS1(reg int u,reg int father){
		size[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+1;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				DFS1(v,u);
				size[u]+=size[v];
				if(size[son[u]]<size[v])
					son[u]=v;
			}
		}
		return;
	}
	int tim,dfn[MAXN];
	int top[MAXN];
	inline void DFS2(reg int u,reg int father,reg int topf){
		dfn[u]=++tim;
		top[u]=topf;
		if(!son[u])
			return;
		DFS2(son[u],u,topf);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father&&v!=son[u])
				DFS2(v,u,v);
		}
		return;
	}
	inline void update(int u,int v,reg int val){
		while(top[u]!=top[v]){
			if(dep[top[u]]>dep[top[v]])
				swap(u,v);
			SegmentTree::update_add(1,1,n,dfn[top[v]],dfn[v],val);
			v=fa[top[v]];
		}
		if(dep[u]>dep[v])
			swap(u,v);
		SegmentTree::update_add(1,1,n,dfn[u],dfn[v],val);
		return;
	}
	inline void Solve(void){
		DFS1(1,0);
		DFS2(1,0,1);
		reg int q=read();
		reg int lastans=0;
		while(q--){
			static int t,v;
			t=read(),v=read();
			switch(t){
				case 1:{
					reg int sum=SegmentTree::querycnt(1,1,n,dfn[v],dfn[v]+size[v]-1)+1;
					SegmentTree::update(1,1,n,dfn[v],sum);
					update(1,v,1);
					update(v,v,-1);
					if(!check(lastans))
						++lastans;
					break;
				}
				case 2:{
					update(1,v,-1);
					update(v,v,1);
					SegmentTree::update(1,1,n,dfn[v],0);
					if(check(lastans-1))
						--lastans;
					break;
				}
			}
			printf("%d\n",lastans);
		}
		return;
	}
}

namespace SubtaskB{
	const int MAXN=2e5+5;
	int dep[MAXN],pos[MAXN];
	inline void DFS(reg int u,reg int father){
		dep[u]=dep[father]+1;
		pos[u]=dep[u];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father)
				DFS(v,father);
		}
		return;
	}
	bool vis[MAXN];
	inline void Solve(void){
		reg int q=read();
		reg int cnt=0;
		while(q--){
			static int t,v;
			t=read(),v=read();
			switch(t){
				case 1:{
					vis[v]=true;
					++cnt;
					break;
				}
				case 2:{
					vis[v]=false;
					--cnt;
					break;
				}
			}
			printf("%d\n",(cnt&1)?(cnt/2+1):(cnt/2));
		}
		return;
	}
}

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int main(void){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=read();
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y);
		Add_Edge(y,x);
	}
	if(n<=1000)
		Subtask0::Solve();
	else if(n<=100000)
		SubtaskA::Solve();
	else if(n<=200000)
		SubtaskB::Solve();
	else
		SubtaskA::Solve();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
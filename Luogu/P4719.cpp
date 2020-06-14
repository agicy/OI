#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
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

const int MAXN=100000+5;

int n,m;
int a[MAXN];

const int MAXSIZE=2;

struct Matrix{
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(void){
		memset(unit,0,sizeof(unit));
		return;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
	inline Matrix operator*(const Matrix& a){
		Matrix res;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				for(reg int k=0;k<MAXSIZE;++k)
					res[i][j]=max(res[i][j],unit[i][k]+a.unit[k][j]);
		return res;
	}
};

int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int son[MAXN],size[MAXN];
int f[MAXN][2];

inline void DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID]=father;
	dep[ID]=dep[father]+1;
	f[ID][1]=a[ID];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS1(to[i],ID);
			size[ID]+=size[to[i]];
			if(size[son[ID]]<size[to[i]])
				son[ID]=to[i];
			f[ID][0]+=max(f[to[i]][0],f[to[i]][1]);
			f[ID][1]+=f[to[i]][0];
		}
	return;
}

int tim,dfn[MAXN],rnk[MAXN];
int top[MAXN];
int End[MAXN];
Matrix g[MAXN];

inline void DFS2(reg int ID,reg int father,reg int topf){
	top[ID]=topf;
	dfn[ID]=++tim;
	rnk[dfn[ID]]=ID;
	End[topf]=dfn[ID];
	g[ID][1][0]=a[ID];
	g[ID][1][1]=-INF;
	if(!son[ID])
		return;
	DFS2(son[ID],ID,topf);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&to[i]!=son[ID]){
			DFS2(to[i],ID,to[i]);
			g[ID][0][0]+=max(f[to[i]][0],f[to[i]][1]);
			g[ID][1][0]+=f[to[i]][0];
		}
	g[ID][0][1]=g[ID][0][0];
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	Matrix val[MAXN<<2];
	inline void pushup(reg int k){
		val[k]=val[lson]*val[rson];
		return;
	}
	inline void Build(reg int k,reg int l,reg int r){
		if(l==r){
			val[k]=g[rnk[l]];
			return;
		}
		Build(lson,l,mid);
		Build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int pos){
		if(l==r){
			val[k]=g[rnk[l]];
			return;
		}
		if(pos<=mid)
			Update(lson,l,mid,pos);
		if(pos>mid)
			Update(rson,mid+1,r,pos);
		pushup(k);
		return;
	}
	inline Matrix Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return val[k];
		if(mid<L)
			return Query(rson,mid+1,r,L,R);
		else if(R<=mid)
			return Query(lson,l,mid,L,R);
		else
			return Query(lson,l,mid,L,R)*Query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

using namespace SegmentTree;

inline void Update(reg int ID,reg int val){
	g[ID][1][0]+=val-a[ID];
	a[ID]=val;
	while(ID){
		Matrix last=Query(1,1,n,dfn[top[ID]],End[top[ID]]);
		Update(1,1,n,dfn[ID]);
		Matrix now=Query(1,1,n,dfn[top[ID]],End[top[ID]]);
		ID=fa[top[ID]];
		g[ID][0][0]+=max(now[0][0],now[1][0])-max(last[0][0],last[1][0]);
		g[ID][0][1]=g[ID][0][0];
		g[ID][1][0]+=now[0][0]-last[0][0];
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	DFS1(1,0);
	DFS2(1,0,1);
	Build(1,1,n);
	while(m--){
		static int x,y;
		x=read(),y=read();
		Update(x,y);
		Matrix ans=Query(1,1,n,1,End[top[1]]);
		printf("%d\n",max(ans[0][0],ans[1][0]));
	}
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 998244353
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

int n;

const int MAXSIZE=3;

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
					res[i][j]=(res[i][j]+(ll)unit[i][k]*a.unit[k][j]%MOD)%MOD;
		return res;
	}
	inline Matrix operator+(const Matrix& a){
		Matrix res;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				res[i][j]=(unit[i][j]+a.unit[i][j])%MOD;
		return res;
	}
};

Matrix I;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int son[MAXN],size[MAXN];

inline void DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS1(to[i],ID);
			size[ID]+=size[to[i]];
			if(size[son[ID]]<size[to[i]])
				son[ID]=to[i];
		}
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	bool istag[MAXN<<2];
	Matrix tag[MAXN<<2];
	Matrix val[MAXN<<2];
	/*
	inline void pushup(reg int k){
		val[k]=val[lson]+val[rson];
		return;
	}
	*/
	inline void Mul(reg int k,const Matrix& x){
		val[k]=val[k]*x;
		if(!istag[k]){
			istag[k]=true;
			tag[k]=x;
		}
		else
			tag[k]=tag[k]*x;
		return;
	}
	inline void pushdown(reg int k){
		if(istag[k]){
			Mul(lson,tag[k]);
			Mul(rson,tag[k]);
			istag[k]=false;
		}
		return;
	}
	inline void Build(reg int k,reg int l,reg int r){
		if(l==r){
			val[k][0][2]=1;
			return;
		}
		Build(lson,l,mid);
		Build(rson,mid+1,r);
		//pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,const Matrix& x){
		if(L<=l&&r<=R){
			Mul(k,x);
			return;
		}
		pushdown(k);
		if(L<=mid)
			Update(lson,l,mid,L,R,x);
		if(R>mid)
			Update(rson,mid+1,r,L,R,x);
		//pushup(k);
		return;
	}
	inline Matrix Query(reg int k,reg int l,reg int r,reg int pos){
		if(l==r)
			return val[k];
		pushdown(k);
		if(pos<=mid)
			return Query(lson,l,mid,pos);
		else
			return Query(rson,mid+1,r,pos);
	}
	#undef lson
	#undef rson
	#undef mid
}

int tim,dfn[MAXN];
int top[MAXN];

inline void DFS2(reg int ID,reg int father,reg int topf){
	dfn[ID]=++tim;
	top[ID]=topf;
	if(son[ID])
		DFS2(son[ID],ID,topf);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&to[i]!=son[ID])
			DFS2(to[i],ID,to[i]);
	return;
}

using namespace SegmentTree;

inline void Update(int u,int v,const Matrix& x){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]])
			swap(u,v);
		Update(1,1,n,dfn[top[v]],dfn[v],x);
		v=fa[top[v]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	Update(1,1,n,dfn[u],dfn[v],x);
	return;
}

int main(void){
	n=read();
	I[0][0]=I[1][1]=I[2][2]=1;
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	DFS1(1,0);
	DFS2(1,0,1);
	Build(1,1,n);
	reg int m=read();
	while(m--){
		static int opt,x,d;
		static Matrix M;
		opt=read(),x=read();
		M=I;
		switch(opt){
			case 1:{
				d=read();
				M[2][0]=d;
				Update(1,x,M);
				break;
			}
			case 2:{
				d=read();
				M[0][1]=d;
				Update(1,x,M);
				break;
			}
			case 3:{
				Matrix res=Query(1,1,n,dfn[x]);
				printf("%d\n",res[0][1]);
				break;
			}
			default:break;
		}
	}
	return 0;
}
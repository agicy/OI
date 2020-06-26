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

const int MAXN=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int p[MAXN];
int cnt,head[MAXN],to[MAXN],Next[MAXN];
vector<int> V;

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		p[i]=read();
		V.push_back(p[i]);
	}
	for(reg int i=2;i<=n;++i){
		static int fa;
		fa=read();
		Add_Edge(fa,i);
	}
	return;
}

const int MAXSIZE=MAXN*30;

struct SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	int tot;
	int root[MAXN];
	int val[MAXSIZE],lson[MAXSIZE],rson[MAXSIZE];
	inline void pushup(reg int k){
		val[k]=val[lson[k]]+val[rson[k]];
		return;
	}
	inline int Build(reg int l,reg int r){
		reg int ID=++tot;
		val[ID]=lson[ID]=rson[ID]=0;
		if(l!=r){
			lson[ID]=Build(l,mid);
			rson[ID]=Build(mid+1,r);
		}
		return ID;
	}
	inline int Update(reg int pre,reg int l,reg int r,reg int pos,reg int Val){
		reg int ID=++tot;
		val[ID]=val[pre],lson[ID]=lson[pre],rson[ID]=rson[pre];
		if(l==r){
			val[ID]+=Val;
			return ID;
		}
		if(pos<=mid)
			lson[ID]=Update(lson[pre],l,mid,pos,Val);
		if(pos>mid)
			rson[ID]=Update(rson[pre],mid+1,r,pos,Val);
		pushup(ID);
		return ID;
	}
	inline int Query(reg int pre,reg int ID,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			return val[ID]-val[pre];
		}
		reg int res=0;
		if(L<=mid){
			res+=Query(lson[pre],lson[ID],l,mid,L,R);
		}
		if(R>mid){
			res+=Query(rson[pre],rson[ID],mid+1,r,L,R);
		}
		return res;
	}
	#undef mid
};

SegmentTree T;

int size[MAXN];
int tim,dfn[MAXN];
int val[MAXN];

inline void DFS(reg int ID){
	size[ID]=1;
	dfn[ID]=++tim;
	T.root[dfn[ID]]=T.Update(T.root[dfn[ID]-1],1,V.size(),p[ID],1);
	for(reg int i=head[ID];i;i=Next[i]){
		DFS(to[i]);
		size[ID]+=size[to[i]];
	}
	return;
}

inline void Work(void){
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		p[i]=lower_bound(V.begin(),V.end(),p[i])-V.begin()+1;
	T.root[0]=T.Build(1,V.size());
	DFS(1);
	for(reg int i=1;i<=n;++i){
		reg int ans=T.Query(T.root[dfn[i]],T.root[dfn[i]+size[i]-1],1,V.size(),p[i]+1,V.size());
		printf("%d\n",ans);
	}
	return;
}

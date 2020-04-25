#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 1000000000
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
const int MAXM=200000+5;
const int MAXK=300000+5;
const int MAXLOG2K=19+1;
const int MAXSIZE=MAXK*MAXLOG2K+MAXM;
const int MAXVCNT=(MAXN<<2)+MAXN;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,s,m;
int inDeg[MAXVCNT],f[MAXVCNT],Min[MAXVCNT];

int cnt,head[MAXVCNT],to[MAXSIZE],w[MAXSIZE],Next[MAXSIZE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	++inDeg[v];
	return;
}

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	int tot,ID[MAXN],lson[MAXVCNT],rson[MAXVCNT];
	inline void Build(int k,reg int l,reg int r){
		if(l==r){
			ID[l]=k;
			tot=max(tot,k);
			return;
		}
		lson[k]=++tot;
		Build(lson[k],l,mid);
		Add_Edge(k,lson[k],0);
		rson[k]=++tot;
		Build(rson[k],mid+1,r);
		Add_Edge(k,rson[k],0);
		return;
	}
	inline void Add_Edge(reg int k,reg int l,reg int r,reg int L,reg int R,reg int pos){
		if(L<=l&&r<=R){
			::Add_Edge(pos,k,1);
			return;
		}
		if(R<l||r<L)
			return;
		Add_Edge(lson[k],l,mid,L,R,pos);
		Add_Edge(rson[k],mid+1,r,L,R,pos);
		return;
	}
	#undef mid
}

using namespace SegmentTree;

inline void Read(void){
	n=read(),s=read(),m=read();
	tot=1;
	Build(1,1,n);
	for(reg int i=1;i<=s;++i){
		static int p,d;
		p=read(),d=read();
		Min[ID[p]]=f[ID[p]]=d;
	}
	for(reg int i=1;i<=m;++i){
		static int l,r,k;
		l=read(),r=read(),k=read();
		reg int ptr=l;
		++tot;
		for(reg int j=1;j<=k;++j){
			static int x;
			x=read();
			Add_Edge(ID[x],tot,0);
			if(ptr<=x-1)
				Add_Edge(1,1,n,ptr,x-1,tot);
			ptr=x+1;
		}
		if(ptr<=r)
			Add_Edge(1,1,n,ptr,r,tot);
	}
	return;
}

bool flag;
bool vis[MAXVCNT],inStack[MAXVCNT];

inline void DFS(reg int ID){
	vis[ID]=true;
	inStack[ID]=true;
	for(reg int i=head[ID];i&&flag;i=Next[i]){
		if(inStack[to[i]]){
			flag=false;
			return;
		}
		if(!vis[to[i]])
			DFS(to[i]);
	}
	inStack[ID]=false;
	return;
}

queue<int> Q;

inline void Work(void){
	for(reg int i=1;i<=tot;++i)
		if(!f[i])
			f[i]=INF;
	for(reg int i=1;i<=tot;++i)
		if(!vis[i]){
			flag=true;
			DFS(i);
			if(!flag){
				printf("NIE");
				return;
			}
	}
	for(int i=1;i<=tot;++i)
		if(!inDeg[i])
			Q.push(i);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		for(reg int i=head[ID];i;i=Next[i]){
			--inDeg[to[i]];
			if(Min[to[i]]>f[ID]-w[i]){
				printf("NIE");
				return;
			}
			f[to[i]]=min(f[to[i]],f[ID]-w[i]);
			if(!inDeg[to[i]])
				Q.push(to[i]);
			if(f[to[i]]<1){
				printf("NIE");
				return;
			}
		}
	}
	puts("TAK");
	for(reg int i=1;i<=n;++i)
		printf("%d%c",f[ID[i]],i==n?'\n':' ');
	return;
}

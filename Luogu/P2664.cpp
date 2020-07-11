#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;
const int MAXC=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int sum;
bool vis[MAXC];
int c[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		c[i]=read();
		if(!vis[c[i]]){
			vis[c[i]]=true;
			++sum;
		}
	}
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	return;
}

int T[MAXC];
int size[MAXN];
int tot[MAXN];

inline void DFS(reg int ID,reg int father){
	size[ID]=1;
	reg int temp=T[c[father]];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS(to[i],ID);
			size[ID]+=size[to[i]];
		}
	++T[c[ID]];
	if(father){
		tot[ID]=size[ID]-T[c[father]]+temp;
		T[c[father]]+=tot[ID];
	}
	return;
}

ll Sum;
int del[MAXN];
ll ans[MAXN];

inline void GetAns(reg int ID,reg int father){
	reg int temp=del[c[father]];
	Sum+=tot[ID]-del[c[father]];
	del[c[father]]=tot[ID];
	ans[ID]=(ll)n*sum-Sum+del[c[ID]];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			GetAns(to[i],ID);
	del[c[father]]=temp;
	Sum-=tot[ID]-del[c[father]];
	return;
}

inline void Work(void){
	DFS(1,0);
	for(reg int i=1;i<=1e5;++i)
		if(vis[i]){
			Sum+=n-T[i];
			del[i]=n-T[i];
		}
	GetAns(1,0);
	for(reg int i=1;i<=n;++i)
		printf("%lld\n",ans[i]);
	return;
}

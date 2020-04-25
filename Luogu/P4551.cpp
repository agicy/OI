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

struct Trie{
	int tot;
	int ch[MAXN*32][2];
	inline void Init(void){
		tot=1;
		return;
	}
	inline void insert(reg int num){
		reg int ID=1;
		for(reg int i=30;i>=0;--i){
			reg int p=((num>>i)&1);
			if(ch[ID][p]==0)
				ch[ID][p]=++tot;
			ID=ch[ID][p];
		}
		return;
	}
	inline int query(reg int num){
		reg int res=0,ID=1;
		for(reg int i=30;i>=0;--i){
			reg int p=((num>>i)&1);
			if(ch[ID][p^1]){
				ID=ch[ID][p^1];
				res|=(1<<i);
			}
			else
				ID=ch[ID][p];
		}
		return res;
	}
};

int n;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
int dis[MAXN];
Trie T;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
	}
	return;
}

inline void DFS(reg int ID,reg int father){
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			dis[to[i]]=dis[ID]^w[i];
			DFS(to[i],ID);
		}
	return;
}

inline void Work(void){
	DFS(1,0);
	T.Init();
	int ans=0;
	for(reg int i=1;i<=n;++i){
		T.insert(dis[i]);
		ans=max(ans,T.query(dis[i]));
	}
	printf("%d\n",ans);
	return;
}

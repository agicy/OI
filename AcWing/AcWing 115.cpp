#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
typedef long long ll;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1000+5;

struct Node{
	int ID;
	int size,val;
	inline bool operator<(const Node &a)const{
		return (double)val/size<(double)a.val/a.size;
	}
	inline bool operator>(const Node &a)const{
		return (double)val/size>(double)a.val/a.size;
	}
};

int n,root;
int val[MAXN];
int cnt,head[MAXN],to[MAXN],Next[MAXN];
Node a[MAXN];
priority_queue<Node,vector<Node>,less<Node>/**/> Q;

inline void DFS(reg int,reg int);
inline void Add_Edge(reg int,reg int);
inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void DFS(reg int ID,reg int father){
	a[ID].ID=ID;
	a[ID].size=1+a[father].size;
	a[ID].val=val[ID]+a[father].val;
	for(reg int i=head[ID];i;i=Next[i])
		DFS(to[i],ID);
	return;
}

inline void Read(void){
	n=read(),root=read();
	for(reg int i=1;i<=n;++i)
		val[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
	}
	return;
}

inline void Work(void){
	reg int T=1,ans=0;
	DFS(root,0);
	Q.push(a[root]);
	while(!Q.empty()){
		Node temp=Q.top();
		Q.pop();
		ans+=T*val[temp.ID];
		for(reg int i=head[temp.ID];i;i=Next[i])
			Q.push(a[to[i]]);
		++T;
	}
	printf("%d\n",ans);
	return;
}

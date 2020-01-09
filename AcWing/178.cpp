#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=1000+5;
const int MAXM=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int a[MAXM],b[MAXM],l[MAXM];
int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];
int s,t,k;

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i)
		a[i]=read(),b[i]=read(),l[i]=read();
	s=read(),t=read(),k=read();
	return;
}

struct Node{
	int ID,val;
	inline Node(void){
		ID=val=0;
		return;
	}
	inline Node(reg int a,reg int b){
		ID=a,val=b;
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

int vis[MAXN];
int f[MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void Dijkstra(reg int s){
	memset(vis,false,sizeof(vis));
	memset(f,0X3F,sizeof(f));
	while(!Q.empty())
		Q.pop();
	f[s]=0,Q.push(Node(s,0));
	while(!Q.empty()){
		static Node temp;
		temp=Q.top();
		Q.pop();
		reg int ID=temp.ID;
		if(vis[ID])
			continue;
		vis[ID]=true;
		for(reg int i=head[ID];i;i=Next[i])
			if(f[to[i]]>f[ID]+w[i]){
				f[to[i]]=f[ID]+w[i];
				if(!vis[to[i]])
					Q.push(Node(to[i],f[to[i]]));
			}
	}
	return;
}

inline void Astar(void){
	if(f[s]==INF)
		return;
	if(s==t)
		++k;
	memset(vis,0,sizeof(vis));
	while(!Q.empty())
		Q.pop();
	Q.push(Node(s,f[s]));
	while(!Q.empty()){
		static Node temp;
		temp=Q.top();
		Q.pop();
		reg int ID=temp.ID,val=temp.val;
		reg int dis=val-f[ID];
		++vis[ID];
		if(vis[t]==k){
			printf("%d\n",dis);
			exit(0);
		}
		for(reg int i=head[ID];i;i=Next[i])
			if(vis[to[i]]<k)
				Q.push(Node(to[i],f[to[i]]+dis+w[i]));
	}
	return;
}

inline void Work(void){
	for(reg int i=1;i<=m;++i)
		Add_Edge(b[i],a[i],l[i]);
	Dijkstra(t);
	cnt=0;
	memset(head,0,sizeof(head));
	for(reg int i=1;i<=m;++i)
		Add_Edge(a[i],b[i],l[i]);
	Astar();
	puts("-1");
	return;
}

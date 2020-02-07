#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=5000+5;
const int MAXM=5000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int c1,c2,y;
		c1=read(),c2=read(),y=read();
		Add_Edge(c2,c1,y);
	}
	return;
}

bool inque[MAXN];
int dis[MAXN];
int inQue[MAXN];
queue<int> Q;

inline bool SPFA(int s){
	memset(inque,false,sizeof(inque));
	memset(dis,0X3F,sizeof(dis));
	while(!Q.empty())Q.pop();
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		inque[ID]=false;
		for(reg int i=head[ID];i;i=Next[i]){
			if(dis[to[i]]>dis[ID]+w[i]){
				dis[to[i]]=dis[ID]+w[i];
				if(!inque[to[i]]){
					inque[to[i]]=true;
					Q.push(to[i]);
					++inQue[to[i]];
					if(inQue[to[i]]>n)
						return false;
				}
			}
		}
	}
	return true;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		Add_Edge(0,i,0);
	if(SPFA(0))
		for(reg int i=1;i<=n;++i)
			printf("%d%c",dis[i],i==n?'\n':' ');
	else
		puts("NO");
	return;
}

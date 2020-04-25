#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3F
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

const int MAXN=100+5;
const int MAXK=10+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,K,a,b,c;
int O[MAXN][MAXN];

inline void Read(void){
	n=read(),K=read(),a=read(),b=read(),c=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			O[i][j]=read();
	return;
}

int cnt=1,head[MAXN*MAXN*MAXK],to[MAXN*MAXN*MAXK*5],Next[MAXN*MAXN*MAXK*5];
ll w[MAXN*MAXN*MAXK*5];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline int GetID(reg int i,reg int j,reg int k){
	return (k-1)*(n*n)+(i-1)*n+j;
}

bool inque[MAXN*MAXN*MAXK];
ll dis[MAXN*MAXN*MAXK];
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
		for(reg int i=head[ID];i;i=Next[i])
			if(dis[to[i]]>dis[ID]+w[i]){
				dis[to[i]]=dis[ID]+w[i];
				if(!inque[to[i]]){
					inque[to[i]]=true;
					Q.push(to[i]);
				}
			}
	}
	return true;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			for(reg int k=1;k<=K;++k)
				Add_Edge(GetID(i,j,k),GetID(i,j,K+1),0);
			if(O[i][j]){
				for(reg int k=2;k<=K+1;++k)
					Add_Edge(GetID(i,j,k),GetID(i,j,1),a);
				if(i<n)
					Add_Edge(GetID(i,j,1),GetID(i+1,j,2),0);
				if(j<n)
					Add_Edge(GetID(i,j,1),GetID(i,j+1,2),0);
				if(i>1)
					Add_Edge(GetID(i,j,1),GetID(i-1,j,2),b);
				if(j>1)
					Add_Edge(GetID(i,j,1),GetID(i,j-1,2),b);
			}
			else{
				for(reg int k=1;k<=K;++k){
					if(i<n)
						Add_Edge(GetID(i,j,k),GetID(i+1,j,k+1),0);
					if(j<n)
						Add_Edge(GetID(i,j,k),GetID(i,j+1,k+1),0);
					if(i>1)
						Add_Edge(GetID(i,j,k),GetID(i-1,j,k+1),b);
					if(j>1)
						Add_Edge(GetID(i,j,k),GetID(i,j-1,k+1),b);
				}
				for(reg int k=2;k<=K+1;++k)
					Add_Edge(GetID(i,j,k),GetID(i,j,1),a+c);
			}
		}
	SPFA(GetID(1,1,1));
	ll ans=INF;
	for(reg int i=1;i<=K+1;++i)
		ans=min(ans,dis[GetID(n,n,i)]);
	printf("%lld\n",ans);
	return;
}

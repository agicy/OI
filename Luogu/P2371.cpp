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

const int MAXN=12+5;
const int MAXA=500000+5;

int n,m;
ll Min=INF;
ll l,r;
int a[MAXN];
int cnt,head[MAXA],to[MAXA*MAXN],w[MAXA*MAXN],Next[MAXA*MAXN];
bool inque[MAXA];
ll dis[MAXA];
queue<int> Q;

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline bool SPFA(int s){
	memset(inque,false,sizeof(inque));
	for(reg int i=0;i<Min;++i)
		dis[i]=INF+1;
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

inline ll Query(reg ll x){
	reg ll res=0;
	for(reg int i=0;i<Min;++i)
		if(dis[i]<=x)
			res+=(x-dis[i])/Min+1;
	return res;
}

int main(void){
	n=read(),l=read(),r=read();
	for(reg int i=1;i<=n;++i){
		static ll x;
		x=read();
		if(x){
			a[++m]=x;
			Min=min(Min,x);
		}
	}
	for(reg int i=0;i<Min;++i)
		for(reg int j=1;j<=n;++j)
			if(a[j]!=Min)
				Add_Edge(i,(i+a[j])%Min,a[j]);
	SPFA(0);
	reg ll ans=Query(r)-Query(l-1);
	printf("%lld\n",ans);
	return 0;
}

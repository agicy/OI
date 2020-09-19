#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXE=MAXM*2+MAXN;

int n,m;
int cnt,head[MAXN],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool inque[MAXN];
int dis[MAXN];
deque<int> Q;

inline bool spfa(reg int s){
	inque[s]=true,dis[s]=0,Q.push_front(s);
	reg int cnt=0;
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop_front();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]<dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				if(!inque[v]){
					inque[v]=true;
					if(!Q.empty()&&dis[v]>dis[Q.front()])
						Q.push_front(v);
					else
						Q.push_back(v);
				}
			}
		}
		++cnt;
		if(cnt>5e5)
			return false;
	}
	return true;
}

int main(void){
	n=read(),m=read();
	reg bool flag=false;
	for(reg int i=1;i<=m;++i){
		static int t,a,b;
		t=read(),a=read(),b=read();
		switch(t){
			case 1:Add_Edge(a,b,0),Add_Edge(b,a,0);break;
			case 2:Add_Edge(a,b,1),flag|=(a==b);break;
			case 3:Add_Edge(b,a,0);break;
			case 4:Add_Edge(b,a,1),flag|=(a==b);break;
			case 5:Add_Edge(a,b,0);break;
		}
	}
	for(reg int i=n;i>=1;--i)
		Add_Edge(0,i,1);
	if(!flag&&spfa(0)){
		reg ll ans=0;
		for(reg int i=1;i<=n;++i)
			ans+=dis[i];
		printf("%lld\n",ans);
	}
	else
		puts("-1");
	return 0;
}
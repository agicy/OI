#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=200000+5;

int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,len);
	return;
}

int ans;
int dis[MAXN];

inline void DP(reg int ID,reg int father){
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DP(to[i],ID);
			ans=max(ans,dis[ID]+dis[to[i]]+w[i]);
			dis[ID]=max(dis[ID],dis[to[i]]+w[i]);
		}
	return;
}

int n;
int col[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		col[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Tube(u,v,(col[u]==col[v])?0:1);
	}
	DP(1,0);
	printf("%d\n",(ans+1)>>1);
	return 0;
}
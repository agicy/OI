#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1000000+5;

int n;
int w[MAXN];
int a[MAXN],b[MAXN],to[MAXN];
int minW=INF;

bool vis[MAXN];
int cnt,Min;
ll sum;

inline void DFS(reg int ID){
	++cnt;
	vis[ID]=true;
	sum+=w[a[ID]];
	Min=min(Min,w[a[ID]]);
	if(!vis[to[b[ID]]])
		DFS(to[b[ID]]);
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		w[i]=read();
		minW=min(minW,w[i]);
	}
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		to[a[i]]=i;
	}
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	reg ll ans=0;
	for(reg int i=1;i<=n;++i)
		if(!vis[i]){
			cnt=sum=0,Min=INF;
			DFS(i);
			ans+=min((ll)Min*(cnt-2)+sum,(ll)minW*(cnt+1)+Min+sum);
		}
	printf("%lld\n",ans);
	return 0;
}
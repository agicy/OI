#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=600+5;
const int inf=0x3f3f3f3f;

int n;
int G[MAXN][MAXN];
bool vis[MAXN],tag[MAXN];
int s,t,w[MAXN];

inline int step(void){
	reg int ans=inf,nex=t,Max;
	for(reg int i=1;i<=n;++i)
		vis[i]=false,w[i]=0;
	for(reg int i=1;i<=n;++i){
		Max=-1;
		for(reg int j=1;j<=n;++j)
			if(!tag[j]&&!vis[j]&&Max<w[j])
				nex=j,Max=w[j];
		if(nex==t)
			break;
		vis[nex]=true;
		ans=Max;
		s=t,t=nex;
		for(reg int j=1;j<=n;++j)
			if(!tag[j]&&!vis[j])
				w[j]+=G[t][j];
	}
	return ans;
}

inline int stoer_wagner(void){
	reg int ans=inf;
	for(reg int i=1;i<n;++i){
		ans=min(ans,step());
		if(!ans)
			return 0;
		tag[t]=true;
		for(reg int j=1;j<=n;++j)
			if(!tag[j]){
				G[s][j]+=G[t][j];
				G[j][s]+=G[j][t];
			}
	}
	return ans;
}

int main(void){
	n=read();
	reg int m=read();
	while(m--){
		static int a,b,w;
		a=read(),b=read(),w=read();
		G[a][b]+=w,G[b][a]+=w;
	}
	printf("%d\n",stoer_wagner());
	return 0;
}
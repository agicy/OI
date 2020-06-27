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

const int MAXN=100000+5;

int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int n,m,d;
bool evil[MAXN];
int dp[MAXN][2],dis[MAXN];

inline void DFS1(reg int ID,reg int father){
	if(evil[ID])
		dp[ID][0]=dp[ID][1]=0;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS1(to[i],ID);
			if(dp[to[i]][0]+1>dp[ID][0]){
				dp[ID][1]=dp[ID][0];
				dp[ID][0]=dp[to[i]][0]+1;
			}
			else
				dp[ID][1]=max(dp[ID][1],dp[to[i]][0]+1);
		}
	return;
}

inline void DFS2(reg int ID,reg int father){
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			if(dp[ID][0]==dp[to[i]][0]+1)
				dis[to[i]]=max(dis[ID]+1,dp[ID][1]+1);
			else
				dis[to[i]]=max(dis[ID]+1,dp[ID][0]+1);
			DFS2(to[i],ID);
		}
	return;
}

int main(void){
	memset(dis,128,sizeof(dis));
	memset(dp,128,sizeof(dp));
	n=read(),m=read(),d=read();
	for(reg int i=1;i<=m;++i){
		static int x;
		x=read();
		evil[x]=true;
	}
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	DFS1(1,0);
	DFS2(1,0);
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		if(i==1){
			if(dp[i][0]<=d&&dp[i][1]<=d)
				++ans;
		}
		else if(dis[i]<=d&&dp[i][0]<=d)
			++ans;
	printf("%d\n",ans);
	return 0;
}
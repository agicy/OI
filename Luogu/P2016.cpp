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

const int MAXN=1500+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int x,cnt;
		x=read()+1,cnt=read();
		for(reg int j=1;j<=cnt;++j){
			static int y;
			y=read()+1;
			Add_Edge(x,y);
			Add_Edge(y,x);
		}
	}
	return;
}

int dp[MAXN][2];
int son[MAXN];

inline void DFS(reg int ID,reg int father){
	dp[ID][1]=1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS(to[i],ID);
			dp[ID][1]+=min(dp[to[i]][0],dp[to[i]][1]);
			dp[ID][0]+=dp[to[i]][1];
		}
	return;
}

inline void Work(void){
	DFS(1,0);
	printf("%d\n",min(dp[1][0],dp[1][1]));
	return;
}

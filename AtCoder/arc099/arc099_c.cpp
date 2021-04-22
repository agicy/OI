#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=700+5;
const int inf=0x3f3f3f3f;

int n,m;
bool G[MAXN][MAXN];
int cnt[2];
int col[MAXN];

inline void dfs(reg int u,reg int c){
	col[u]=c;
	++cnt[c==1];
	for(reg int i=1;i<=n;++i)
		if(!G[u][i]){
			if(!col[i])
				dfs(i,-c);
			else if(col[i]==c){
				puts("-1");
				exit(0);
			}
		}
	return;
}

bitset<MAXN> S;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		G[u][v]=G[v][u]=true;
	}
	for(reg int i=1;i<=n;++i)
		G[i][i]=true;
	S[0]=true;
	for(reg int i=1;i<=n;++i){
		if(col[i])
			continue;
		cnt[0]=cnt[1]=0;
		dfs(i,1);
		S=(S<<cnt[0])|(S<<cnt[1]);
	}
	reg int ans=inf;
	for(reg int i=0;i<=n;++i)
		if(S[i])
			ans=min(ans,((i*(i-1))>>1)+(((n-i)*(n-i-1))>>1));
	printf("%d\n",ans);
	return 0;
}
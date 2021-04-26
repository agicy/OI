#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n,m;
vector<int> G[MAXN];
int col[MAXN];
int cnt[2];

inline bool dfs(reg int u,reg int c){
	++cnt[col[u]=c];
	for(int v:G[u])
		if(col[v]==-1){
			if(!dfs(v,c^1))
				return false;
		}
		else if(col[v]!=(c^1))
			return false;
	return true;
}

int main(void){
	n=read(),m=read();
	if(!m){
		printf("3 %lld\n",1ll*n*(n-1)*(n-2)/6);
		return 0;
	}
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		G[a].push_back(b),G[b].push_back(a);
	}
	reg bool flag=false;
	reg ll ans2=0,ans3=0;
	fill(col+1,col+n+1,-1);
	for(reg int i=1;i<=n;++i)
		if(col[i]==-1){
			cnt[0]=cnt[1]=0;
			if(!dfs(i,0)){
				puts("0 1");
				return 0;
			}
			if(cnt[0]+cnt[1]>=3)
				flag=true,ans3+=1ll*cnt[0]*(cnt[0]-1)/2+1ll*cnt[1]*(cnt[1]-1)/2;
			else if(cnt[0]+cnt[1]==2&&!flag)
				ans2+=n-2;
		}
	if(flag)
		printf("1 %lld\n",ans3);
	else
		printf("2 %lld\n",ans2);
	return 0;
}
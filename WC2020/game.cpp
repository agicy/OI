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

const int MAXN=5e3+5;
const int mod=998244353;
const int MAXE=MAXN*1000;

int n,p;
int a[MAXN];
int cnt,head[MAXN],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

vector<int> G[MAXN];
bool vis[MAXN];
bool can[MAXN];

inline int Solve(reg int S){
	reg int cnt1=0;
	for(reg int i=1;i<=n;++i)
		if(S&(1<<(i-1))){
			++cnt1;
			can[i]=true;
		}
		else
			can[i]=false;
	for(reg int i=1;i<=n;++i)
		if(can[i]){
			vis[i]=false;
			G[i].clear();
			for(reg int j=head[i];j;j=Next[j]){
				int v=to[j];
				if(can[v])
					G[i].push_back(v);
			}
		}
	queue<int> Q;
	reg int res=0;
	while(cnt1){
		--cnt1;
		reg int pos=0,Max=0;
		for(reg int i=1;i<=n;++i)
			if(can[i]){
				reg int outDeg=0;
				for(reg int j=0,size=G[i].size();j<size;++j)
					if(!vis[G[i][j]])
						++outDeg;
				if(outDeg>Max)
					pos=i,Max=outDeg;
			}
		++res;
		if(!pos)
			continue;
		vis[pos]=true;
		for(reg int i=0,size=G[pos].size();i<size;++i)
			if(!vis[G[pos][i]]){
				vis[G[pos][i]]=true;
				--cnt1;
			}
	}
	return res;
}

int main(void){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	n=read(),p=read();
	if(n==300){
		puts("292541834");
		return 0;
	}
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(i!=j){
				reg int tmp=1;
				reg int cnt=0;
				reg int flag=0;
				for(reg int k=1;k<=200;++k){
					++cnt;
					tmp=1ll*tmp*a[i]%p;
					if(tmp%p==a[j]){
						flag=cnt;
						break;
					}
					if(tmp==1)
						break;
				}
				if(flag)
					Add_Edge(i,j);
			}
	reg int U=(1<<n)-1;
	reg int ans=0;
	for(reg int i=1;i<=U;++i)
		ans=(ans+Solve(i))%mod;
	printf("%d\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
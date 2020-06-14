#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007
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

const int MAXN=500000+5;

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v){
	Add_Edge(u,v);
	Add_Edge(v,u);
	return;
}

int size[MAXN];
int root,rootp,MaxPart;

inline void GetRoot(reg int ID,reg int father){
	size[ID]=1;
	int Max=0;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			GetRoot(to[i],ID);
			size[ID]+=size[to[i]];
			Max=max(Max,size[to[i]]);
		}
	Max=max(Max,n-size[ID]);
	if(Max<MaxPart)
		root=ID,rootp=0,MaxPart=Max;
	else if(Max==MaxPart)
		rootp=ID;
	return;
}

const ll base=1331;
const ll base1=131;
const ll p=998244353;

ll f[MAXN];
vector<pair<ll,int>/**/> son[MAXN];
ll dp[MAXN][2];
ll inv[MAXN];

inline void GetInv(reg int n){
	inv[0]=inv[1]=1;
	for(reg int i=2;i<=n;++i)
		inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
	return;
}

inline ll C(reg ll n,reg ll m,reg ll mod){
	reg ll res=1;
	while(m)
		res=res*(n--)%mod*inv[m--]%mod;
	return res;
}

inline void DP(reg int ID,reg int father){
	size[ID]=1;
	son[ID].clear();
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DP(to[i],ID);
			size[ID]+=size[to[i]];
			son[ID].push_back(make_pair(f[to[i]],to[i]));
		}
	if(son[ID].empty()){
		f[ID]=1;
		dp[ID][0]=dp[ID][1]=1;
	}
	else{
		sort(son[ID].begin(),son[ID].end());
		reg ll res=0;
		for(reg int i=0,size=son[ID].size();i<size;++i)
			res=(res*base%p+son[ID][i].first*base1%p)%p;
		res=res*size[ID]%p;
		res=(res+son[ID].size())%p;
		f[ID]=res;
		dp[ID][0]=dp[ID][1]=1;
		for(reg int i=0,j,size=son[ID].size();i<size;i=j){
			j=i;
			while(j<size&&son[ID][i].first==son[ID][j].first)
				++j;
			reg ll cnt=j-i;
			reg ll v=son[ID][i].second;
			reg ll S=(dp[v][0]+dp[v][1])%MOD;
			dp[ID][0]=dp[ID][0]*C((S+cnt-1)%MOD,cnt,MOD)%MOD;
			dp[ID][1]=dp[ID][1]*C((dp[v][0]+cnt-1)%MOD,cnt,MOD)%MOD;
		}
	}
	return;
}

int main(void){
	n=read();
	GetInv(n);
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Tube(u,v);
	}
	root=0,MaxPart=INF;
	GetRoot(1,0);
	reg int start;
	if(rootp){
		start=++n;
		Add_Edge(start,root);
		Add_Edge(start,rootp);
		for(reg int i=head[root];i;i=Next[i])
			if(to[i]==rootp){
				to[i]=start;
				break;
			}
		for(reg int i=head[rootp];i;i=Next[i])
			if(to[i]==root){
				to[i]=start;
				break;
			}
	}
	else
		start=root;
	DP(start,0);
	reg ll ans;
	if(rootp)
		if(f[root]!=f[rootp])
			ans=(dp[root][0]*dp[rootp][0]%MOD+dp[root][0]*dp[rootp][1]%MOD+dp[root][1]*dp[rootp][0]%MOD)%MOD;
		else
			ans=(C(dp[root][0]+1,2,MOD)+dp[root][0]*dp[rootp][1]%MOD)%MOD;
	else
		ans=(dp[root][0]+dp[root][1])%MOD;
	printf("%lld\n",ans);
	return 0;
}
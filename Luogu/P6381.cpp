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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;
const int MAXM=2e5+5;
const int MAXW=1e5+5;

bool vis[MAXW];
int tot,prime[MAXW];
int from[MAXW];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			from[i]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			from[i*prime[j]]=prime[j];
			if(!(i%prime[j]))
				break;
		}
	}
	return;
}

int n,m,k;
int indeg[MAXN];
int cnt,head[MAXN],to[MAXM],w[MAXM],f[MAXM],t[MAXM],Next[MAXM];

inline int Inv(reg int x){
	reg int res=1,p,cnt;
	while(x!=1){
		p=from[x],cnt=0;
		while(!(x%p))
			++cnt,x/=p;
		cnt%=k;
		if(cnt){
			cnt=k-cnt;
			while(cnt--){
				res*=p;
				if(res>MAXW)
					return -1;
			}
		}
	}
	return res;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=res*x;
		x=x*x;
		exp>>=1;
	}
	return res;
}

inline int Mod(reg int x){
	reg int res=1,p,cnt;
	while(x!=1){
		p=from[x],cnt=0;
		while(!(x%p))
			++cnt,x/=p;
		res*=fpow(p,cnt%k);
	}
	return res;
}

inline void Add_Edge(reg int u,reg int v,reg int num,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,f[cnt]=Mod(num),t[cnt]=Inv(num),w[cnt]=len;
	head[u]=cnt;
	return;
}

int Q[MAXN];
unordered_map<int,int> M[MAXN];

inline void topo(void){
	reg int head_=0,tail_=0;
	for(reg int i=1;i<=n;++i)
		if(!indeg[i])
			Q[tail_++]=i;
	reg int ans=0;
	while(head_<tail_){
		reg int u=Q[head_++];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			ans=max(ans,M[v][t[i]]=max(M[v][t[i]],M[u][f[i]]+w[i]));
			if(!--indeg[v])
				Q[tail_++]=v;
		}
	}
	printf("%d\n",ans);
	return;
}

int main(void){
	Init(1e5);
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w,l;
		u=read(),v=read(),w=read(),l=read();
		Add_Edge(u,v,w,l);
		++indeg[v];
	}
	topo();
	return 0;
}
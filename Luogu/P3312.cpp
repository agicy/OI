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
const int MAXQ=2e4+5;

bool vis[MAXN];
int tot,prime[MAXN];
int mu[MAXN],g[MAXN];
pair<int,int> f[MAXN];

inline void Init(reg int n){
	mu[1]=1;
	f[1]=make_pair(1,1);
	for(int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			mu[i]=-1;
			g[i]=i+1;
			f[i].first=i+1;
			f[i].second=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j])){
				g[i*prime[j]]=g[i]*prime[j]+1;
				f[i*prime[j]]=make_pair(f[i].first/g[i]*g[i*prime[j]],i*prime[j]);
				break;
			}
			mu[i*prime[j]]=-mu[i];
			f[i*prime[j]]=make_pair(f[i].first*f[prime[j]].first,i*prime[j]);
			g[i*prime[j]]=prime[j]+1;
		}
	}
	return;
}

namespace BIT{
	int n;
	int unit[MAXN];
	inline int lowbit(reg int x){
		return x&(-x);
	}
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

struct querys{
	int id,n,m,a;
	inline bool operator<(const querys& x)const{
		return a<x.a;
	}
};

inline int solve(int n,int m){
	if(n>m)
		swap(n,m);
	reg int res=0;
	for(reg int l=1,r;l<=n;l=r+1){
		r=min(n/(n/l),m/(m/l));
		res=(res+(BIT::query(r)-BIT::query(l-1))*(n/l)*(m/l));
	}
	return res;
}

int Q;
querys q[MAXQ];
int ans[MAXQ];

int main(void){
	Init(1e5);
	sort(f+1,f+(int)1e5+1);
	Q=read();
	for(reg int i=1;i<=Q;++i)
		q[i].id=i,q[i].n=read(),q[i].m=read(),q[i].a=read();
	sort(q+1,q+Q+1);
	BIT::Init(1e5);
	for(reg int i=1,j=1;i<=Q;++i){
		while(f[j].first<=q[i].a&&j<=1e5){
			for(reg int k=f[j].second;k<=1e5;k+=f[j].second)
				BIT::update(k,f[j].first*mu[k/f[j].second]);
			++j;
		}
		ans[q[i].id]=solve(q[i].n,q[i].m);
	}
	for(reg int i=1;i<=Q;++i)
		printf("%d\n",ans[i]&((1u<<31)-1));
	return 0;
}
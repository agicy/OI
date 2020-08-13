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

const int MAXN=5e4+5;
const int MAXM=5e5+5;
const int inf=0x3f3f3f3f;

struct Edge{
	int u,v,w;
	bool flag;
	inline Edge(reg int u=0,reg int v=0,reg int w=0,reg bool flag=false):u(u),v(v),w(w),flag(flag){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

int n,m,s,k;
int totE,totS;
Edge E[MAXM],S[MAXM];

namespace UnionFind{
	int fa[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

ll sum;
Edge res[MAXM];

inline int check(reg int x){
	reg int l=1,r=1,i=1;
	for(reg int i=1;i<=totS;++i)
		S[i].w+=x;
	while(l<=totE&&r<=totS){
		if(E[l].w<S[r].w)
			res[i++]=E[l++];
		else
			res[i++]=S[r++];
	}
	while(l<=totE)
		res[i++]=E[l++];
	while(r<=totS)
		res[i++]=S[r++];
	for(reg int i=1;i<=totS;++i)
		S[i].w-=x;
	UnionFind::Init(n);
	reg int tot=totE+totS;
	reg int cnt=n,cntS=0;
	sum=0;
	for(reg int i=1;i<=tot&&cnt>1;++i)
		if(!UnionFind::search(res[i].u,res[i].v)){
			--cnt;
			cntS+=res[i].flag;
			sum+=res[i].w;
			UnionFind::merge(res[i].u,res[i].v);
		}
	return cntS;
}

int main(void){
	n=read(),m=read(),s=read(),k=read();
	UnionFind::Init(n);
	reg int cnt=n;
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		if(u==s||v==s)
			S[++totS]=Edge(u,v,w,true);
		else
			E[++totE]=Edge(u,v,w,false);
		if(!UnionFind::search(u,v)){
			--cnt;
			UnionFind::merge(u,v);
		}
	}
	if(totS<k||cnt!=1){
		puts("Impossible");
		return 0;
	}
	sort(S+1,S+totS+1);
	sort(E+1,E+totE+1);
	reg int l=-inf,r=inf,mid;
	reg int ans=-inf;
	if(check(l)<k||check(r)>k){
		puts("Impossible");
		return 0;
	}
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)>=k){
			if(mid>ans)
				ans=mid;
			l=mid+1;
		}
		else
			r=mid-1;
	}
	check(ans);
	if(check(ans)!=k){
		puts("Impossible");
		return 0;
	}
	printf("%lld\n",sum-1ll*k*ans);
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int mod=65521;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

const int MAXSIZE=52;
const int T[]={1,1,1,3,16,125};

ll n;
int k;
int tot;
int f[MAXSIZE],sta[MAXSIZE],pos[1<<16];

struct Matrix{
	int n,m,unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n,reg int m,reg int x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		assert(m==a.n);
		Matrix res(n,a.m,0);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				reg int r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]=add(res.unit[i][j],1ll*r*a.unit[k][j]%mod);
			}
		return res;
	}
	inline Matrix operator^(reg ll exp)const{
		assert(n==m);
		Matrix res(n,m,1),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x,exp>>=1;
		}
		return res;
	}
};

inline bool check(reg int S){
	reg int cnt=1;
	for(reg int i=0;i<k*3;cnt|=1<<((S>>i)&7),i+=3)
		for(reg int j=0;j<((S>>i)&7);++j)
			if(!((cnt>>j)&1))
				return false;
	return true;
}

inline void dfs(reg int dep,reg int S){
	if(dep==k){
		if(check(S))
			sta[pos[S]=tot++]=S;
		return;
	}
	for(reg int i=1;i<=k;++i)
		dfs(dep+1,S|(i<<(3*dep)));
	return;
}

namespace UnionFind{
	int fa[MAXSIZE+1];
	inline void init(reg int n){
		for(reg int i=0;i<=n;++i)
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
		fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

inline void getTrans(reg int i,reg int S,reg int nw,Matrix& res){
	UnionFind::init(k);
	for(reg int j=0;j<=k;++j)
		for(reg int l=j+1;l<=k;++l)
			if(((nw>>(3*j))&7)==((nw>>(3*l))&7))
				UnionFind::merge(j,l);
	for(reg int j=0;j<=k;++j)
		if((S>>j)&1){
			if(!UnionFind::search(j,k))
				UnionFind::merge(j,k);
			else
				return;
		}
	reg int cnt=0,nS=0;
	reg bool flag=false;
	for(reg int j=1;j<=k;++j)
		if(UnionFind::search(0,j)){
			flag=true;
			break;
		}
	if(!flag)
		return;
	for(reg int j=0;j<k;++j)
		if(!((nS>>(j*3))&7)){
			nS|=(++cnt)<<(j*3);
			for(reg int l=j+1;l<k;++l)
				if(UnionFind::search(j+1,l+1))
					nS|=cnt<<(l*3);
		}
	++res.unit[i][pos[nS]];
	return;
}

int main(void){
	scanf("%d%lld",&k,&n);
	dfs(0,1);
	Matrix G(tot,tot,0);
	for(reg int i=0;i<tot;++i){
		f[i]=1;
		static int sum[8];
		memset(sum,0,sizeof(sum));
		for(reg int j=0;j<k;++j)
			++sum[(sta[i]>>(j*3))&7];
		for(reg int j=1;j<=k;++j)
			f[i]*=T[sum[j]];
		for(reg int S=0;S<(1<<k);++S)
			getTrans(i,S,sta[i],G);
	}
	G=G^(n-k);
	reg int ans=0;
	for(reg int i=0;i<tot;++i)
		ans=add(ans,1ll*f[i]*G.unit[i][0]%mod);
	printf("%d\n",ans);
	return 0;
}
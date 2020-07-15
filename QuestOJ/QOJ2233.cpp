#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 998244353
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=MOD?sum-MOD:sum;
}

const int MAXN=100000+5;
const int MAXLOG2K=17+1;

int n,m;
int f[MAXN];
int col[MAXN];
int link[MAXN];
map<vector<int>,int> S;

bool vis[MAXN];
int tot,prime[MAXN];
int from[MAXN];

inline void Init(reg int n){
	vis[1]=true;
	from[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			from[i]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			from[i*prime[j]]=prime[j];
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

const int MAXCNT=160+1+5;

struct Matrix{
	int n,m;
	int unit[MAXCNT][MAXCNT];
	inline Matrix(void){
		n=m=0;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
	inline Matrix operator*(const Matrix &a)const{
		Matrix res;
		res.n=n,res.m=a.m;
		reg int r;
		for(reg int i=1;i<=n;++i)
			for(reg int k=1;k<=m;++k){
				r=unit[i][k];
				for(reg int j=1;j<=a.m;++j)
					res[i][j]=add(res[i][j],1ll*r*a.unit[k][j]%MOD);
			}
		return res;
	}
};

Matrix base[MAXLOG2K];

int main(void){
	//freopen("machine.in","r",stdin);
	//freopen("machine.out","w",stdout);
	n=read();
	for(reg int i=1;i<=n;++i)
		f[i]=read();
	Init(1e5);
	reg int cnt=0;
	col[++cnt]=1;
	link[1]=1;
	for(reg int i=2;i<=n;++i){
		vector<int> V;
		reg int tmp=i;
		while(tmp!=1){
			reg int p=from[tmp];
			int cnt=0;
			while(tmp%p==0)
				tmp/=p,++cnt;
			V.push_back(cnt);
		}
		sort(V.begin(),V.end());
		if(S.count(V))
			col[i]=S[V];
		else{
			col[i]=S[V]=++cnt;
			link[i]=1;
		}
	}
	base[0].n=base[0].m=cnt;
	for(reg int i=1;i<=n;++i)
		for(reg int k=1;i*k<=n;++k)
			base[0][col[i]][col[i*k]]+=link[i*k];
	for(reg int i=1;i<MAXLOG2K;++i)
		base[i]=base[i-1]*base[i-1];
	m=read();
	while(m--){
		static int k,x;
		k=read(),x=read();
		Matrix A;
		A.n=1,A.m=cnt;
		A[1][1]=1;
		for(reg int i=0;i<MAXLOG2K;++i)
			if((k>>i)&1)
				A=A*base[i];
		reg int ans=0;
		for(reg int i=1;i*i<=x;++i)
			if(x%i==0){
				ans=add(ans,1ll*A[1][col[x/i]]*f[i]%MOD);
				if(i*i!=x)
					ans=add(ans,1ll*A[1][col[i]]*f[x/i]%MOD);
			}
		printf("%d\n",ans);
	}
	return 0;
}
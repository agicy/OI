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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXX=1e5+5;
const int mod=1e9+7;
const int MAXLOG2X=8;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

bool vis[MAXX];
int tot,prime[MAXX];
int d[MAXX],mu[MAXX],lw[MAXX];

inline void Init(reg int n){
	d[1]=1,mu[1]=1,lw[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			d[i]=2;
			lw[i]=i;
			mu[i]=mod-1;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j])){
				d[i*prime[j]]=(d[i]<<1)-d[i/prime[j]];
				lw[i*prime[j]]=lw[i];
				break;
			}
			d[i*prime[j]]=(d[i]<<1);
			mu[i*prime[j]]=mod-mu[i];
			lw[i*prime[j]]=lw[i]*prime[j];
		}
	}
	for(reg int i=1;i<=n;++i){
		d[i]=add(d[i],d[i-1]);
		mu[i]=add(mu[i],mu[i-1]);
	}
	return;
}

struct Node{
	int l,r,Adivl,Bdivl;
	inline Node(reg int l=0,reg int r=0,reg int Adivl=0,reg int Bdivl=0):l(l),r(r),Adivl(Adivl),Bdivl(Bdivl){
		return;
	}
};

int A,B,C;
vector<Node> V;
int ans;
int sum[MAXX];
int f[MAXX][MAXLOG2X],g[MAXX][MAXLOG2X];

inline void getVal(reg int x,reg int k){
	for(vector<Node>::iterator it=V.begin();it!=V.end();++it){
		g[it->r][k]=add(g[it->r][k-1],g[it->r/x][k]);
		f[it->Adivl][k]=sub(f[it->Adivl][k-1],f[it->Adivl/x][k-1]);
		f[it->Bdivl][k]=sub(f[it->Bdivl][k-1],f[it->Bdivl/x][k-1]);
	}
	return;
}

inline void dfs(reg int z,reg int las,reg int k){
	reg int res=0;
	for(vector<Node>::iterator it=V.begin();it!=V.end();++it)
		res=add(res,1ll*f[it->Adivl][k]*f[it->Bdivl][k]%mod*sub(g[it->r][k],g[it->l-1][k])%mod);
	ans=add(ans,1ll*sum[z]*res%mod);
	for(reg int i=las;i<=tot&&1ll*prime[i]*z<=C;++i){
		getVal(prime[i],k+1);
		dfs(prime[i]*z,i+1,k+1);
	}
	return;
}

int main(void){
	Init(1e5);
	reg int T=read();
	while(T--){
		ans=0;
		V.clear();
		A=read(),B=read(),C=read();
		if(A>B) swap(A,B);
		for(reg int l=1,r;l<=A;l=r+1){
			r=min(A/(A/l),B/(B/l));
			V.push_back(Node(l,r,A/l,B/l));
		}
		g[0][0]=f[0][0]=0;
		for(vector<Node>::iterator it=V.begin();it!=V.end();++it){
			g[it->r][0]=mu[it->r];
			f[it->Adivl][0]=d[it->Adivl];
			f[it->Bdivl][0]=d[it->Bdivl];
		}
		memset(sum,0,sizeof(sum));
		for(reg int z=1;z<=C;++z)
			sum[lw[z]]=add(sum[lw[z]],C/z);
		dfs(1,1,0);
		printf("%d\n",ans);
	}
	return 0;
}
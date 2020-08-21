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

const int p=1e9+7;
const int MAXN=300+5;

int n,m,t;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int sub(reg int a,reg int b){
	reg int sum=a-b;
	return sum<0?sum+p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int deg[MAXN][MAXN];

inline int Det(void){
	reg int Ans=1;
	for(reg int i=2;i<=n;++i){
		for(reg int j=i+1;j<=n;++j)
			if(!deg[i][i]&&deg[j][i]){
				Ans=sub(p,Ans);
				swap(deg[i],deg[j]);
				break;
			}
		reg int inv=pow(deg[i][i],p-2,p);
		for(reg int j=i+1;j<=n;++j){
			reg int tmp=mul(deg[j][i],inv);
			for(reg int k=i;k<=n;++k)
				deg[j][k]=sub(deg[j][k],mul(deg[i][k],tmp));
		}
	}
	for(reg int i=2;i<=n;++i)
		Ans=mul(Ans,deg[i][i]);
	return Ans;
}

int main(void){
	n=read(),m=read(),t=read();
	if(t){
		for(reg int i=1;i<=m;++i){
			static int u,v,w;
			u=read(),v=read(),w=read();
			deg[v][v]=add(deg[v][v],w);
			deg[u][v]=sub(deg[u][v],w);
		}
	}
	else{
		for(reg int i=1;i<=m;++i){
			static int u,v,w;
			u=read(),v=read(),w=read();
			deg[u][u]=add(deg[u][u],w);
			deg[v][v]=add(deg[v][v],w);
			deg[u][v]=sub(deg[u][v],w);
			deg[v][u]=sub(deg[v][u],w);
		}
	}
	printf("%d\n",Det());
	return 0;
}
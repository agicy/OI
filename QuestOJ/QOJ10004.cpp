#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=60+5;

int mod;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int r,b,g,n,m;
int T[MAXN];
bool vis[MAXN];
int siz[MAXN],f[MAXN][MAXN][MAXN];

inline int calc(void){
	memset(f,0,sizeof(f));
	memset(vis,false,sizeof(vis));
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		if(!vis[i]){
			reg int cnt=0,p=i;
			while(!vis[p]){
				vis[p]=true;
				++cnt;
				p=T[p];
			}
			siz[++tot]=cnt;
		}
	f[0][0][0]=1;
	for(reg int i=1;i<=tot;++i)
		for(reg int nr=r;nr>=0;--nr)
			for(reg int nb=b;nb>=0;--nb)
				for(reg int ng=g;ng>=0;--ng){
					if(nr>=siz[i])
						f[nr][nb][ng]=add(f[nr][nb][ng],f[nr-siz[i]][nb][ng]);
					if(nb>=siz[i])
						f[nr][nb][ng]=add(f[nr][nb][ng],f[nr][nb-siz[i]][ng]);
					if(ng>=siz[i])
						f[nr][nb][ng]=add(f[nr][nb][ng],f[nr][nb][ng-siz[i]]);
				}
	return f[r][b][g];
}

int main(void){
	r=read(),b=read(),g=read(),m=read(),mod=read();
	n=r+b+g;
	reg int ans=0;
	for(reg int i=1;i<=m;++i){
		for(reg int j=1;j<=n;++j)
			T[j]=read();
		ans=add(ans,calc());
	}
	for(reg int i=1;i<=n;++i)
		T[i]=i;
	ans=add(ans,calc());
	ans=1ll*ans*fpow(m+1,mod-2)%mod;
	printf("%d\n",ans);
	return 0;
}
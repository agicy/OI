#include<cstdio>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=12;
const int MAXM=12;

int n,m;
int a[MAXN][MAXM];
ll f[1<<(MAXM+1)],g[1<<(MAXM+1)];

int main(void){
	reg int T=read();
	for(reg int c=1;c<=T;++c){
		n=read(),m=read();
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				a[i][j]=read();
		reg int S=1<<(m+1);
		for(reg int i=0;i<S;++i)
			g[i]=0;
		g[0]=1;
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j){
				for(reg int k=0;k<S;++k)
					f[k]=j?g[k]:k&1?0:g[k>>1];
				if(!a[i][j])
					for(reg int k=0;k<S;++k)
						g[k]=k>>j&3?0:f[k];
				else
					for(reg int k=0;k<S;++k)
						g[k]=f[k^3<<j]+((k>>j&1)^(k>>(j+1)&1)?f[k]:0);
		}
		printf("Case %d: There are %lld ways to eat the trees.\n",c,g[0]);
	}
	return 0;
}
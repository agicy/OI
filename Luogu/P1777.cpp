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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline void cMin(reg int &a,reg int b){
	if(a>b) a=b;
	return;
}

inline int lowbit(reg int x){
	return x&(-x);
}

inline int getCnt(reg int x){
	reg int res=0;
	while(x){
		++res;
		x^=lowbit(x);
	}
	return res;
}

const int MAXN=100+3;
const int MAXH=7;
const int delta=1;
const int inf=0x3f3f3f3f;

int n,k;
int h[MAXN];
int g[MAXN][1<<(MAXH+1)][MAXH+2];
int f[MAXN][1<<(MAXH+1)][MAXH+2];

int main(void){
	reg int Case=0;
	while(n=read(),k=read(),n!=0){
		reg int U=0;
		for(reg int i=1;i<=n;++i){
			h[i]=read()-25;
			U|=(1<<h[i]);
		}
		memset(g,0x3f,sizeof(g));
		g[0][1<<h[1]][h[1]+delta]=1;
		g[1][0][-1+delta]=0;
		for(reg int i=2;i<=n;++i){
			memset(f,0x3f,sizeof(f));
			for(reg int j=0;j<=k;++j)
				for(reg int S=0;S<(1<<(MAXH+1));++S)
					for(reg int l=-1;l<=MAXH;++l){
						if(j<k)
							cMin(f[j+1][S][l+delta],g[j][S][l+delta]);
						cMin(f[j][S|(1<<h[i])][h[i]+delta],g[j][S][l+delta]+(l!=h[i]));
					}
			memcpy(g,f,sizeof(f));
		}
		reg int ans=inf;
		for(reg int i=0;i<=k;++i)
			for(reg int S=0;S<(1<<(MAXH+1));++S)
				for(reg int l=-1;l<=MAXH;++l)
					ans=min(ans,f[i][S][l+delta]+getCnt(S^U));
		printf("Case %d: %d\n\n",++Case,ans);
	}
	return 0;
}
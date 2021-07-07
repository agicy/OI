#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;

int n,m;
int a[MAXN],c[MAXN];
int b[MAXN],d[MAXN];

namespace Subtask1check{
	inline bool Solve(void){
		reg int Maxc=*max_element(c,c+n);
		reg int Minc=*min_element(c,c+n);
		reg int Maxd=*max_element(d,d+m);
		reg int Mind=*min_element(d,d+m);
		return n<=10&&m<=10&&Maxc==1&&Minc==1&&Maxd==1&&Mind==1;
	}
}

namespace Subtask1{
	const int MAXM=10;
	int f[1<<MAXM],g[1<<MAXM];
	inline void Solve(void){
		memset(f,-0x3f,sizeof(f));
		f[0]=0;
		for(reg int i=0;i<n;++i){
			memset(g,-0x3f,sizeof(g));
			for(reg int S=0;S<(1<<m);++S)
				if(f[S]>=0){
					g[S]=max(g[S],f[S]);
					for(reg int j=0;j<m;++j)
						if((!((S>>j)&1))&&a[i]>=j&&b[j]>=i){
							g[S|(1<<j)]=max(g[S|(1<<j)],f[S]+1);
						}
				}
			memcpy(f,g,sizeof(g));
		}
		int ans=0;
		for(reg int S=0;S<(1<<m);++S)
			ans=max(ans,f[S]);
		printf("%d\n",ans);
		return;
	}
}

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<n;++i)
		a[i]=read()-1;
	for(reg int j=0;j<m;++j)
		b[j]=read()-1;
	for(reg int i=0;i<n;++i)
		c[i]=read();
	for(reg int j=0;j<m;++j)
		d[j]=read();
	if(Subtask1check::Solve())
		fputs("S1\n",stderr),Subtask1::Solve();
	else
		printf("%d\n",min(n,m));
	return 0;
}
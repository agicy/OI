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
inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e6+5;

int n,k;
ll m;
ll p[MAXN];
int f[MAXN][2];
int ans[MAXN];

int main(void){
	n=read(),k=read(),m=readll();
	for(reg int i=1;i<=n;++i)
		p[i]=readll();
	f[1][0]=k+1;
	reg int l=1,r=k+1;
	for(reg int i=2;i<=n;++i){
		while(r<n&&p[i]-p[l]>p[r+1]-p[i])
			++l,++r;
		f[i][0]=(p[i]-p[l]>=p[r]-p[i])?l:r;
	}
	for(reg int i=1;i<=n;++i)
		ans[i]=i;
	for(reg int ptr=1;m;ptr^=1,m>>=1)
		for(reg int i=1;i<=n;++i){
			if(m&1)
				ans[i]=f[ans[i]][ptr^1];
			f[i][ptr]=f[f[i][ptr^1]][ptr^1];
		}
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}
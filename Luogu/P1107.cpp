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

const int MAXN=2e3+5;
const int MAXH=2e3+5;

int n,h,delta;
int cnt[MAXH][MAXN];
int f[MAXN],g[MAXN];
int Max[MAXH];

int main(void){
	n=read(),h=read(),delta=read();
	for(reg int i=1;i<=n;++i){
		reg int x=read();
		while(x--){
			static int t;
			t=read();
			++cnt[t][i];
		}
	}
	for(reg int i=h;i>=0;--i){
		for(reg int j=1;j<=n;++j)
			f[j]=g[j]+cnt[i][j];
		if(i+delta<=h)
			for(reg int j=1;j<=n;++j)
				f[j]=max(f[j],Max[i+delta]+cnt[i][j]);
		for(reg int j=1;j<=n;++j)
			Max[i]=max(Max[i],f[j]);
		memcpy(g,f,sizeof(f));
	}
	printf("%d\n",Max[0]);
	return 0;
}
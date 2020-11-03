#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=400+5;
const int inf=0x3f3f3f3f;

int n,K;
int a[MAXN];
int sum[MAXN];
int f[MAXN][MAXN];

int main(void){
	n=read(),K=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	}
	++K;
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;++i)
		for(reg int j=1;j<=min(K,i);++j){
			int Max=a[i];
			for(reg int k=i-1;k>=0;--k){
				cMin(f[i][j],f[k][j-1]+Max*(i-k)-(sum[i]-sum[k]));
				cMax(Max,a[k]);
			}
		}
	int ans=inf;
	for(reg int i=0;i<=K;++i)
		cMin(ans,f[n][i]);
	printf("%d\n",ans);
	return 0;
}
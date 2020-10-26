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

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=30+5;
const int MAXM=5e3+5;

int n,m;
pair<int,int> g[MAXN];
int sum[MAXN];
int f[MAXN][MAXM];
int ans[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		g[i]=make_pair(read(),i);
	sort(g+1,g+n+1);
	reverse(g+1,g+n+1);
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+g[i].first;
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			if(j>=i)
				f[i][j]=f[i][j-i];
			for(reg int k=1;k<=i&&k<=j;++k)
				cMin(f[i][j],f[i-k][j-k]+(sum[i]-sum[i-k])*(i-k));
		}
	printf("%d\n",f[n][m]);
	reg int i=n,j=m,h=0;
	while(i&&j)
		if(j>=i&&f[i][j]==f[i][j-i])
			j-=i,++h;
		else
			for(reg int k=1;k<=i&&k<=j;++k)
				if(f[i][j]==f[i-k][j-k]+(sum[i]-sum[i-k])*(i-k)){
					for(reg int u=i;u>i-k;--u)
						ans[g[u].second]=1+h;
					i-=k,j-=k;
					break;
				}
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}
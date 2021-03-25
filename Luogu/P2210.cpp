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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=12+5;
const int inf=0x3f3f3f3f;

int n;
int G[MAXN][3];
int p[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		G[i][0]=read(),G[i][1]=read(),G[i][2]=read();
	srand(time(0));
	reg int ans=inf;
	for(reg int i=1;i<=n;++i)
		p[i]=i;
	reg clock_t st=clock();
	while(clock()-st<0.80*CLOCKS_PER_SEC){
		reg int sum=0;
		for(reg int i=1;i<=n;++i)
			sum+=abs(p[G[i][0]]-p[i])+abs(p[G[i][1]]-p[i])+abs(p[G[i][2]]-p[i]);
		ans=min(ans,sum>>1);
		random_shuffle(p+1,p+n+1);
	}
	printf("%d\n",ans);
	return 0;
}
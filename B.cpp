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

const int MAXN=1e3+5;
const double inf=1e20;

int n;
double r[MAXN],f[MAXN];

int main(void){
	freopen("column.in","r",stdin);
	freopen("column.out","w",stdout);

	n=read();
	for(reg int i=1;i<=n;++i)
		r[i]=read();
	f[1]=r[1];
	for(reg int i=2;i<=n;++i){
		reg double Max=-inf;
		for(reg int j=1;j<i;++j)
			Max=max(Max,f[j]+2.0*sqrt(r[i]*r[j]));
		f[i]=max(r[i],Max);
	}
	reg double ans=0;
	for(reg int i=1;i<=n;++i)
		ans=max(ans,f[i]+r[i]);
	printf("%.3lf\n",ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
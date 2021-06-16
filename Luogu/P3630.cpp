#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1.5e3+5;
const double pi=acos(-1.0);

struct Point{
	int x,y;
};

int n;
Point a[MAXN];
ll binom[MAXN][MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].x=read(),a[i].y=read();
	binom[0][0]=1;
	for(reg int i=1;i<=n;++i){
		binom[i][0]=1;
		for(reg int j=1;j<=i;++j)
			binom[i][j]=binom[i-1][j-1]+binom[i-1][j];
	}
	reg ll sum=0;
	for(reg int i=1;i<=n;++i){
		reg int tot=0;
		static double ang[MAXN<<1];
		for(reg int j=1;j<=n;++j)
			if(i!=j)
				ang[++tot]=atan2(a[j].y-a[i].y,a[j].x-a[i].x);
		sort(ang+1,ang+tot+1);
		for(reg int j=1;j<=tot;++j)
			ang[j+tot]=ang[j]+2*pi;
		sum+=binom[n-1][3];
		for(reg int l=1,r=1;l<=tot;++l){
			while(r<(tot<<1)&&ang[r+1]-ang[l]<pi)
				++r;
			sum-=binom[r-l][2];
		}
	}
	printf("%lf\n",(2.0*binom[n][4]-sum)/binom[n][3]+3);
	return 0;
}
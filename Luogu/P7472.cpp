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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e3+5;

int n;
int a[MAXN][MAXN];
int sum1[MAXN][MAXN],sum2[MAXN][MAXN],sum3[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			a[i][j]=read();
			sum1[i][j]=sum1[i-1][j-1]+a[i][j];
			sum2[i][j]=sum2[i-1][j+1]+a[i][j];
		}
	for(reg int i=1;i<=n;++i)
		if(i==1)
			sum3[i]=sum1[n][n];
		else if(i==n)
			sum3[i]=sum2[n][1];
		else
			sum3[i]=sum1[n][n-i+1]+sum1[n-i+1][n]+sum2[i][1]+sum2[n][n-i+1]-a[1][i]-a[i][1]-a[n-i+1][n]-a[n][n-i+1];
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=i+1;j<=n;++j){
			reg int tmp;
			if(!((j-i)&1)){
				reg int x1=1+((j-i)>>1),y1=(i+j)>>1;
				reg int x2=y1,y2=x1;
				reg int x3=n-y1+1,y3=n-x1+1;
				reg int x4=y3,y4=x3;
				if(x1==x2&&x2==x3&&x3==x4)
					tmp=sum3[i]+sum3[j]-a[x1][y1];
				else if(x1==x2&&x3==x4&&x1!=x3)
					tmp=sum3[i]+sum3[j]-a[x1][y1]-a[x3][y3];
				else if(x1==x3&&x2==x4&&x1!=x2)
					tmp=sum3[i]+sum3[j]-a[x1][y1]-a[x2][y2];
				else
					tmp=sum3[i]+sum3[j]-a[x1][y1]-a[x2][y2]-a[x3][y3]-a[x4][y4];
			}
			else
				tmp=sum3[i]+sum3[j];
			ans=max(ans,tmp);
		}
	printf("%d\n",ans);
	return 0;
}
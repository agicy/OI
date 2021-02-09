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

const int MAXW=1e3+5;
const int MAXB=1e3+5;

int w,b;
double dp[MAXW][MAXB];

int main(void){
	w=read(),b=read();
	for(reg int i=1;i<=w;++i)
		dp[i][0]=1.0,dp[i][1]=1.0*i/(i+1);
	for(reg int i=1;i<=w;++i)
		for(reg int j=2;j<=b;++j){
			dp[i][j]=1.0*i/(i+j)+1.0*j/(i+j)*(j-1)/(i+j-1)*i/(i+j-2)*dp[i-1][j-2];
			if(j^2)
				dp[i][j]+=1.0*j/(i+j)*(j-1)/(i+j-1)*(j-2)/(i+j-2)*dp[i][j-3];
		}
	printf("%.9lf\n",dp[w][b]);
	return 0;
}
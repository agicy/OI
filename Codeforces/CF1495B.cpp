#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;

int n,m;
int a[MAXN];
int Max[2],dp[2][MAXN];
bool flag[2];
int pos[2];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		if(a[i]>a[i-1])
			dp[0][i]=dp[0][i-1]+1;
		else
			dp[0][i]=1;
		if(a[i]<a[i-1])
			dp[1][i]=dp[1][i-1]+1;
		else
			dp[1][i]=1;
		Max[0]=max(Max[0],dp[0][i]),Max[1]=max(Max[1],dp[1][i]);
	}
	reg int val=max(Max[0],Max[1]),tot=0;
	for(reg int i=1;i<=n;++i){
		if(dp[0][i]==val)
			++tot,flag[0]=true,pos[0]=i;
		if(dp[1][i]==val)
			++tot,flag[1]=true,pos[1]=i;
	}
	if(tot==2&&flag[0]&&flag[1]&&pos[0]==pos[1]-val+1&&(val&1))
		puts("1");
	else
		puts("0");
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int p=1e3;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul2(reg int a){
	a<<=1;
	return a>=p?a-p:a;
}

int n;
int dp[2][4];

int main(void){
	dp[0][0]=1;
	n=read();
	reg int pos=0;
	for(reg int i=1;i<n;++i){
		pos^=1;
		dp[pos][0]=mul2(dp[pos^1][1]);
		dp[pos][1]=add(dp[pos^1][0],dp[pos^1][2]);
		dp[pos][2]=add(dp[pos^1][1],dp[pos^1][3]);
		dp[pos][3]=dp[pos^1][2];
	}
	printf("%d\n",mul2(dp[pos][3]));
	return 0;
}
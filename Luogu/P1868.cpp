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
	return res;
}

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=1.5e5+5;
const int MAXX=3e6+5;

int n;
int x[MAXN],y[MAXN];
vector<int> V[MAXX];
int dp[MAXX];

int main(void){
	n=read();
	int Max=0;
	for(reg int i=1;i<=n;++i){
		static int x,y;
		x=read(),y=read();
		V[y].push_back(x-1);
		cMax(Max,y);
	}
	int ans=0;
	for(reg int i=1;i<MAXX;++i){
		dp[i]=dp[i-1];
		for(reg int j=0,siz=V[i].size();j<siz;++j)
			cMax(dp[i],dp[V[i][j]]+i-V[i][j]);
		cMax(ans,dp[i]);
	}
	printf("%d\n",ans);
	return 0;
}
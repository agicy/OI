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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1.5e5+5;
const int inf=0x3f3f3f3f;

int n[4];
int c[4][MAXN];
int dp[4][MAXN];
vector<int> bad[3][MAXN];

int main(void){
	for(reg int i=0;i<4;++i)
		n[i]=read();
	for(reg int i=0;i<4;++i)
		for(reg int j=0;j<n[i];++j)
			c[i][j]=read();
	for(reg int i=0;i<3;++i){
		reg int m=read();
		for(reg int j=0;j<m;++j){
			static int x,y;
			x=read()-1,y=read()-1;
			bad[i][y].push_back(x);
		}
	}
	memcpy(dp[0],c[0],sizeof(c[0]));
	for(reg int i=0;i<3;++i){
		multiset<int> S;
		for(reg int j=0;j<n[i];++j)
			S.insert(dp[i][j]);
		for(reg int j=0;j<n[i+1];++j){
			for(int k:bad[i][j])
				S.erase(S.find(dp[i][k]));
			if(S.empty())
				dp[i+1][j]=inf;
			else
				dp[i+1][j]=*S.begin()+c[i+1][j];
			for(int k:bad[i][j])
				S.insert(dp[i][k]);
		}
	}
	reg int ans=inf;
	for(reg int i=0;i<n[3];++i)
		ans=min(ans,dp[3][i]);
	printf("%d\n",ans==inf?-1:ans);
	return 0;
}
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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXM=605+5;
const int MAXLOG2L=64;

int T;
int m;
ll L;
bool a[MAXM];
int tot,bin[MAXLOG2L];
ll dp[MAXLOG2L][2][2][2];

inline int calc(reg bool lim,reg bool las,reg bool cnt){
	reg int Max=lim?(L&1023):1023;
	reg int res=0;
	for(reg int val=0;val<=Max;++val){
		reg bool flag=true;
		for(reg int i=0;i<m;++i){
			reg int res=0;
			if(val+i>=1024)
				res=__builtin_parity(val+i)^cnt^las;
			else
				res=__builtin_parity(val+i)^cnt;
			if(res!=a[i]){
				flag=false;
				break;
			}
		}
		if(flag)
			++res;
	}
	return res;
}

inline ll dfs(reg int dep,reg bool lim,reg bool las,reg bool cnt){
	if(dep==-1)
		return calc(lim,las,cnt);
	if(dp[dep][lim][las][cnt]!=-1)
		return dp[dep][lim][las][cnt];
	reg ll res=0;
	if(dep<=9)
		res=dfs(dep-1,lim,las,cnt);
	else{
		reg int Min=0,Max=lim?bin[dep]:1;
		for(reg int i=Min;i<=Max;++i)
			res+=dfs(dep-1,lim&&i==Max,i&&!las,cnt^i);
	}
	return dp[dep][lim][las][cnt]=res;
}

inline void Init(reg ll x){
	if(!x)
		bin[tot=0]=0;
	else{
		tot=-1;
		while(x){
			bin[++tot]=x&1;
			x>>=1;
		}
	}
	return;
}

int main(void){
	T=read();
	while(T--){
		memset(dp,-1,sizeof(dp));
		m=read(),L=readll();
		for(reg int i=0;i<m;++i)
			a[i]=read();
		Init(L);
		printf("%lld\n",dfs(tot,true,false,false));
	}
	return 0;
}
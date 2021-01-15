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

const int MAXN=1e5+5;
const int MAXS=1e4+5;

int n;
int s[MAXN];
int T[MAXS];
int ord[MAXN];
ll f[MAXN];

inline int X(reg int i){
	return ord[i];
}

inline ll Y(reg int i){
	return f[i-1]+1ll*s[i]*ord[i]*ord[i]-2ll*s[i]*ord[i];
}

inline double slope(reg int i,reg int j){
	return 1.0*(Y(i)-Y(j))/(X(i)-X(j));
}

inline ll calc(reg int i,reg int j){
	return f[j-1]+1ll*s[i]*(ord[i]-ord[j]+1)*(ord[i]-ord[j]+1);
}

vector<int> S[MAXS];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		s[i]=read();
		ord[i]=++T[s[i]];
	}
	for(int i=1;i<=n;++i){
		reg int c=s[i];
		while(S[c].size()>=2&&slope(S[c][S[c].size()-2],i)>=slope(S[c][S[c].size()-2],S[c][S[c].size()-1]))
			S[c].pop_back();
		S[c].push_back(i);
		while(S[c].size()>=2&&calc(i,S[c][S[c].size()-1])<=calc(i,S[c][S[c].size()-2]))
			S[c].pop_back();
		f[i]=calc(i,S[c][S[c].size()-1]);
	}
	printf("%lld\n",f[n]);
	return 0;
}
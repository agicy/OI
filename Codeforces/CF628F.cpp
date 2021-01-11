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

inline int lowbit(reg int x){
	return x&(-x);
}

inline int getCnt(reg int x){
	reg int res=0;
	while(x){
		x^=lowbit(x);
		++res;
	}
	return res;
}

int K,n,b,q;
vector<pair<int,int>/**/> V;

int main(void){
	K=5,n=read(),b=read(),q=read();
	for(reg int i=1;i<=q;++i){
		static int P,Q;
		P=read(),Q=read();
		V.push_back(make_pair(P,Q));
	}
	V.push_back(make_pair(b,n));
	sort(V.begin(),V.end());
	for(reg int i=0,siz=V.size();i<siz-1;++i)
		if(V[i].second>V[i+1].second){
			puts("unfair");
			return 0;
		}
	for(reg int S=0;S<(1<<K);++S){
		reg int sum=0;
		for(reg int i=0;i<=q;++i){
			reg int pos=i?V[i-1].first+1:1;
			reg int cnt=i?V[i].second-V[i-1].second:V[i].second;
			reg int res=0;
			for(reg int j=pos;j<=V[i].first;++j)
				if((S>>(j%K))&1)
					++res;
			sum+=min(cnt,res);
		}
		if(sum<n/K*getCnt(S)){
			puts("unfair");
			return 0;
		}
	}
	puts("fair");
	return 0;
}
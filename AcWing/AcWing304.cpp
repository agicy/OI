#pragma GCC optimize (2)
#pragma GCC optimize (3)
#pragma GCC optimize ("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e6+5;

int n,L,P;
int s[MAXN],Q[MAXN],k[MAXN],pr[MAXN];
double f[MAXN];

inline double pow(reg double x,reg int exp){
	reg double res=1;
	while(exp){
		if(exp&1)
			res=res*x;
		x=x*x;
		exp>>=1;
	}
	return res;
}

inline double Calc(reg int i,reg int j){
	return f[j]+pow(abs(s[i]-s[j]-L),P);
}

inline int bound(reg int x,reg int y){
	reg int l=x,r=n+1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(Calc(mid,x)>=Calc(mid,y))
			r=mid;
		else
			l=mid+1;
	}
	return l;
}

int main(void){
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--){
		cin>>n>>L>>P;
		++L;
		for(reg int i=1;i<=n;++i){
			static string str;
			cin>>str;
			s[i]=s[i-1]+str.length()+1;
		}
		reg int head=1,tail=1;
		Q[head]=0;
		for(reg int i=1;i<=n;++i){
			while(head<tail&&k[head]<=i)
				++head;
			f[i]=Calc(i,Q[head]);
			while(head<tail&&k[tail-1]>=bound(Q[tail],i))
				--tail;
			k[tail]=bound(Q[tail],i),Q[++tail]=i;
		}
		if(f[n]>1e18)
			puts("Too hard to arrange");
		else
			printf("%.0lf\n",f[n]);
		puts("--------------------");
	}
	return 0;
}
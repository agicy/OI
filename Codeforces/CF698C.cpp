#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=20;

int n,k;
int lg[1<<MAXN];
double p[MAXN];
double sum[1<<MAXN],f[1<<MAXN];
double ans[MAXN];

inline int lowbit(reg int x){
	return x&(-x);
}

int main(void){
	scanf("%d%d",&n,&k);
	reg int cnt=0;
	for(reg int i=0;i<n;++i){
		scanf("%lf",&p[i]);
		lg[1<<i]=i;
		if(p[i]) ++cnt;
	}
	if(cnt<=k)
		for(reg int i=0;i<n;++i)
			if(p[i])
				putchar('1'),putchar(i==n-1?'\n':' ');
			else
				putchar('0'),putchar(i==n-1?'\n':' ');
	else{
		f[0]=1;
		for(reg int S=1;S<(1<<n);++S){
			sum[S]=sum[S^lowbit(S)]+p[lg[lowbit(S)]];
			if(__builtin_popcount(S)<=k)
				for(reg int sub=S;sub;sub^=lowbit(sub))
					f[S]+=f[S^lowbit(sub)]*(p[lg[lowbit(sub)]]/(1-sum[S^lowbit(sub)]));
			if(__builtin_popcount(S)==k)
				for(reg int sub=S;sub;sub^=lowbit(sub))
					ans[lg[lowbit(sub)]]+=f[S];
		}
		for(reg int i=0;i<n;++i)
			printf("%.6lf%c",ans[i],i==n-1?'\n':' ');
	}
	return 0;
}
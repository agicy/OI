#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int lowbit(reg int x){
	return x&(-x);
}

inline int lg(reg int x){
	switch(x){
		case 1<<0:return 0;
		case 1<<1:return 1;
		case 1<<2:return 2;
		case 1<<3:return 3;
		case 1<<4:return 4;
		case 1<<5:return 5;
		case 1<<6:return 6;
		case 1<<7:return 7;
		case 1<<8:return 8;
		case 1<<9:return 9;
		case 1<<10:return 10;
		case 1<<11:return 11;
		case 1<<12:return 12;
		case 1<<13:return 13;
	}
	return -1;
}

const int MAXN=13;
const int MAXM=500;

int n,m;
int a[MAXN];
ll f[1<<MAXN][MAXN][MAXM+1];

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=0;i<n;++i)
		scanf("%d",&a[i]);
	reg int Max=max_element(a,a+n)-a;
	for(reg int i=0;i<n;++i){
		reg int tmp=n*(a[Max]-a[i]+(Max<i));
		if(tmp<=m)
			f[1<<i][i][tmp]=1;
	}
	for(reg int S=1;S<((1<<n)-1);++S)
		for(reg int T=S;T;T^=lowbit(T)){
			reg int pos=lg(lowbit(T));
			for(reg int sum=0;sum<=m;++sum)
				if(f[S][pos][sum])
					for(reg int P=(~S)&((1<<n)-1);P;P^=lowbit(P)){
						reg int id=lg(lowbit(P));
						reg int tmp=sum+(n-__builtin_popcount(S))*max(0,(pos<id)+a[pos]-a[id]);
						if(tmp<=m)
							f[S|lowbit(P)][id][tmp]+=f[S][pos][sum];
					}
		}
	reg ll ans=0;
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<=m;++j)
			ans+=f[(1<<n)-1][i][j];
	printf("%lld\n",ans);
	return 0;
}
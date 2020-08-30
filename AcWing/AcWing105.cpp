#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=2e5+5;
const int MAXM=2e5+5;

int n,m,T;
ll a[MAXN],b[MAXM];

inline ll Solve(ll a[],int n){
	static ll s[MAXM];
	for(int i=1;i<=n;++i){
		a[i]-=T/n;
		s[i]=s[i-1]+a[i];
	}
	sort(s+1,s+n+1);
	int mid=(n+1)>>1;
	ll sum=0;
	for(int i=1;i<=n;++i)
		sum+=abs(s[mid]-s[i]);
	return sum;
}

int main(void){
	scanf("%d%d%d",&n,&m,&T);
	for(int i=1;i<=T;++i){
		static int x,y;
		scanf("%d%d",&x,&y);
		++a[x],++b[y];
	}
	if(T%n==0&&T%m==0)
		printf("both %lld\n",Solve(a,n)+Solve(b,m));
	else if(T%n==0)
		printf("row %lld\n",Solve(a,n));
	else if(T%m==0)
		printf("column %lld\n",Solve(b,m));
	else
		puts("impossible");
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int myrand(reg int l,reg int r){
	return rand()%(r-l+1)+l;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXQ=1e5+5;

int n,m,q;
int k;
char s0[MAXM];
char s[MAXM];
int t[MAXN];
int fa[MAXN];
int u[MAXQ],v[MAXQ];

int main(void){
	srand(time(0));

	n=myrand(1,1e5),q=myrand(1,1e5);
	k=myrand(1,20);
	reg int tmpS=myrand(0,(1<<k)-1);
	for(reg int i=0;i<k;++i)
		s0[i]=((tmpS>>i)&1)+'0';
	reg int pod=myrand(k,1e5)/k;
	//fprintf(stderr,"k=%d pod=%d\n",k,pod);
	m=pod*k;
	for(reg int i=1;i<=m;++i)
		s[i]=s0[(i-1)%k];
	for(reg int i=1;i<=n;++i)
		t[i]=myrand(0,1);
	for(reg int i=2;i<=n;++i)
		fa[i]=i-1;
	for(reg int i=1;i<=q;++i)
		u[i]=myrand(1,n),v[i]=myrand(1,n);
	
	printf("%d %d %d\n",n,m,q);
	printf("%s\n",s+1);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",t[i],i==n?'\n':' ');
	for(reg int i=2;i<=n;++i)
		printf("%d %d\n",fa[i],i);
	for(reg int i=1;i<=q;++i)
		printf("%d %d\n",u[i],v[i]);
	return 0;
}
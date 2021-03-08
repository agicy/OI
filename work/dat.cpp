#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int myrand(reg int l,reg int r){
	return rand()%(r-l+1)+l;
}

const int MAXN=5e4+5;
const int MAXQ=5e4+5;

int n,q;
int a[MAXN],b[MAXN];
int tmpa[MAXN],tmpb[MAXN];
int opt[MAXQ],x[MAXQ],y[MAXQ];

int main(void){
	srand(time(0));
	n=myrand(1,100),q=myrand(1,100);
	for(reg int i=1;i<=n;++i)
		tmpa[i]=a[i]=myrand(1,1e5);
	for(reg int i=1;i<=n;++i)
		tmpb[i]=b[i]=myrand(1,1e5);
	for(reg int i=1;i<=q;++i){
		opt[i]=myrand(0,1),x[i]=myrand(1,n);
		if(opt[i]==0){
			y[i]=myrand(tmpa[x[i]],1e5);
			tmpa[x[i]]=y[i];
		}
		else{
			y[i]=myrand(tmpb[x[i]],1e5);
			tmpb[x[i]]=y[i];
		}
	}
	printf("%d %d\n",n,q);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",a[i],i==n?'\n':' ');
	for(reg int i=1;i<=n;++i)
		printf("%d%c",b[i],i==n?'\n':' ');
	for(reg int i=1;i<=q;++i)
		printf("%d %d %d\n",opt[i],x[i],y[i]);
	return 0;
}
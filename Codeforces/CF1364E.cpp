#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int kN=3e3 + 5;

int n,p[kN];

inline int query(reg int x,reg int y){
	printf("? %d %d\n",x,y);
	fflush(stdout);
	int res;
	scanf("%d",&res);
	return res;
}

inline int RandDiff(reg int x){
	reg int res;
	do
		res=rand()%n+1;
	while(res==x);
	return res;
}

inline int getVal(reg int x){
	reg int res=query(x,RandDiff(x));
	const int T=15;
	for(reg int i=1;i<=T;++i)
		res&=query(x,RandDiff(x));
	return res;
}

int main(void){
	srand(time(0));
	scanf("%d",&n);
	reg int x=rand()%n+1,val=getVal(x);
	for(reg int i=1;i<=n;++i)
		if(x!=i&&query(x,i)==val){
			val=getVal(i);
			x=i;
		}
	p[x]=val;
	for(reg int i=1;i<=n;++i)
		if(i!=x)
			p[i]=query(x,i);
	printf("! ");
	for(reg int i=1;i<=n;++i)
		printf("%d%c",p[i],i==n?'\n':' ');
	return 0;
}
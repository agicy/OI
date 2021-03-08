#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int n,m;

inline bool query(reg bool flag,reg int len,reg int a,reg int b){
	if(!flag)
		printf("? %d %d %d %d %d %d\n",len,m,a,1,b,1);
	else
		printf("? %d %d %d %d %d %d\n",n,len,1,a,1,b);
	fflush(stdout);
	int res;
	scanf("%d",&res);
	return res;
}

inline bool check(reg bool flag,reg int len,reg int c){
	if(c==2)
		return query(flag,len>>1,1,(len>>1)+1);
	reg int nl=len/c*(c/2);
	return query(flag,nl,1,nl+1)&&query(flag,nl,1,nl+len/c+1);
}

const int MAXS=10+5;

int a[MAXS],b[MAXS];

inline int solve(reg bool flag,reg int x){
	reg int tot=0;
	reg int tmp=x;
	for(reg int i=2;i<=tmp;++i)
		if(!(tmp%i)){
			a[++tot]=i;
			b[tot]=0;
			while(!(tmp%i))
				++b[tot],tmp/=i;
		}
	reg int res=1;
	for(reg int i=1;i<=tot;++i)
		for(reg int j=1;j<=b[i];++j)
			if(check(flag,x/res,a[i]))
				res*=a[i];
			else
				break;
	return res;
}

inline int sigma(reg int x){
	reg int res=0;
	for(reg int i=1;1ll*i*i<=x;++i)
		if(!(x%i)){
			++res;
			if(i*i!=x)
				++res;
		}
	return res;
}

int main(void){
	scanf("%d%d",&n,&m);
	printf("! %d\n",sigma(solve(0,n))*sigma(solve(1,m)));
	return 0;
}
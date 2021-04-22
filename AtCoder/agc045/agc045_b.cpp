#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F

const int MAXS=1000000+5;

int n;
char str[MAXS];
int a[MAXS],sum[MAXS];
int sMin[MAXS];

inline int Solve(reg int Min){
	reg int base=0;
	static int tmp[MAXS];
	for(reg int i=1;i<=n;++i)
		if(str[i]=='?')
			if(sMin[i]-base-2>=Min){
				base+=2;
				tmp[i]=-1;
			}
			else
				tmp[i]=1;
		else
			tmp[i]=(str[i]=='0')?(-1):(1);
	int Max=0,sum=0;
	for(reg int i=1;i<=n;++i){
		sum+=tmp[i];
		Max=max(Max,sum);
	}
	return Max-Min;
}

int main(void){
	scanf("%s",str+1);
	n=strlen(str+1);
	for(reg int i=1;i<=n;++i)
		a[i]=(str[i]=='0')?(-1):(1);
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i];
	sMin[n]=sum[n];
	for(reg int i=n-1;i>=0;--i)
		sMin[i]=min(sMin[i+1],sum[i]);
	printf("%d\n",min(Solve(sMin[0]),Solve(sMin[0]-1)));
	return 0;
}
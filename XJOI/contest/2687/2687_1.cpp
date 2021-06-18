#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

bool st;

const int MAXN=5e5+5;

int n,L,R,s;
char col[MAXN],val[MAXN];
int sum[MAXN];

inline int solve(reg int x){
	static int pos[128],f[MAXN];
	for(reg int i=0;i<x;++i){
		for(reg int j=i;j<n;j+=x)
			pos[int(col[j])]=-1;
		for(reg int j=i;j<n;j+=x)
			f[j]=pos[int(col[j])],pos[int(col[j])]=j;
	}
	reg int res=0;
	for(reg int i=0,las=-1;i<n;++i){
		las=max(las,f[i]+1);
		reg int len=i-las+1;
		if(len/x<s)
			continue;
		len/=x;
		res=max(res,sum[i+1]-sum[i-len*x+1]);
	}
	return res;
}

bool ed;

int main(void){
	scanf("%d%d%d%d%s%s",&n,&L,&R,&s,col,val);
	for(reg int i=0;i<n;++i)
		val[i]^='0';
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+val[i-1];
	reg int ans=0;
	for(reg int i=L;i<=R;++i)
		ans=max(ans,solve(i));
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}
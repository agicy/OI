#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e6+5;

int n;
char s[MAXN];
int a[MAXN],sum[MAXN];
int head[MAXN],to[MAXN],Next[MAXN];

int main(void){
	scanf("%d%s",&n,s+1);
	memset(head,-1,sizeof(head));
	for(reg int i=1;i<=n;++i)
		a[i]=(s[i]=='p')?(1):(-1);
	int Min=0;
	for(reg int i=1;i<=n;++i){
		sum[i]=sum[i-1]+a[i];
		Min=min(Min,sum[i]);
	}
	for(reg int i=n;i>=0;--i){
		Next[i]=head[sum[i]-Min];
		head[sum[i]-Min]=i;
		to[i]=i;
	}
	int ans=0;
	for(reg int i=n,last=n;i>=1;--i)
		if(a[i]==-1)
			last=i-1;
		else{
			if(Next[i-1]>=0&&sum[to[Next[i-1]]]>=sum[last])
				last=to[Next[i-1]];
			to[i-1]=last;
			ans=max(ans,last-i+1);
		}
	printf("%d\n",ans);
	return 0;
}

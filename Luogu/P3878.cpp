#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=30+5;

int n;
int v[MAXN];
ll sum[MAXN];

inline ll DFS(reg int dep,int cnt1,ll sum1,int cnt2,ll sum2){
	if(cnt1>n/2||cnt2>n/2)
		return sum[n];
	reg int len=n/2-cnt1;
	reg ll Maxsum=sum1+sum[dep+len-1]-sum[dep-1];
	if(Maxsum*2<=sum[n])
		return sum[n]-Maxsum*2;
	reg ll Minsum=sum1+sum[n]-sum[n-len];
	if(Minsum*2>=sum[n])
		return Minsum*2-sum[n];
	return min(
		DFS(dep+1,cnt1+1,sum1+v[dep],cnt2,sum2),
		DFS(dep+1,cnt1,sum1,cnt2+1,sum2+v[dep])
	);
}

inline bool cmp(reg int a,reg int b){
	return a>b;
}

int main(void){
	reg int T=read();
	while(T--){
		n=read();
		for(reg int i=1;i<=n;++i)
			v[i]=read();
		if(n&1)
			v[++n]=0;
		sort(v+1,v+n+1,cmp);
		for(reg int i=1;i<=n;++i)
			sum[i]=sum[i-1]+v[i];
		printf("%lld\n",DFS(1,0,0,0,0));
	}
	return 0;
}
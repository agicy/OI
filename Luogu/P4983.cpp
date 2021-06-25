#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,m;
int sum[MAXN];
int cnt[MAXN];
ll f[MAXN];

inline ll x(reg int i){
	return sum[i];
}

inline ll y(reg int i){
	return f[i]+1ll*sum[i]*(sum[i]-2);
}

inline double k(reg int a,int b){
	return 1.0*(y(b)-y(a))/(x(b)-x(a));
}

inline void calc(reg ll mid){
	fill(f+1,f+n+1,inf);
	f[0]=0,cnt[0]=0;
	reg int _head=0,_tail=0;
	static int Q[MAXN];
	Q[_tail++]=0;
	for(reg int i=1;i<=n;++i){
		while(_tail-_head>1&&k(Q[_head],Q[_head+1])<2ll*sum[i])
			++_head;
		reg int j=Q[_head];
		f[i]=f[j]+1ll*(sum[i]-sum[j]+1)*(sum[i]-sum[j]+1)+mid;
		cnt[i]=cnt[j]+1;
		while(_tail-_head>1&&k(Q[_tail-2],Q[_tail-1])>k(Q[_tail-2],i))
			--_tail;
		Q[_tail++]=i;
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+read();
	reg ll l=0,r=1e18,mid;
	while(l<r){
		mid=(l+r)>>1;
		calc(mid);
		if(cnt[n]<=m)
			r=mid;
		else
			l=mid+1;
	}
	calc(l);
	printf("%lld\n",f[n]-l*m);
	return 0;
}
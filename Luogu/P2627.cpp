#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=1e5+5;

int n,k;
ll sum[MAXN];
ll f[MAXN];

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+read();
	reg int _head=0,_tail=0;
	static int Q[MAXN];
	Q[_tail++]=0,Q[_tail++]=1;
	for(reg int i=1;i<=n;++i){
		while(_head<_tail&&Q[_head]<i-k)
			++_head;
		reg int j=Q[_head];
		if(!j)
			f[i]=sum[i];
		else
			f[i]=f[j-1]+sum[i]-sum[j];
		while(_head<_tail&&f[Q[_tail-1]-1]-sum[Q[_tail-1]]<f[i]-sum[i+1])
			--_tail;
		Q[_tail++]=i+1;
	}
	printf("%lld\n",f[n]);
	return 0;
}
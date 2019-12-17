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

const int MAXN=300000+5;

int n,m;
int a[MAXN];
ll sum[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i];
	ll ans=a[1];
	deque<int> Q;
	Q.push_front(0);
	for(reg int i=1;i<=n;++i){
		while(!Q.empty()&&Q.front()+m<i)
			Q.pop_front();
		ans=max(ans,sum[i]-sum[Q.front()]);
		while(!Q.empty()&&sum[Q.back()]>=sum[i])
			Q.pop_back();
		Q.push_back((int)i);
	}
	printf("%lld\n",ans);
	return;
}

#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
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

const int MAXN=200000+5;

int n,q;
int a[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

inline void Work(void){
	reg ll ans=0;
	for(reg int i=1;i<n;++i)
		ans+=max(max(a[i],a[i+1]),0);
	while(q--){
		static int p,x;
		p=read(),x=read();
		if(p>1){
			ans-=max(max(a[p-1],a[p]),0);
			ans+=max(max(a[p-1],x),0);
		}
		if(p<n){
			ans-=max(max(a[p+1],a[p]),0);
			ans+=max(max(a[p+1],x),0);
		}
		a[p]=x;
		printf("%lld\n",ans);
	}
	return;
}

#include<cstdio>
#include<cmath>
#include<algorithm>
using std::max;
using std::sort;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=200000+5;

int n;
ll k;
ll tmp[MAXN];
ll a[MAXN],f[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	reg int i;
	n=read(),k=read();
	for(i=1;i<=n;++i)
		a[i]=read();
	for(i=1;i<=n;++i)
		f[i]=read();
	return;
}

inline bool check(reg ll mid){
	reg ll i;
	for(i=1;i<=n;++i)
		tmp[i]=mid/f[i];
	sort(tmp+1,tmp+n+1);
	ll ans=0;
	for(i=n;i>=1;--i)
		ans+=max(0ll,a[i]-tmp[i]);
	return ans<=k;
}

inline void Work(void){
	sort(a+1,a+n+1);
	sort(f+1,f+n+1);
	reg ll l=0,r=1e13,mid,ans=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}
		else
			l=mid+1;
	}
	printf("%lld\n",ans);
	return;
}
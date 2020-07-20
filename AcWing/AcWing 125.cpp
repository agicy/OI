#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=50000+5;

struct Node{
	int w,s;
	inline void Read(void){
		w=read(),s=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return w+s<a.w+a.s;
	}
};

int n;
Node a[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	return;
}

inline void Work(void){
	sort(a+1,a+n+1);
	reg ll sum=0,ans=-INF;
	for(reg int i=1;i<=n;++i){
		ans=max((ll)ans,sum-a[i].s);
		sum+=a[i].w;
	}
	printf("%lld\n",ans);
	return;
}

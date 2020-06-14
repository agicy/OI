#include<bits/stdc++.h>
using namespace std;
#define reg register
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
	int w,x,d;
	inline void Read(void){
		w=read(),x=read(),d=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return x<a.x;
	}
};

int n,L;
int W;
Node a[MAXN];

inline bool check(reg int mid){
	reg int l=1,r=n,sum=0;
	for(reg int i=1;i<=n;++i)
		if(a[i].x+a[i].d*mid<=0)
			sum+=a[l++].w;
		else if(a[i].x+a[i].d*mid>=L)
			sum+=a[r--].w;
	return (sum<<1)>=W;
}

int f[MAXN];

int main(void){
	n=read(),L=read();
	for(reg int i=1;i<=n;++i){
		a[i].Read();
		W+=a[i].w;
	}
	sort(a+1,a+n+1);
	reg int l=0,r=INF,mid,T=0;
	while(l<r-1){
		mid=(l+r)>>1;
		if(check(mid))
			r=T=mid;
		else
			l=mid;
	}
	reg int cnt=0,ans=0;
	for(reg int i=1;i<=n;++i){
		if(a[i].d==-1){
			reg int X=a[i].x-(T<<1);
			reg int l=0,r=cnt+1,mid;
			while(l<r-1){
				mid=(l+r)>>1;
				if(f[mid]>=X)
					r=mid;
				else
					l=mid;
			}
			ans+=cnt-r+1;
		}
		else
			f[++cnt]=a[i].x;
	}
	printf("%d\n",ans);
	return 0;
}
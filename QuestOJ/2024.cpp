#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define eps 1e-7
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

int n;
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
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

inline double Calc(reg int pos,reg int len){
	return (double)(sum[n]-sum[n-len]+sum[pos]-sum[pos-len-1])/(len<<1|1);
}

inline void Work(void){
	sort(a+1,a+n+1);
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i];
	reg double ans=0;
	for(reg int i=2;i<=n-1;++i){
		reg int l=1,r=min(n-i,i-1),mid;
		reg double bar=a[i];
		while(l<=r){
			mid=(l+r)>>1;
			reg double temp1=Calc(i,mid),temp2=Calc(i,mid-1);
			if(temp1-temp2>-eps){
				bar=temp1;
				l=mid+1;
			}
			else
				r=mid-1;
		}
		ans=max((double)ans,bar-a[i]);
	}
	printf("%.5lf\n",ans);
	return;
}

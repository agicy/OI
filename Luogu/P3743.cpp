#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define eps 1e-6
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

const int MAXN=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,p;
int a[MAXN],b[MAXN];

inline void Read(void){
	n=read(),p=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),b[i]=read();
	return;
}

inline bool check(reg double mid){
	reg double Max=p*mid;
	reg double sum=0;
	for(reg int i=1;i<=n;++i)
		if(a[i]*mid>b[i])
			sum+=(a[i]*mid-b[i]);
	return sum<=Max;
}

inline void Work(void){
	reg ll sum=0;
	for(reg int i=1;i<=n;++i)
		sum+=a[i];
	if(sum<=p){
		puts("-1");
		return;
	}
	reg double l=0,r=1e10,mid;
	while(fabs(r-l)>eps){
		mid=(l+r)/2.0;
		if(check(mid))
			l=mid;
		else
			r=mid;
	}
	printf("%.6lf\n",l);
	return;
}

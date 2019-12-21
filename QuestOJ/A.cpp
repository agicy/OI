#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

inline void Work(void){
	sort(a+1,a+n+1);
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i];
	double last,temp,ans=0;
	//odd
	for(reg int i=1;i<=n;++i){
		last=-1;
		for(reg int j=1;j<=n&&i+j<=n&&1<=i-j;++j){
			reg ll S=a[i]+sum[i-1]-sum[i-j-1]+sum[n]-sum[n-j];
			temp=(double)S/(j*2+1)-a[i];
			if(temp<last||temp<ans)
				break;
			else{
				//printf("i=%d j=%d temp=%.5lf\n",i,j,temp);
				last=temp;
				ans=max(ans,temp);
			}
		}
	}
	//even_before
	for(reg int i=1;i<=n;++i){
		last=-1;
		for(reg int j=1;j<=n&&i+j<=n&&1<=i-j-1;++j){
			reg ll S=a[i]+sum[i-1]-sum[i-j-2]+sum[n]-sum[n-j];
			temp=(double)S/(j*2+2)-(double)(a[i]+a[i-1])/2;
			if(temp<last||temp<ans)
				break;
			else{
				//printf("i=%d j=%d temp=%.5lf\n",i,j,temp);
				last=temp;
				ans=max(ans,temp);
			}
		}
	}
	//even_after
	for(reg int i=1;i<=n;++i){
		last=-1;
		for(reg int j=1;j<=n&&i+j+1<=n&&1<=i-j;++j){
			reg ll S=a[i]+sum[i-1]-sum[i-j-1]+sum[n]-sum[n-j-1];
			temp=(double)S/(j*2+2)-(double)(a[i]+a[n-j])/2;
			if(temp<last||temp<ans)
				break;
			else{
				//printf("i=%d j=%d temp=%.5lf\n",i,j,temp);
				last=temp;
				ans=max(ans,temp);
			}
		}
	}
	printf("%.5lf\n",ans);
	return;
}

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

const int MAXN=300000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int a[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

inline bool check(reg int mid){
	static int temp[MAXN];
	for(reg int i=1;i<=n;++i)
		temp[i]=a[i];
	for(reg int i=1;i<=n;++i)
		if(temp[i]<temp[i-1])
			if(temp[i-1]-temp[i]>mid)
				return false;
			else
				temp[i]=temp[i-1];
		else if(temp[i-1]+m-temp[i]<=mid)
			temp[i]=temp[i-1];
	return true;
}

inline void Work(void){
	reg int l=0,r=m,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%d\n",l);
	return;
}

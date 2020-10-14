#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

int n,m,w;
int a[MAXN];
int d[MAXN];

inline bool check(reg int mid){
	reg int sum=0,cnt=m;
	for(reg int i=1;i<=n;++i){
		if(i>=w)
			sum-=d[i-w];
		d[i]=max(0,mid-sum-a[i]);
		sum+=d[i];
		cnt-=d[i];
		if(cnt<0)
			return false;
	}
	return true;
}

int main(void){
	n=read(),m=read(),w=read();
	int Min=inf;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		cMin(Min,a[i]);
	}
	reg int l=Min,r=Min+m,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid+1))
			l=mid+1;
		else
			r=mid;
	}
	printf("%d\n",r);
	return 0;
}
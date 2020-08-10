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

const int MAXN=250+5;
const int MAXW=1e3+5;
const ll inf=0x3f3f3f3f3f3f3f3fll;

int n,W;
int w[MAXN],t[MAXN];
ll val[MAXN];
ll f[MAXW];

inline bool check(reg int x){
	for(reg int i=1;i<=n;++i)
		val[i]=t[i]-1ll*x*w[i];
	f[0]=0;
	for(reg int i=1;i<=W;++i)
		f[i]=-inf;
	for(reg int i=1;i<=n;++i)
		for(reg int j=W;j>=0;--j)
			if(f[j]!=-inf){
				reg int p=min(j+w[i],W);
				f[p]=max(f[p],f[j]+val[i]);
			}
	return f[W]>0;
}

int main(void){
	n=read(),W=read();
	for(reg int i=1;i<=n;++i)
		w[i]=read(),t[i]=read()*1000;
	reg int l=0,r=1e7,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))
			l=mid+1;
		else
			r=mid-1;
	}
	printf("%d\n",l-1);
	return 0;
}
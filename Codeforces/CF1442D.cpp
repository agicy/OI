#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=3e3+5;
const int MAXK=3e3+5;

int n,k;
vector<int> a[MAXN];
int v[MAXN];
ll w[MAXN];
ll f[MAXK];
ll ans;

inline void solve(reg int l,reg int r){
	if(l==r){
		reg ll sum=0;
		for(reg int i=0;i<v[l]&&i+1<=k;++i){
			sum+=a[l][i];
			ans=max(ans,f[k-(i+1)]+sum);
		}
		return;
	}
	ll tmp[MAXK];
	for(reg int i=0;i<=k;++i)
		tmp[i]=f[i];
	reg int mid=(l+r)>>1;
	for(reg int i=l;i<=mid;++i)
		for(reg int j=k;j>=v[i];--j)
			f[j]=max(f[j],f[j-v[i]]+w[i]);
	solve(mid+1,r);
	for(reg int i=0;i<=k;++i)
		f[i]=tmp[i];
	for(reg int i=mid+1;i<=r;++i)
		for(reg int j=k;j>=v[i];--j)
			f[j]=max(f[j],f[j-v[i]]+w[i]);
	solve(l,mid);
	return;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i){
		v[i]=read();
		a[i].resize(v[i]);
		for(reg int j=0;j<v[i];++j)
			a[i][j]=read(),w[i]+=a[i][j];
	}
	solve(1,n);
	printf("%lld\n",ans);
	return 0;
}
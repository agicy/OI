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

const int MAXN=1e5+5;

int n;
int a[MAXN];

int c[MAXN];
int T[MAXN];
ll sum,tot;

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN*2];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
}

int p[MAXN];

const int Delta=MAXN;

inline ll check(reg int mid){
	for(reg int i=1;i<=n;++i)
		p[i]=p[i-1]+(a[i]>mid)*2;
	reg ll res=0;
	for(reg int i=1;i<=n;++i){
		BIT::update(Delta+i-p[i],1);
		res+=BIT::query(Delta+i-p[i]-1);
	}
	for(reg int i=1;i<=n;++i)
		BIT::update(Delta+i-p[i],-1);
	return res;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg int l=1,r=1e9,mid,ans;
	BIT::Init(Delta+n);
	BIT::update(Delta,1);
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)<(1ll*n*(n+1ll)/4ll+1ll))
			l=mid+1;
		else{
			ans=mid;
			r=mid-1;
		}
	}
	printf("%d\n",ans);
	return 0;
}
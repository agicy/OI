#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1<<20;

ll B;

struct querys{
	int id,l,r;
	inline bool operator<(const querys& a)const{
		return (l/B==a.l/B)?r<a.r:l<a.l;
	}
};

ll n,m;
ll k;
ll a[MAXN];
ll T[MAXN];
ll ans[MAXN],sum;
querys q[MAXN];

inline void add(reg int w){
	sum+=T[a[w]^k];
	++T[a[w]];
	return;
}

inline void del(reg int w){
	--T[a[w]];
	sum-=T[a[w]^k];
	return;
}

int main(void){
	n=read(),m=read(),k=read();
	B=sqrt(n);
	for(reg int i=1;i<=n;++i)
		a[i]=read()^a[i-1];
	for(reg int i=1;i<=m;++i){
		q[i].id=i;
		q[i].l=read(),q[i].r=read();
	}
	sort(q+1,q+1+m);
	reg int l=1,r=0;
	T[0]=1;
	for(reg int i=1;i<=m;++i){
		while(l<q[i].l){
			del(l-1);
			l++;
		}
		while(l>q[i].l){
			l--;
			add(l-1);
		}
		while(r<q[i].r){
			r++;
			add(r);
		}
		while(r>q[i].r){
			del(r);
			r--;
		}
		ans[q[i].id]=sum;
	}
	for(reg int i=1;i<=m;++i)
		printf("%lld\n",ans[i]);
	return 0;
}
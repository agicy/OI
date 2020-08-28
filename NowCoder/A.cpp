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
const int MAXQ=1e5+5;

struct querys{
	int l,r,id,bl;
	inline querys(reg int l=0,reg int r=0,reg int id=0,reg int bl=0):l(l),r(r),id(id),bl(bl){
		return;
	}
	inline bool operator<(const querys& a)const{
		return bl==a.bl?r<a.r:bl<a.bl;
	}
};

int n,q;
int a[MAXN];
int B;
int Ans;
int cnt[MAXN];
int ans[MAXQ];
querys Q[MAXQ];

inline void del(reg int x){
	--cnt[a[x]];
	if(!cnt[a[x]])
		Ans=min(Ans,a[x]);
	return;
}

inline void add(reg int x){
	++cnt[a[x]];
	while(cnt[Ans])
		++Ans;
	return;
}

int main(void){
	n=read(),q=read();
	reg int B=sqrt(n);
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=q;++i){
		static int l,r;
		l=read(),r=read();
		Q[i]=querys(l,r,i,(l-1)/B+1);
	}
	reg int l=1,r=0;
	sort(Q+1,Q+q+1);
	for(reg int i=1;i<=q;++i){
		while(r<Q[i].r)
			add(++r);
		while(r>Q[i].r)
			del(r--);
		while(l<Q[i].l)
			del(l++);
		while(l>Q[i].l)
			add(--l);
		ans[Q[i].id]=Ans;
	}
	for(reg int i=1;i<=q;++i)
		printf("%d\n",ans[i]);
	return 0;
}
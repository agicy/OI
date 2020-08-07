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

const int MAXN=5e4+5;
const int MAXM=5e4+5;
const int MAXK=5e4+5;

int B;

struct querys{
	int id,l,r;
	inline void Read(reg int i){
		id=i;
		l=read(),r=read();
		return;
	}
	inline bool operator<(const querys& a)const{
		return l/B==a.l/B?r<a.r:l<a.l;
	}
};

int n,m,k;
int a[MAXN];
querys q[MAXM];
int c[MAXK];
int ans[MAXM];
int sum;

inline int calc(reg int x){
	return (x<<1|1);
}

inline void add(reg int a){
	sum+=calc(c[a]++);
	return;
}

inline void del(reg int a){
	sum-=calc(--c[a]);
	return;
}

int main(void){
	n=read(),m=read(),k=read();
	B=n/sqrt(m);
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=m;++i)
		q[i].Read(i);
	sort(q+1,q+m+1);
	reg int l=1,r=0;
	for(reg int i=1;i<=m;++i){
		while(q[i].l<l)
			add(a[--l]);
		while(l<q[i].l)
			del(a[l++]);
		while(r<q[i].r)
			add(a[++r]);
		while(q[i].r<r)
			del(a[r--]);
		ans[q[i].id]=sum;
	}
	for(reg int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}
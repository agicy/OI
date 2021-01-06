#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline int max(reg int a,reg int b){
	return a<b?b:a;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXA=1e5+5;
const int inf=0x3f3f3f3f;

int n,m;
int B,pos[MAXN];
int a[MAXN];

struct querys{
	int id,l,r;
	int a,b;
	inline querys(reg int id=0,reg int l=0,reg int r=0,reg int a=0,reg int b=0):id(id),l(l),r(r),a(a),b(b){
		return;
	}
	inline bool operator<(const querys& a)const{
		if(pos[l]!=pos[a.l])
			return pos[l]<pos[a.l];
		else
			return (pos[l]&1)?r<a.r:r>a.r;
	}
};

namespace BIT1{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXA];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		if(id>n)id=n;
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline int query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
}

namespace BIT2{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXA];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		if(id>n)id=n;
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline int query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
}

querys q[MAXM];
pair<int,int> ans[MAXM];
int T[MAXA];

inline void add(reg int val){
	BIT1::update(val,1);
	++T[val];
	if(T[val]==1)
		BIT2::update(val,1);
	return;
}

inline void del(reg int val){
	BIT1::update(val,-1);
	--T[val];
	if(T[val]==0)
		BIT2::update(val,-1);
	return;
}

int main(void){
	n=read(),m=read();
	B=sqrt(n);
	reg int Max=-inf;
	for(reg int i=1;i<=n;++i){
		pos[i]=(i-1)/B+1;
		Max=max(Max,a[i]=read());
	}
	for(reg int i=1;i<=m;++i)
		q[i].id=i,q[i].l=read(),q[i].r=read(),q[i].a=read(),q[i].b=read();
	sort(q+1,q+m+1);
	BIT1::Init(Max),BIT2::Init(Max);
	for(reg int i=1,l=1,r=0;i<=m;++i){
		while(l<q[i].l) del(a[l++]);
		while(r>q[i].r) del(a[r--]);
		while(l>q[i].l) add(a[--l]);
		while(r<q[i].r) add(a[++r]);
		ans[q[i].id].first=BIT1::query(q[i].a,q[i].b);
		ans[q[i].id].second=BIT2::query(q[i].a,q[i].b);
	}
	for(reg int i=1;i<=m;++i)
		write(ans[i].first),putchar(' '),write(ans[i].second),putchar('\n');
	flush();
	return 0;
}
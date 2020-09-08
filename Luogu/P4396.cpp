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
const int MAXM=1e5+5;
const int MAXA=1e5+5;
const int inf=0x3f3f3f3f;

int n,m;
int B,pos[MAXN];
int a[MAXN];

struct querys{
	int id;
	int l,r;
	int a,b;
	inline querys(reg int id=0,reg int l=0,reg int r=0,reg int a=0,reg int b=0):id(id),l(l),r(r),a(a),b(b){
		return;
	}
	inline bool operator<(const querys& a)const{
		if(pos[l]!=pos[a.l])
			return pos[l]<pos[a.l];
		else
			return r<a.r;
	}
};

struct BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXA];
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
};

querys q[MAXM];
BIT T1,T2;
pair<int,int> ans[MAXM];
int T[MAXA];

inline void add(reg int val){
	T1.update(val,1);
	++T[val];
	if(T[val]==1)
		T2.update(val,1);
	return;
}

inline void del(reg int val){
	T1.update(val,-1);
	--T[val];
	if(T[val]==0)
		T2.update(val,-1);
	return;
}

int main(void){
	n=read(),m=read();
	B=sqrt(n);
	int Max=-inf;
	for(reg int i=1;i<=n;++i){
		pos[i]=(i-1)/B+1;
		a[i]=read();
		Max=max(Max,a[i]);
	}
	for(reg int i=1;i<=m;++i){
		static int l,r,a,b;
		l=read(),r=read(),a=read(),b=read();
		q[i]=querys(i,l,r,a,b);
	}
	sort(q+1,q+m+1);
	reg int l=1,r=0;
	T1.Init(Max),T2.Init(Max);
	for(reg int i=1;i<=m;++i){
		while(l<q[i].l)
			del(a[l++]);
		while(r>q[i].r)
			del(a[r--]);
		while(l>q[i].l)
			add(a[--l]);
		while(r<q[i].r)
			add(a[++r]);
		int tmp1=T1.query(q[i].b)-T1.query(q[i].a-1);
		int tmp2=T2.query(q[i].b)-T2.query(q[i].a-1);
		ans[q[i].id]=make_pair(tmp1,tmp2);
	}
	for(reg int i=1;i<=m;++i)
		printf("%d %d\n",ans[i].first,ans[i].second);
	return 0;
}
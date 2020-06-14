#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=200000+5;
#define delta 10

struct Node{
	int val,id;
	inline void Read(reg int i){
		id=i;
		val=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return val==a.val?id<a.id:val<a.val;
	}
};

struct Querys{
	int l,r,id;
	inline void Read(reg int i){
		id=i;
		l=read(),r=read();
		return;
	}
};

int n,m;
int rnk[MAXN<<1];
int tot[MAXN<<1],cnt[MAXN<<1];
int BLOCK;

inline bool cmp(const Querys& a,const Querys& b){
	if(a.l/BLOCK!=b.l/BLOCK)
		return a.l/BLOCK<b.l/BLOCK;
	if(a.r/BLOCK!=b.r/BLOCK)
		return a.r/BLOCK<b.r/BLOCK;
	return a.id<b.id;
}

Node a[MAXN<<1];
Querys Q[MAXN<<1];
int Ans;

inline void Add(reg int x,reg int flag){
	reg int d=cnt[x];
	if(flag==1){
		if(Ans==d)
			++Ans;
		--tot[d+delta];
		++tot[d+delta+1];
		++cnt[x];
	}
	else{
		if(Ans==d&&tot[d+delta]==1)
			--Ans;
		--tot[d+delta];
		++tot[d+delta-1];
		--cnt[x];
	}
	return;
}

int ans[MAXN<<1];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read(i);
	sort(a+1,a+n+1);
	reg int cnt=0;
	for(reg int i=1;i<=n;++i){
		if(i==1||a[i].val!=a[i-1].val)
			++cnt;
		rnk[a[i].id]=cnt;
	}
	BLOCK=ceil(sqrt(n));
	for(reg int i=1;i<=m;++i)
		Q[i].Read(i);
	sort(Q+1,Q+m+1,cmp);
	reg int l=1,r=0;
	tot[0]=cnt;
	for(reg int i=1;i<=m;++i){
		while(r<Q[i].r)
			Add(rnk[++r],1);
		while(r>Q[i].r)
			Add(rnk[r--],-1);
		while(l<Q[i].l)
			Add(rnk[l++],-1);
		while(l>Q[i].l)
			Add(rnk[--l],1);
		ans[Q[i].id]=-Ans;
	}
	for(reg int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}
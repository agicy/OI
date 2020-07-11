#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;
const int MAXM=100000+5;
const int MAXA=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Node{
	int ID;
	int l,r;
	inline void Read(reg int i){
		ID=i;
		l=read()-1,r=read();
		return;
	}
};

int n,m,K;
int Block;
int a[MAXN],ID[MAXN];
Node Q[MAXM];

inline void Read(void){
	n=read(),m=read(),K=read();
	Block=sqrt(n);
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		ID[i]=(i-1)/Block+1;
		a[i]=a[i-1]^a[i];
	}
	for(reg int i=1;i<=m;++i)
		Q[i].Read(i);
	return;
}

int T[MAXA];
int ans[MAXM];

inline bool cmp(const Node& a,const Node& b){
	if(ID[a.l]!=ID[b.l])
		return a.l<b.l;
    if(ID[a.l]&1)
		return a.r<b.r;
	return a.r>b.r;
}

int sum;

inline void Add(reg int x){
	sum+=T[a[x]^K];
	++T[a[x]];
	return;
}

inline void Del(reg int x){
	--T[a[x]];
	sum-=T[K^a[x]];
	return;
}

inline void Work(void){
	sort(Q+1,Q+m+1,cmp);
	reg int lptr=1,rptr=0;
	for(reg int i=1;i<=m;++i){
		while(lptr>Q[i].l)
			Add(--lptr);
		while(lptr<Q[i].l)
			Del(lptr++);
		while(rptr<Q[i].r)
			Add(++rptr);
		while(rptr>Q[i].r)
			Del(rptr--);
		ans[Q[i].ID]=sum;
	}
	for(reg int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return;
}

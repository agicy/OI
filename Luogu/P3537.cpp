#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
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

const int MAXN=1000+5;
const int MAXP=1000000+5;
const int MAXK=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Node{
	int c,a,b;
	inline void Read(void){
		c=read(),a=read(),b=read();
		return;
	}
	inline bool operator<(const Node& x)const{
		return a<x.a;
	}
};

struct Query{
	int m,k,s,id;
	inline void Read(reg int i){
		m=read(),k=read(),s=read(),id=i;
		return;
	}
	inline bool operator<(const Query& a)const{
		return m<a.m;
	}
};

int n,p;
Node a[MAXN];
Query Q[MAXP];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	p=read();
	for(reg int i=1;i<=p;++i)
		Q[i].Read(i);
	return;
}

int f[MAXK];
bool ans[MAXP];

inline void Work(void){
	sort(a+1,a+n+1);
	sort(Q+1,Q+p+1);
	int MaxK=0;
	for(reg int i=1;i<=p;++i)
		MaxK=max(MaxK,Q[i].k);
	reg int lptr=1;
	f[0]=INF;
	for(reg int i=1;i<=p;++i){
		while(lptr<=n&&a[lptr].a<=Q[i].m){
			for(reg int k=MaxK;k>=a[lptr].c;--k)
				f[k]=max(f[k],min(f[k-a[lptr].c],a[lptr].b));
			++lptr;
		}
		ans[Q[i].id]=f[Q[i].k]>Q[i].m+Q[i].s;
	}
	for(reg int i=1;i<=p;++i)
		puts(ans[i]?"TAK":"NIE");
	return;
}

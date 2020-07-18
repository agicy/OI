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

const int MAXN=500000+5;
const int MAXQ=500000+5; 

int n,q;
int c[MAXN];
int ans[MAXQ];

const int MAXLOG2C=20+1;

namespace Basis{
	int unit[MAXLOG2C],pos[MAXLOG2C];
	inline void Init(void){
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void insert(int x,int p){
		for(reg int i=MAXLOG2C-1;i>=0;--i)
			if((x>>i)&1){
				if(!unit[i]){
					unit[i]=x;
					pos[i]=p;
					break;
				}
				if(pos[i]<p){
					swap(pos[i],p);
					swap(x,unit[i]);
				}
				x^=unit[i];
			}
		return;
	}
	inline int query(reg int p){
		reg int res=0;
		for(reg int i=MAXLOG2C-1;i>=0;--i)
			if(p<=pos[i]&&(res^unit[i])>res)
				res^=unit[i];
		return res;
	}
}

struct Querys{
	int id,l,r;
	inline void Read(reg int i){
		id=i;
		l=read(),r=read();
		return;
	}
	inline bool operator<(const Querys& a)const{
		return r<a.r;
	}
};

Querys Q[MAXQ];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	q=read();
	for(reg int i=1;i<=q;++i)
		Q[i].Read(i);
	sort(Q+1,Q+q+1);
	reg int ptr=1;
	for(reg int i=1;i<=q;++i){
		while(ptr<=Q[i].r){
			Basis::insert(c[ptr],ptr);
			++ptr;
		}
		ans[Q[i].id]=Basis::query(Q[i].l);
	}
	for(reg int i=1;i<=q;++i)
		printf("%d\n",ans[i]);
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXQ=1e5+5;
const int MAXLOG2A=20;
const int mod=1e9+7;

struct querys{
	int id,l,x;
	inline bool operator<(const querys& a)const{
		return l<a.l;
	}
};

namespace Basis{
	int cnt;
	int unit[MAXLOG2A];
	inline void insert(reg int x){
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if((x>>i)&1){
				if(!unit[i]){
					++cnt;
					unit[i]=x;
					return;
				}
				x^=unit[i];
			}
		return;
	}
	inline bool check(reg int x){
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if((x>>i)&1)
				x^=unit[i];
		return !x;
	}
}

int n,q;
int base2[MAXN];
int a[MAXN];
querys Q[MAXQ];
int ans[MAXN];

inline void solve(const querys &q,reg int pos){
	if(Basis::check(q.x))
		ans[q.id]=base2[pos-Basis::cnt];
	else
		ans[q.id]=0;
	return;
}

int main(void){
	n=read(),q=read();
	base2[0]=1;
	for(reg int i=1;i<=n;++i)
		base2[i]=(base2[i-1]<<1)>=mod?(base2[i-1]<<1)-mod:(base2[i-1]<<1);
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=q;++i)
		Q[i].id=i,Q[i].l=read(),Q[i].x=read();
	sort(Q+1,Q+q+1);
	reg int ptr=1;
	for(reg int i=1;i<=n;++i){
		Basis::insert(a[i]);
		while(ptr<=q&&Q[ptr].l==i){
			solve(Q[ptr],i);
			++ptr;
		}
	}
	for(reg int i=1;i<=q;++i)
		writeln(ans[i]);
	flush();
	return 0;
}
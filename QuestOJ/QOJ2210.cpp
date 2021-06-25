#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
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

const int MAXN=4e5+5;
const int MAXQ=4e5+5;
const int MAXA=4e5+5;

struct querys{
	int id,l,r;
	inline bool operator<(const querys& a)const{
		return r<a.r;
	}
};

namespace BIT1{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int unit[MAXN];
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
	int n;
	int unit[MAXN];
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
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline int query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
}

int n,Q;
int a[MAXN];
int pos[MAXN],pre[MAXN],lef[MAXA];
querys q[MAXQ];
int ans[MAXQ];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	Q=read();
	for(reg int i=1;i<=Q;++i)
		q[i].id=i,q[i].l=read(),q[i].r=read();
	sort(q+1,q+Q+1);
	BIT1::Init(n),BIT2::Init(n);
	reg int ptr=1;
	for(reg int i=1;i<=n;++i){
		pre[i]=pos[a[i]];
		pos[a[i]]=i;
		if(pre[i])
			BIT1::update(pre[i],-1);
		BIT1::update(i,1);
		if(pre[i]&&pre[pre[i]]&&i+pre[pre[i]]!=(pre[i]<<1)){
			if(lef[a[i]])
				BIT2::update(lef[a[i]],-1);
			lef[a[i]]=pre[pre[i]];
			BIT2::update(lef[a[i]],1);
		}
		while(ptr<=Q&&q[ptr].r==i){
			reg int col=BIT1::query(q[ptr].l,i),cnt=BIT2::query(q[ptr].l,i);
			ans[q[ptr].id]=col+!(col-cnt);
			++ptr;
		}
	}
	for(reg int i=1;i<=n;++i)
		writeln(ans[i]);
	flush();
	return 0;
}
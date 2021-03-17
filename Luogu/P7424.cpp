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

const int MAXN=2e5+5;
const int MAXM=2e5+5;
const int MAXX=2e5+5;

struct Node{
	int l,r,s;
};

int n,m;
Node a[MAXN];
int pos[MAXM];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,tim;
	int unit[MAXX],t[MAXX];
	inline void Init(reg int s){
		n=s,++tim;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i)){
			if(t[i]!=tim)
				t[i]=tim,unit[i]=0;
			unit[i]+=val;
		}
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			if(t[i]==tim)
				res+=unit[i];
		return res;
	}
}

int id[MAXN];
int ans[MAXM];

inline void solve(reg int l,reg int r,reg int L,reg int R){
	if(l>r||L>R)
		return;
	if(l==r){
		ans[l]=R-L+1;
		return;
	}
	reg int mid=(l+r)>>1;
	BIT::Init(2e5);
	for(reg int i=l;i<=mid;++i)
		BIT::update(pos[i],1);
	reg int cntl=0,cntr=0;
	static int idl[MAXN],idr[MAXN];
	for(reg int i=L;i<=R;++i){
		reg int x=BIT::query(a[id[i]].r)-BIT::query(a[id[i]].l-1);
		if(x>=a[id[i]].s)
			idl[++cntl]=id[i];
		else
			a[id[i]].s-=x,idr[++cntr]=id[i];
	}
	for(reg int i=l;i<=mid;++i)
		BIT::update(pos[i],-1);
	for(reg int i=1;i<=cntl;++i)
		id[L+i-1]=idl[i];
	for(reg int i=1;i<=cntr;++i)
		id[R-i+1]=idr[i];
	solve(l,mid,L,L+cntl-1),solve(mid+1,r,R-cntr+1,R);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		a[i].l=read(),a[i].r=read(),a[i].s=read();
		id[i]=i;
	}
	for(reg int i=1;i<=m;++i)
		pos[i]=read();
	pos[m+1]=pos[1];
	solve(1,m+1,1,n);
	for(reg int i=1;i<=m;++i)
		writeln(ans[i]);
	flush();
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

static char wbuf[1<<21];
int wp1;
const int wp2=1<<21;

inline void flush(void){
	fwrite(wbuf,1,wp1,stdout);
	wp1=0;
	return;
}

#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)

inline void write(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0)
		putchar('0');
	else
		while(x)
			buf[++p]=(x%10)^'0',x/=10;
	while(~p)
		putchar(buf[p--]);
	return;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int U=(1<<30)-1;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int sor,tag;
		#define sor(x) unit[(x)].sor
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void build(reg int k,reg int l,reg int r){
		sor(k)=tag(k)=U;
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
		return;
	}
	inline void pushup(reg int k){
		sor(k)=sor(lson)|sor(rson);
		return;
	}
	inline void del(reg int k,reg int val){
		sor(k)&=val;
		tag(k)&=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)!=U){
			del(lson,tag(k));
			del(rson,tag(k));
			tag(k)=U;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			del(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sor(k);
		pushdown(k);
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)|query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	inline void print(reg int k,reg int l,reg int r){
		if(l==r){
			write(sor(k));
			putchar(' ');
			return;
		}
		pushdown(k);
		print(lson,l,mid),print(rson,mid+1,r);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

struct querys{
	int l,r,p;
};

int n,m;
querys q[MAXM];

int main(void){
	freopen("or.in","r",stdin);
	freopen("or.out","w",stdout);
	n=read(),m=read();
	SegmentTree::build(1,1,n);
	for(reg int i=1;i<=m;++i){
		q[i].l=read(),q[i].r=read(),q[i].p=read();
		SegmentTree::update(1,1,n,q[i].l,q[i].r,q[i].p);
	}
	reg bool ans=true;
	for(reg int i=1;i<=m;++i)
		if((SegmentTree::query(1,1,n,q[i].l,q[i].r)&q[i].p)!=q[i].p){
			ans=false;
			break;
		}
	if(ans)
		putchar('Y'),putchar('e'),putchar('s'),putchar('\n'),SegmentTree::print(1,1,n),putchar('\n');
	else
		putchar('N'),putchar('o'),putchar('\n');
	flush();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
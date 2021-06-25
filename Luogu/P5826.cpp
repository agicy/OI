#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
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

inline void Yes(void){
	putchar('Y'),putchar('e'),putchar('s'),putchar('\n');
	return;
}

inline void No(void){
	putchar('N'),putchar('o'),putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXQ=1e5+5;

namespace SegmentTree{
	const int MAXSIZE=MAXM*60;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int val;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define val(x) unit[(x)].val
	};
	int tot;
	Node unit[MAXSIZE];
	inline void Init(void){
		val(0)=-1;
		return;
	}
	inline int update(reg int pre,reg int l,reg int r,reg int pos,reg int Val){
		reg int p=++tot;
		unit[p]=unit[pre];
		val(p)=Val;
		if(l!=r){
			if(pos<=mid)
				lson(p)=update(lson(pre),l,mid,pos,Val);
			else
				rson(p)=update(rson(pre),mid+1,r,pos,Val);
		}
		return p;
	}
	inline int query(reg int p,reg int l,reg int r,reg int pos){
		if(l==r)
			return val(p);
		if(pos<=mid)
			return query(lson(p),l,mid,pos);
		else
			return query(rson(p),mid+1,r,pos);
	}
}

int n,q,m;
int a[MAXN],b[MAXN];
int rt[MAXN];

int main(void){
	read(),n=read(),q=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	SegmentTree::Init();
	for(reg int i=n;i>=1;--i)
		rt[i]=SegmentTree::update(rt[i+1],1,m,a[i],i+1);
	while(q--){
		static int l;
		l=read();
		for(reg int i=1;i<=l;++i)
			b[i]=read();
		reg int pos=1;
		reg bool flag=true;
		for(reg int i=1;i<=l;++i){
			reg int nex=SegmentTree::query(rt[pos],1,m,b[i]);
			if(nex!=-1)
				pos=nex;
			else{
				flag=false;
				break;
			}
		}
		if(flag)
			Yes();
		else
			No();
	}
	flush();
	return 0;
}
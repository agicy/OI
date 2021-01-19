#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXM=2e5+5;

namespace SegmentTree{
	const int MAXSIZE=MAXN*50;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int fa,dep;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define fa(x) unit[(x)].fa
		#define dep(x) unit[(x)].dep
	};
	int tot;
	Node unit[MAXSIZE];
	inline int build(reg int l,reg int r){
		reg int p=++tot;
		if(l==r)
			fa(p)=l;
		else
			lson(p)=build(l,mid),rson(p)=build(mid+1,r);
		return p;
	}
	inline int query(reg int p,reg int l,reg int r,reg int pos){
		if(l==r)
			return p;
		if(pos<=mid)
			return query(lson(p),l,mid,pos);
		else
			return query(rson(p),mid+1,r,pos);
	}
	inline int getFa(reg int id,reg int l,reg int r,reg int x){
		reg int f=query(id,l,r,x);
		if(x==fa(f))
			return f;
		else
			return getFa(id,l,r,fa(f));
	}
	inline int update(reg int pre,reg int l,reg int r,reg int pos,reg int f){
		reg int p=++tot;
		unit[p]=unit[pre];
		if(l==r){
			fa(p)=f;
			return p;
		}
		if(pos<=mid)
			lson(p)=update(lson(pre),l,mid,pos,f);
		else
			rson(p)=update(rson(pre),mid+1,r,pos,f);
		return p;
	}
	inline void update(reg int p,reg int l,reg int r,reg int pos){
		if(l==r){
			++dep(p);
			return;
		}
		if(pos<=mid)
			update(lson(p),l,mid,pos);
		else
			update(rson(p),mid+1,r,pos);
		return;
	}
	#undef mid
}

int n,m;
int rt[MAXM];

int main(void){
	n=read(),m=read();
	rt[0]=SegmentTree::build(1,n);
	for(reg int i=1;i<=m;++i){
		static int opt,a,b,k,ra,rb;
		opt=read();
		switch(opt){
			case 1:{
				a=read(),b=read();
				ra=SegmentTree::getFa(rt[i-1],1,n,a),rb=SegmentTree::getFa(rt[i-1],1,n,b);
				if(SegmentTree::fa(ra)!=SegmentTree::fa(rb)){
					if(SegmentTree::dep(ra)>SegmentTree::dep(rb))
						swap(ra,rb);
					rt[i]=SegmentTree::update(rt[i-1],1,n,SegmentTree::fa(ra),SegmentTree::fa(rb));
					if(SegmentTree::dep(ra)==SegmentTree::dep(rb))
						SegmentTree::update(rt[i],1,n,SegmentTree::fa(rb));
				}
				else
					rt[i]=rt[i-1];
				break;
			}
			case 2:{
				k=read();
				rt[i]=rt[k];
				break;
			}
			case 3:{
				a=read(),b=read();
				ra=SegmentTree::getFa(rt[i-1],1,n,a),rb=SegmentTree::getFa(rt[i-1],1,n,b);
				putchar('0'|(SegmentTree::fa(ra)==SegmentTree::fa(rb))),putchar('\n');
				rt[i]=rt[i-1];
				break;
			}
		}
	}
	flush();
	return 0;
}
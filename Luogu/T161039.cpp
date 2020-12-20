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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0)
		putchar('0');
	else
		while(x)
			buf[++p]=(x%10)^'0',x/=10;
	while(~p)
		putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a<b?b:a;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;

int n,m;

namespace SegmenetTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max;
		int a,b;
		inline int getVal(reg int x){
			return a*x+b;
		}
		#define Max(x) unit[(x)].Max
		#define a(x) unit[(x)].a
		#define b(x) unit[(x)].b
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Max(k)=max(Max(k),max(Max(lson),Max(rson)));
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		Max(k)=0;
		if(l==r){
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int ai,reg int bi){
		if(L<=l&&r<=R){
			reg int lval=unit[k].getVal(l),rval=unit[k].getVal(r);
			reg int nlval=ai*l+bi,nrval=ai*r+bi;
			if(nlval<=lval&&nrval<=rval)
				return;
			if(nlval>=lval&&nrval>=rval){
				a(k)=ai,b(k)=bi;
				Max(k)=max(Max(k),max(nlval,nrval));
				return;
			}
			reg double p=1.0*(b(k)-bi)/(ai-a(k));
			if(lval>nlval)
				if(p<=(double)mid){
					update(lson,l,mid,L,R,a(k),b(k));
					a(k)=ai,b(k)=bi;
				}
				else
					update(rson,mid+1,r,L,R,ai,bi);
			else
				if(p<=(double)mid)
					update(lson,l,mid,L,R,ai,bi);
				else{
					update(rson,mid+1,r,L,R,a(k),b(k));
					a(k)=ai,b(k)=bi;
				}
			Max(k)=max(Max(k),max(nlval,nrval));
			pushup(k);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,ai,bi);
		if(R>mid)
			update(rson,mid+1,r,L,R,ai,bi);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Max(k);
		reg int res=0;
		reg int lef=max(l,L),rig=min(r,R);
		res=max(res,max(unit[k].getVal(lef),unit[k].getVal(rig)));
		if(L<=mid)
			res=max(res,query(lson,l,mid,L,R));
		if(R>mid)
			res=max(res,query(rson,mid+1,r,L,R));
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read(),m=read();
	SegmenetTree::build(1,1,n);
	for(reg int i=1;i<=m;++i){
		static int opt,l,r,x;
		opt=read(),l=read(),r=read();
		switch(opt){
			case 1:{
				x=read();
				SegmenetTree::update(1,1,n,l,r,0,x);
				if(l>1)
					SegmenetTree::update(1,1,n,1,l-1,1,x-l);
				if(r<n)
					SegmenetTree::update(1,1,n,r+1,n,-1,x+r);
				break;
			}
			case 2:{
				reg int ans=SegmenetTree::query(1,1,n,l,r);
				writeln(ans);
				break;
			}
		}
	}
	flush();
	return 0;
}
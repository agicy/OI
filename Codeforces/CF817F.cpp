#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;

struct updates{
	int opt;
	ll l,r;
};

int n;
vector<ll> V;
updates up[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		bool ext0,ext1;
		int tag;
		#define ext0(x) unit[(x)].ext0
		#define ext1(x) unit[(x)].ext1
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<5];
	inline void pushup(reg int k){
		ext0(k)=ext0(lson)||ext0(rson);
		ext1(k)=ext1(lson)||ext1(rson);
		return;
	}
	inline void setOn(reg int k){
		ext0(k)=false,ext1(k)=true,tag(k)=1;
		return;
	}
	inline void setZe(reg int k){
		ext0(k)=true,ext1(k)=false,tag(k)=2;
		return;
	}
	inline void flip(reg int k){
		swap(ext0(k),ext1(k));
		switch(tag(k)){
			case 0:tag(k)=3;break;
			case 1:tag(k)=2;break;
			case 2:tag(k)=1;break;
			case 3:tag(k)=0;break;
			default:assert(false);
		}
		return;
	}
	inline void pushdown(reg int k){
		switch(tag(k)){
			case 0:break;
			case 1:setOn(lson),setOn(rson);break;
			case 2:setZe(lson),setZe(rson);break;
			case 3:flip(lson),flip(rson);break;
			default:assert(false);
		}
		tag(k)=0;
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			ext0(k)=true,ext1(k)=false;
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int opt){
		if(L<=l&&r<=R){
			switch(opt){
				case 1:setOn(k);break;
				case 2:setZe(k);break;
				case 3:flip(k);break;
				default:assert(false);
			}
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,opt);
		if(R>mid)
			update(rson,mid+1,r,L,R,opt);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r){
		if(!ext1(k))
			return l;
		pushdown(k);
		if(ext0(lson))
			return query(lson,l,mid);
		else
			return query(rson,mid+1,r);
	}
	#undef lson
	#undef rson
	#undef mid
	#undef ext0
	#undef ext1
	#undef tag
}

bool ed;

int main(void){
	n=read();
	V.reserve((n<<2)+1);
	for(reg int i=1;i<=n;++i){
		up[i].opt=read(),up[i].l=readll(),up[i].r=readll();
		if(up[i].l!=1)
			V.push_back(up[i].l-1);
		V.push_back(up[i].l);
		V.push_back(up[i].r);
		V.push_back(up[i].r+1);
	}
	V.push_back(1);
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	SegmentTree::build(1,1,V.size());
	for(reg int i=1;i<=n;++i){
		reg int l=lower_bound(V.begin(),V.end(),up[i].l)-V.begin()+1,r=lower_bound(V.begin(),V.end(),up[i].r)-V.begin()+1;
		SegmentTree::update(1,1,V.size(),l,r,up[i].opt);
		writeln(V[SegmentTree::query(1,1,V.size())-1]);
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}
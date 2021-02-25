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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;
const int MAXA=1e5+5;
const int MAXLOG2A=17+1;

namespace Trie{
	const int MAXSIZE=MAXA*120;
	struct Node{
		int ch[2];
		int sum;
		#define sum(x) unit[(x)].sum
		#define ch(x) unit[(x)].ch
	};
	int tot;
	Node unit[MAXSIZE];
	inline int insert(reg int pre,const int& val){
		reg int rt=++tot;
		reg int p=rt;
		unit[p]=unit[pre];
		++sum(p);
		for(reg int i=MAXLOG2A-1;i>=0;--i){
			reg int c=(val>>i)&1;
			ch(p)[c]=++tot;
			p=ch(p)[c],pre=ch(pre)[c];
			unit[p]=unit[pre];
			++sum(p);
		}
		return rt;
	}
	inline int query(reg int p,reg int pre,reg int  val){
		reg int res=0;
		for(reg int i=MAXLOG2A-1;i>=0;--i){
			reg int c=(val>>i)&1;
			if(sum(ch(p)[c^1])-sum(ch(pre)[c^1])){
				p=ch(p)[c^1],pre=ch(pre)[c^1];
				res|=(1<<i);
			}
			else
				p=ch(p)[c],pre=ch(pre)[c];
		}
		return res;
	}
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		vector<pair<int,int>/**/> V;
		int rt;
		#define V(x) unit[(x)].V
		#define rt(x) unit[(x)].rt
	};
	Node unit[MAXN<<2];
	inline void build(reg int k,reg int l,reg int r){
		rt(k)=0;
		V(k).push_back(make_pair(0,0));
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,const int& pos,const int& val,const int& tim){
		int rot=Trie::insert(rt(k),val);
		V(k).push_back(make_pair(rot,tim));
		rt(k)=rot;
		if(l!=r){
			if(pos<=mid)
				update(lson,l,mid,pos,val,tim);
			else
				update(rson,mid+1,r,pos,val,tim);
		}
		return;
	}
	inline int query(reg int k,reg int l,reg int r,const int& L,const int& R,const int& val,const int& tim){
		if(L<=l&&r<=R){
			if(V(k).size()<=1||V(k).back().second<tim)
				return 0;
			reg int lef=1,rig=V(k).size()-1;
			while(lef<rig){
				reg int _mid=(lef+rig)>>1;
				if(V(k)[_mid].second>=tim)
					rig=_mid;
				else
					lef=_mid+1;
			}
			return Trie::query(rt(k),V(k)[lef-1].first,val);
		}
		if(L<=mid&&mid<R)
			return max(query(lson,l,mid,L,R,val,tim),query(rson,mid+1,r,L,R,val,tim));
		else if(L<=mid)
			return query(lson,l,mid,L,R,val,tim);
		else
			return query(rson,mid+1,r,L,R,val,tim);
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m;
int rt[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		static int a;
		a=read();
		rt[i]=Trie::insert(rt[i-1],a);
	}
	SegmentTree::build(1,1,n);
	int tim=0;
	while(m--){
		static int opt,s,v,l,r,x,d;
		opt=read();
		switch(opt){
			case 0:{
				s=read(),v=read();
				SegmentTree::update(1,1,n,s,v,++tim);
				break;
			}
			case 1:{
				l=read(),r=read(),x=read(),d=read();
				writeln(max(Trie::query(rt[r],rt[l-1],x),SegmentTree::query(1,1,n,l,r,x,tim-d+1)));
				break;
			}
		}
	}
	flush();
	return 0;
}
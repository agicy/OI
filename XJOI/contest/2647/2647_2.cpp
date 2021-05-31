#pragma GCC optimize("Ofast")
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
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

template<typename mod_t,mod_t mod> struct modInt{
	mod_t x;
	inline modInt(mod_t x=0):x(x){
		//assert(0<=x&&x<mod);
		return;
	}
	inline modInt operator+(const modInt& a)const{
		mod_t sum=x+a.x;
		return sum>=mod?sum-mod:sum;
	}
	inline modInt operator-(const modInt& a)const{
		mod_t sum=x-a.x;
		return sum<0?sum+mod:sum;
	}
	inline modInt operator-(void)const{
		return modInt(0)-*this;
	}
	inline modInt operator*(const modInt& a)const{
		return 1ll*x*a.x%mod;
	}
	inline void operator+=(const modInt& a){
		x+=a.x;
		if(x>=mod) x-=mod;
		return;
	}
	inline void operator-=(const modInt& a){
		x-=a.x;
		if(x<0) x+=mod;
		return;
	}
	inline void operator*=(const modInt& a){
		x=1ll*x*a.x%mod;
		return;
	}
	inline bool operator==(const modInt& a)const{
		return x==a.x;
	}
	inline bool operator!=(const modInt& a)const{
		return x!=a.x;
	}
	inline bool operator!(void)const{
		return !x;
	}
	inline operator bool(void)const{
		return (bool)x;
	}
	inline bool operator<(const modInt& a)const{
		return x<a.x;
	}
};

const int MAXN=1e5+5;
const int mod1=1e9+7;
const int mod2=1e9+9;

namespace SegmentTree{
	const int MAXSIZE=MAXN*300;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		modInt<int,mod1> Hash1;
		modInt<int,mod2> Hash2;
		inline bool isExist(void)const{
			return Hash1||Hash2;
		}
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define Hash1(x) unit[(x)].Hash1
		#define Hash2(x) unit[(x)].Hash2
	};
	int tot;
	Node unit[MAXSIZE];
	inline void pushup(reg int p){
		Hash1(p)=Hash1(lson(p))+Hash1(rson(p));
		Hash2(p)=Hash2(lson(p))+Hash2(rson(p));
		return;
	}
	inline int update(reg int pre,reg int l,reg int r,reg int pos,modInt<int,mod1> val1,modInt<int,mod2> val2){
		reg int p=++tot;
		unit[p]=unit[pre];
		Hash1(p)+=val1,Hash2(p)+=val2;
		if(l!=r){
			if(pos<=mid)
				lson(p)=update(lson(pre),l,mid,pos,val1,val2);
			else
				rson(p)=update(rson(pre),mid+1,r,pos,val1,val2);
		}
		return p;
	}
	inline void cmp(reg int p,reg int q,reg int l,reg int r,reg bool& t,reg bool& x,reg bool &y){
		if(!p||!q){
			t=p;
			return;
		}
		if(l==r){
			t=unit[p].isExist();
			return;
		}
		if(Hash1(lson(p))!=Hash1(lson(q))||Hash2(lson(p))!=Hash2(lson(q))){
			x=x||unit[rson(p)].isExist(),y=y||unit[rson(q)].isExist();
			return cmp(lson(p),lson(q),l,mid,t,x,y);
		}
		else
			return cmp(rson(p),rson(q),mid+1,r,t,x,y);
	}
	inline void query(reg int p,int l,reg int r,vector<int>& ans){
		if(!p)
			return;
		if(l==r&&unit[p].isExist()){
			ans.push_back(l);
			return;
		}
		if(lson(p))
			query(lson(p),l,mid,ans);
		if(rson(p))
			query(rson(p),mid+1,r,ans);
		return;
	}
	#undef mid
	#undef lson
	#undef rson
	#undef Hash1
	#undef Hash2
}

struct Event{
	int x,id;
	inline Event(reg int x=0,reg int id=0):x(x),id(id){
		return;
	}
	inline bool operator<(const Event& a)const{
		return x<a.x;
	}
};

int n,k;
int tot;
Event e[MAXN<<1];
modInt<int,mod1> base1=1331,bas1[MAXN];
modInt<int,mod2> base2=53,bas2[MAXN];
set<pair<modInt<int,mod1>,modInt<int,mod2>>> S;
int cnt,Rt[MAXN<<1];

inline bool cmp(reg int u,reg int v){
	bool t=false,x=false,y=false;
	SegmentTree::cmp(u,v,1,n,t,x,y);
	if(!t)
		return !x;
	else
		return y;
}

bool ed;

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i){
		e[++tot]=Event(read(),i);
		e[++tot]=Event(read(),-i);
	}
	sort(e+1,e+tot+1);
	bas1[0]=1,bas2[0]=1;
	for(reg int i=1;i<=n;++i)
		bas1[i]=bas1[i-1]*base1,bas2[i]=bas2[i-1]*base2;
	reg int rt=0;
	for(reg int l=1,r;l<=tot;l=r+1){
		r=l;
		while(r<tot&&e[r+1].x==e[l].x)
			++r;
		for(reg int i=l;i<=r;++i)
			if(e[i].id>0)
				rt=SegmentTree::update(rt,1,n,e[i].id,bas1[e[i].id],bas2[e[i].id]);
			else
				rt=SegmentTree::update(rt,1,n,-e[i].id,-bas1[-e[i].id],-bas2[-e[i].id]);
		if(SegmentTree::unit[rt].isExist()&&!S.count(make_pair(SegmentTree::unit[rt].Hash1,SegmentTree::unit[rt].Hash2))){
			S.insert(make_pair(SegmentTree::unit[rt].Hash1,SegmentTree::unit[rt].Hash2));
			Rt[++cnt]=rt;
		}
	}
	nth_element(Rt+1,Rt+k,Rt+cnt+1,cmp);
	vector<int> ans;
	SegmentTree::query(Rt[k],1,n,ans);
	write(ans.size()),putchar('\n');
	for(reg int i=0,siz=ans.size();i<siz;++i)
		write(ans[i]),putchar(i==siz-1?'\n':' ');
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}
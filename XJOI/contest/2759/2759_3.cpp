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
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

template<const uint32_t K> struct Point{
	int x[K];
	inline Point(void){
		return;
	}
	inline Point(const vector<int>& V){
		for(reg uint32_t i=0;i<K;++i)
			x[i]=V[i];
		return;
	}
};

template<const uint32_t K> inline bool operator==(const Point<K>& a,const Point<K>& b){
	for(reg uint32_t i=0;i<K;++i)
		if(a.x[i]!=b.x[i])
			return false;
	return true;
}

template<const uint32_t K> inline Point<K> max(const Point<K>& a,const Point<K>& b){
	Point<K> res;
	for(reg uint32_t i=0;i<K;++i)
		res.x[i]=max(a.x[i],b.x[i]);
	return res;
}

template<const uint32_t K> inline Point<K> min(const Point<K>& a,const Point<K>& b){
	Point<K> res;
	for(reg uint32_t i=0;i<K;++i)
		res.x[i]=min(a.x[i],b.x[i]);
	return res;
}

const int MAXN=1e5+5;
const int MAXQ=1e5+5;
const int inf=0x3f3f3f3f;

int T;
int n,q;
int a[MAXN];

template<const uint32_t K,const uint32_t SIZ,const uint32_t __p,const uint32_t __q> struct kD_Tree{
	struct FHQTreap_Node{
		uint32_t lson,rson,siz;
		int val,Min;
		#define lson(x) FHQTreap_unit[(x)].lson
		#define rson(x) FHQTreap_unit[(x)].rson
		#define siz(x) FHQTreap_unit[(x)].siz
		#define val(x) FHQTreap_unit[(x)].val
		#define Min(x) FHQTreap_unit[(x)].Min
	};
	uint32_t FHQTreap_tot;
	uint32_t FHQTreap_top,FHQTreap_S[SIZ];
	FHQTreap_Node FHQTreap_unit[SIZ];
	inline void FHQTreap_init(void){
		FHQTreap_tot=0,Min(0)=inf;
		return;
	}
	inline void FHQTreap_pushup(reg uint32_t p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		Min(p)=min(val(p),min(Min(lson(p)),Min(rson(p))));
		return;
	}
	inline uint32_t FHQTreap_getId(void){
		return FHQTreap_top?FHQTreap_S[--FHQTreap_top]:++FHQTreap_tot;
	}
	inline uint32_t FHQTreap_New(reg int v){
		reg uint32_t p=FHQTreap_getId();
		lson(p)=rson(p)=0,siz(p)=1;
		val(p)=Min(p)=v;
		return p;
	}
	uint32_t x=123456789,y=362436069,z=521288629;
	inline uint32_t MY_RAND_get(void){
		x^=x<<16,x^=x>>5,x^=x<<1;
		reg uint32_t t=x;
		x=y,y=z,z=t^x^y;
		return z;
	}
	inline uint32_t FHQTreap_merge(reg uint32_t x,reg uint32_t y){
		if(!x||!y)
			return x|y;
		if(MY_RAND_get()%(siz(x)+siz(y))<siz(x)){
			rson(x)=FHQTreap_merge(rson(x),y);
			FHQTreap_pushup(x);
			return x;
		}
		else{
			lson(y)=FHQTreap_merge(x,lson(y));
			FHQTreap_pushup(y);
			return y;
		}
	}
	inline void FHQTreap_split(reg uint32_t p,reg int v,reg uint32_t &x,reg uint32_t &y){
		if(!p){
			x=y=0;
			return;
		}
		if(val(p)<=v){
			x=p;
			FHQTreap_split(rson(x),v,rson(x),y);
			FHQTreap_pushup(x);
		}
		else{
			y=p;
			FHQTreap_split(lson(y),v,x,lson(y));
			FHQTreap_pushup(y);
		}
		return;
	}
	inline void FHQTreap_del(reg uint32_t p){
		if(lson(p))
			FHQTreap_del(lson(p));
		FHQTreap_S[FHQTreap_top++]=p;
		if(rson(p))
			FHQTreap_del(rson(p));
		return;
	}
	#undef lson
	#undef rson
	#undef siz
	#undef val
	#undef Min

	struct Data{
		uint32_t rt;
		Point<K> p;
		inline Data(void){return;}
		inline Data(const uint32_t& rt,const Point<K>& p):rt(rt),p(p){return;}
	};
	inline int getMin(const Data& dat){
		return FHQTreap_unit[dat.rt].Min;
	}
	inline void insert(Data& dat,reg int pos,reg int val){
		uint32_t lef,rig;
		FHQTreap_split(dat.rt,pos,lef,rig);
		dat.rt=FHQTreap_merge(FHQTreap_merge(lef,FHQTreap_New(val)),rig);
		return;
	}
	inline void del(Data& dat,reg int pos){
		uint32_t lef,mid,rig;
		FHQTreap_split(dat.rt,pos,mid,rig);
		FHQTreap_split(mid,pos-1,lef,mid);
		FHQTreap_del(mid);
		dat.rt=FHQTreap_merge(lef,rig);
		return;
	}
	struct Node{
		uint32_t lson,rson,siz;
		Point<K> Max,Min;
		Data dat;
		int sbMin;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define siz(x) unit[(x)].siz
		#define Max(x) unit[(x)].Max
		#define Min(x) unit[(x)].Min
		#define dat(x) unit[(x)].dat
		#define sbMin(x) unit[(x)].sbMin
	};
	uint32_t nex[K];
	uint32_t tot;
	Data tmp[SIZ];
	uint32_t rt;
	uint32_t top,S[SIZ];
	Node unit[SIZ];
	inline uint32_t getId(void){
		return top?S[--top]:++tot;
	}
	inline void init(void){
		Max(0)=Point<K>({-inf,-inf});
		Min(0)=Point<K>({inf,inf});
		sbMin(0)=inf;
		return;
	}
	inline void pushup(reg uint32_t p){
		if(!p)
			pushup(p);
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		Max(p)=max(dat(p).p,max(Max(lson(p)),Max(rson(p))));
		Min(p)=min(dat(p).p,min(Min(lson(p)),Min(rson(p))));
		sbMin(p)=min(getMin(dat(p)),min(sbMin(lson(p)),sbMin(rson(p))));
		return;
	}
	inline uint32_t getNod(const Data& v){
		reg uint32_t p=getId();
		lson(p)=rson(p)=0,siz(p)=1;
		Max(p)=Min(p)=v.p;
		dat(p)=v;
		sbMin(p)=getMin(dat(p));
		return p;
	}
	inline uint32_t build(reg uint32_t l,reg uint32_t r,reg uint32_t wd){
		if(l>r) return 0;
		reg uint32_t mid=(l+r)>>1;
		nth_element(tmp+l,tmp+mid,tmp+r+1,[&,wd](const Data& a,const Data& b){return a.p.x[wd]<b.p.x[wd]||(a.p.x[wd]==b.p.x[wd]&&a.p.x[nex[wd]]<b.p.x[nex[wd]]);});
		reg uint32_t p=getNod(tmp[mid]);
		lson(p)=build(l,mid-1,nex[wd]),rson(p)=build(mid+1,r,nex[wd]);
		pushup(p);
		return p;
	}
	inline void reBuild(reg uint32_t p,reg uint32_t rnk){
		if(lson(p))
			reBuild(lson(p),rnk);
		tmp[siz(lson(p))+rnk+1]=dat(p);
		S[top++]=p;
		if(rson(p))
			reBuild(rson(p),rnk+siz(lson(p))+1);
		return;
	}
	inline void check(reg uint32_t &p,reg uint32_t wd){
		if(siz(p)*__p<__q*max(siz(lson(p)),siz(rson(p)))){
			reBuild(p,0);
			p=build(1,siz(p),wd);
		}
		return;
	}
	inline void insert(reg uint32_t &p,reg uint32_t wd,const Point<K>& pos,const pair<int,int>& val){
		if(!p){
			p=getNod(Data(0,pos));
			insert(dat(p),val.first,val.second);
			pushup(p);
			return;
		}
		if(dat(p).p==pos){
			insert(dat(p),val.first,val.second);
			pushup(p);
			return;
		}
		if(pos.x[wd]<dat(p).p.x[wd]||(pos.x[wd]==dat(p).p.x[wd]&&pos.x[nex[wd]]<dat(p).p.x[nex[wd]]))
			insert(lson(p),nex[wd],pos,val);
		else
			insert(rson(p),nex[wd],pos,val);
		pushup(p);
		check(p,wd);
		return;
	}
	inline void del(reg uint32_t &p,reg uint32_t wd,const Point<K>& pos,reg int val){
		if(!p) assert(false);
		if(dat(p).p==pos){
			del(dat(p),val);
			pushup(p);
			return;
		}
		if(pos.x[wd]<dat(p).p.x[wd]||(pos.x[wd]==dat(p).p.x[wd]&&pos.x[nex[wd]]<dat(p).p.x[nex[wd]]))
			del(lson(p),nex[wd],pos,val);
		else
			del(rson(p),nex[wd],pos,val);
		pushup(p);
		check(p,wd);
		return;
	}
	inline bool in(const uint32_t& p,const Point<K>& p0,const Point<K>& p1){
		for(reg uint32_t i=0;i<K;++i)
			if(!(p0.x[i]<=Min(p).x[i]&&Max(p).x[i]<=p1.x[i]))
				return false;
		return true;
	}
	inline bool check(const uint32_t& p,const Point<K>& p0,const Point<K>& p1){
		for(reg uint32_t i=0;i<K;++i)
			if(dat(p).p.x[i]<p0.x[i]||p1.x[i]<dat(p).p.x[i])
				return false;
		return true;
	}
	inline bool out(const uint32_t& p,const Point<K>& p0,const Point<K>& p1){
		for(reg uint32_t i=0;i<K;++i)
			if(Max(p).x[i]<p0.x[i]||p1.x[i]<Min(p).x[i])
				return true;
		return false;
	}
	inline int query(const uint32_t& p,const Point<K>& p0,const Point<K>& p1){
		if(in(p,p0,p1))
			return sbMin(p);
		if(out(p,p0,p1))
			return inf;
		reg int res=inf;
		if(check(p,p0,p1))
			res=min(res,getMin(dat(p)));
		if(sbMin(lson(p))<=sbMin(rson(p))){
			if(sbMin(lson(p))<res){
				res=min(res,query(lson(p),p0,p1));
				if(sbMin(rson(p))<res)
					res=min(res,query(rson(p),p0,p1));
			}
		}
		else{
			if(sbMin(rson(p))<res){
				res=min(res,query(rson(p),p0,p1));
				if(sbMin(lson(p))<res)
					res=min(res,query(lson(p),p0,p1));
			}
		}
		return res;
	}
	inline kD_Tree(void){
		for(reg uint32_t i=0;i<K;++i)
			nex[i]=(i+1)%K;
		FHQTreap_init();
		init();
		return;
	}
	#undef lson
	#undef rson
	#undef siz
	#undef Max
	#undef Min
	#undef val
	#undef Minv
};

kD_Tree<2,MAXN*2+MAXQ,4,5> Tr;
set<int> S[MAXN];

inline void insert(int id,reg int x,reg int y){
	Tr.insert(Tr.rt,0,Point<2>({x,y}),make_pair(id,id));
	return;
}

inline void del(reg int id,reg int x,reg int y){
	Tr.del(Tr.rt,0,Point<2>({x,y}),id);
	return;
}

inline void update(int pos,reg int v){
	if(a[pos]==v)
		return;
	set<int>::iterator it,lef,rig;
	reg int __v;

	__v=a[pos];
	it=S[__v].lower_bound(pos);
	lef=it,rig=it;
	--lef,++rig;
	del(__v,*lef+1,*it-1),del(__v,*it+1,*rig-1);
	insert(__v,*lef+1,*rig-1);

	S[__v].erase(pos);
	a[pos]=v;

	__v=a[pos];
	S[__v].insert(pos);
	it=S[__v].lower_bound(pos);

	lef=it,rig=it;
	--lef,++rig;
	del(__v,*lef+1,*rig-1);
	insert(__v,*lef+1,*it-1),insert(__v,*it+1,*rig-1);
	return;
}

inline int query(reg int l,reg int r){
	return Tr.query(Tr.rt,Point<2>({1,r}),Point<2>({l,n}));
}

bool ed;

int main(void){
	T=read(),n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(int i=1;i<=n;++i)
		S[a[i]].insert(i);
	for(reg int i=0;i<=n;++i){
		S[i].insert(0),S[i].insert(n+1);
		for(set<int>::iterator it=++S[i].begin(),las=S[i].begin();it!=S[i].end();las=it++)
			insert(i,*las+1,*it-1);
	}
	reg int lastans=0;
	while(q--){
		static int typ,x,y;
		typ=read(),x=read(),y=read();
		switch(typ){
			case 0:{
				x=(x+1ll*T*lastans)%n+1,y=(y+1ll*T*lastans)%n;
				update(x,y);
				break;
			}
			case 1:{
				x=(x+1ll*T*lastans)%n+1,y=(y+1ll*T*lastans)%n+1;
				if(x>y)
					swap(x,y);
				writeln(lastans=query(x,y));
				break;
			}
			default:assert(false);
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}
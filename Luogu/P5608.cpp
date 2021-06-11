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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline unsigned readu(void){
	reg char ch=getchar();
	reg unsigned res=0;
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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int mod=1e9+7;
const int inf=0x3f3f3f3f;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		//assert(0<=x&&x<mod);
		return;
	}
	inline modInt operator+(const modInt& a)const{
		reg int sum=x+a.x;
		return sum>=mod?sum-mod:sum;
	}
	inline modInt operator-(const modInt& a)const{
		reg int sum=x-a.x;
		return sum<0?sum+mod:sum;
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
};

inline modInt fpow(modInt x,reg int exp){
	modInt res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x,exp>>=1;
	}
	return res;
}

int n,m;
modInt a[MAXN];
char opt[MAXN];

struct Segment{
	int len,cnt;
	inline Segment(reg int len=0,reg int cnt=0):len(len),cnt(cnt){
		return;
	}
};

struct Data{
	int len;
	modInt sum,pod;
	modInt lval,rval;
	int llen,rlen;
	modInt lpod,rpod;
	modInt val;
	char opt;
	vector<Segment> V;
	inline void init(modInt x,reg char op){
		len=1;
		sum=pod=x;
		lval=rval=x;
		llen=rlen=1;
		lpod=rpod=x;
		val=x;
		opt=op;
		V={Segment(1,1)};
		return;
	}
};

inline Data merge(Data x,Data y,reg bool flag){
	Data res;
	res.len=x.len+y.len;
	res.sum=x.sum+y.sum;
	res.pod=x.pod*y.pod;
	res.lval=x.lval,res.rval=y.rval;
	switch(x.opt){
		case '*':{
			if(x.llen==x.len)
				res.llen=x.len+y.llen,
				res.lpod=x.pod*y.lpod;
			else
				res.llen=x.llen,
				res.lpod=x.lpod;
			if(y.rlen==y.len)
				res.rlen=y.len+x.rlen,
				res.rpod=y.pod*x.rpod;
			else
				res.rlen=y.rlen,
				res.rpod=y.rpod;
			res.val=(x.rpod*y.lpod)+(x.val-x.rpod)+(y.val-y.lpod);
			break;
		}
		case '+':{
			res.llen=x.llen,
			res.lpod=x.lpod;
			res.rlen=y.rlen;
			res.rpod=y.rpod;
			res.val=x.val+y.val;
			break;
		}
		//default:assert(false);
	}
	res.opt=y.opt;
	if(flag){
		res.V.clear();
		switch(x.opt){
			case '*':{
				reg int ptrx=0,sizx=x.V.size(),ptry=0,sizy=y.V.size();
				reg int __l,__r,__mid;
				__l=0,__r=sizx-1;
				while(__l<__r){
					__mid=(__l+__r)>>1;
					if(x.V[__mid].len<x.rlen)
						__l=__mid+1;
					else
						__r=__mid;
				}
				--x.V[__l].cnt;
				__l=0,__r=sizy-1;
				while(__l<__r){
					__mid=(__l+__r)>>1;
					if(y.V[__mid].len<y.llen)
						__l=__mid+1;
					else
						__r=__mid;
				}
				--y.V[__l].cnt;
				reg int nlen=x.rlen+y.llen;
				while(ptrx<sizx&&ptry<sizy){
					reg int len=min(min(x.V[ptrx].len,y.V[ptry].len),nlen),cnt=0;
					if(len==nlen)
						++cnt,nlen=inf;
					if(x.V[ptrx].len==len)
						cnt+=x.V[ptrx++].cnt;
					if(y.V[ptry].len==len)
						cnt+=y.V[ptry++].cnt;
					if(cnt)
						res.V.push_back(Segment(len,cnt));
				}
				while(ptrx<sizx){
					reg int len=min(x.V[ptrx].len,nlen),cnt=0;
					if(len==nlen)
						++cnt,nlen=inf;
					if(x.V[ptrx].len==len)
						cnt+=x.V[ptrx++].cnt;
					if(cnt)
						res.V.push_back(Segment(len,cnt));
				}
				while(ptry<sizy){
					reg int len=min(y.V[ptry].len,nlen),cnt=0;
					if(len==nlen)
						++cnt,nlen=inf;
					if(y.V[ptry].len==len)
						cnt+=y.V[ptry++].cnt;
					if(cnt)
						res.V.push_back(Segment(len,cnt));
				}
				if(nlen!=inf)
					res.V.push_back(Segment(nlen,1));
				break;
			}
			case '+':{
				reg int ptrx=0,sizx=x.V.size(),ptry=0,sizy=y.V.size();
				while(ptrx<sizx&&ptry<sizy){
					reg int len=min(x.V[ptrx].len,y.V[ptry].len),cnt=0;
					if(x.V[ptrx].len==len)
						cnt+=x.V[ptrx++].cnt;
					if(y.V[ptry].len==len)
						cnt+=y.V[ptry++].cnt;
					if(cnt)
						res.V.push_back(Segment(len,cnt));
				}
				while(ptrx<sizx){
					if(x.V[ptrx].cnt)
						res.V.push_back(x.V[ptrx]);
					++ptrx;
				}
				while(ptry<sizy){
					if(y.V[ptry].cnt)
						res.V.push_back(y.V[ptry]);
					++ptry;
				}
				break;
			}
			//default:assert(false);
		}
	}
	return res;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		Data dat;
		char tOpt;
		int tVal;
		#define dat(x) unit[(x)].dat
		#define tOpt(x) unit[(x)].tOpt
		#define tVal(x) unit[(x)].tVal
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		dat(k)=merge(dat(lson),dat(rson),true);
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		tOpt(k)=tVal(k)=-1;
		if(l==r){
			dat(k).init(a[l],opt[l]);
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void changeVal(reg int k,reg int v){
		tVal(k)=v;
		dat(k).sum=modInt(v)*dat(k).len,dat(k).pod=fpow(modInt(v),dat(k).len);
		dat(k).lval=dat(k).rval=modInt(v);
		dat(k).lpod=fpow(dat(k).lval,dat(k).llen),dat(k).rpod=fpow(dat(k).rval,dat(k).rlen);
		reg int las=0;
		modInt bas=1;
		dat(k).val=0;
		for(reg int i=0,siz=dat(k).V.size();i<siz;++i){
			bas*=fpow(modInt(v),dat(k).V[i].len-las);
			las=dat(k).V[i].len;
			dat(k).val+=bas*dat(k).V[i].cnt;
		}
		return;
	}
	inline void changeOpt(reg int k,reg char v){
		tOpt(k)=v;
		switch(v){
			case '*':{
				dat(k).llen=dat(k).rlen=dat(k).len;
				dat(k).lpod=dat(k).rpod=dat(k).pod;
				dat(k).val=dat(k).pod;
				dat(k).opt=v;
				dat(k).V={Segment(dat(k).len,1)};
				break;
			}
			case '+':{
				dat(k).llen=dat(k).rlen=1;
				dat(k).lpod=dat(k).lval,dat(k).rpod=dat(k).rval;
				dat(k).val=dat(k).sum;
				dat(k).opt=v;
				dat(k).V={Segment(1,dat(k).len)};
				break;
			}
			//default:assert(false);
		}
		return;
	}
	inline void pushdown(reg int k){
		if(tVal(k)!=-1){
			changeVal(lson,tVal(k)),changeVal(rson,tVal(k));
			tVal(k)=-1;
		}
		if(tOpt(k)!=-1){
			changeOpt(lson,tOpt(k)),changeOpt(rson,tOpt(k));
			tOpt(k)=-1;
		}
		return;
	}
	inline void updateVal(reg int k,reg int l,reg int r,reg int L,reg int R,reg int v){
		if(L<=l&&r<=R){
			changeVal(k,v);
			return;
		}
		pushdown(k);
		if(L<=mid)
			updateVal(lson,l,mid,L,R,v);
		if(R>mid)
			updateVal(rson,mid+1,r,L,R,v);
		pushup(k);
		return;
	}
	inline void updateOpt(reg int k,reg int l,reg int r,reg int L,reg int R,reg char v){
		if(L<=l&&r<=R){
			changeOpt(k,v);
			return;
		}
		pushdown(k);
		if(L<=mid)
			updateOpt(lson,l,mid,L,R,v);
		if(R>mid)
			updateOpt(rson,mid+1,r,L,R,v);
		pushup(k);
		return;
	}
	inline Data query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return dat(k);
		pushdown(k);
		if(L<=mid&&mid<R)
			return merge(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R),false);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=readu()%mod;
	for(reg int i=1;i<n;++i)
		opt[i]=read()?'*':'+';
	SegmentTree::build(1,1,n);
	Data val;
	while(m--){
		static int opt,l,r;
		opt=read(),l=read(),r=read();
		switch(opt){
			case 1:{
				SegmentTree::updateVal(1,1,n,l,r,readu()%mod);
				break;
			}
			case 2:{
				SegmentTree::updateOpt(1,1,n,l,r,read()?'*':'+');
				break;
			}
			case 3:{
				writeln(SegmentTree::query(1,1,n,l,r).val.x);
				break;
			}
		}
	}
	flush();
	return 0;
}
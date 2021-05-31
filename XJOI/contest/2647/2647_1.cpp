#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int mod=1e9+7;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
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
	inline modInt operator-(void){
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
};

inline modInt fpow(modInt x,reg int exp){
	modInt res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x;
		exp>>=1;
	}
	return res;
}

const modInt inv2=(mod+1)/2;
const int MAXN=2e5+5;
const int inf=0x3f3f3f3f;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		modInt val[8];
		modInt tCov[3];
		#define val(x) unit[(x)].val
		#define tCov(x) unit[(x)].tCov
	};
	Node unit[MAXN<<2];
	inline void build(reg int k,reg int l,reg int r){
		val(k)[0]=r-l+1;
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
		return;
	}
	inline void pushup(reg int k){
		val(k)[0]=val(lson)[0]+val(rson)[0];
		val(k)[1]=val(lson)[1]+val(rson)[1];
		val(k)[2]=val(lson)[2]+val(rson)[2];
		val(k)[3]=val(lson)[3]+val(rson)[3];
		val(k)[4]=val(lson)[4]+val(rson)[4];
		val(k)[5]=val(lson)[5]+val(rson)[5];
		val(k)[6]=val(lson)[6]+val(rson)[6];
		val(k)[7]=val(lson)[7]+val(rson)[7];
		return;
	}
	inline void add(reg int k,reg int id,modInt Val){
		tCov(k)[id]=Val;
		switch(id){
			case 0:{
				val(k)[1]=val(k)[0]*Val;
				val(k)[3]=val(k)[2]*Val;
				val(k)[5]=val(k)[4]*Val;
				val(k)[7]=val(k)[6]*Val;
				break;
			}
			case 1:{
				val(k)[2]=val(k)[0]*Val;
				val(k)[3]=val(k)[1]*Val;
				val(k)[6]=val(k)[4]*Val;
				val(k)[7]=val(k)[5]*Val;
				break;
			}
			case 2:{
				val(k)[4]=val(k)[0]*Val;
				val(k)[5]=val(k)[1]*Val;
				val(k)[6]=val(k)[2]*Val;
				val(k)[7]=val(k)[3]*Val;
				break;
			}
		}
		return;
	}
	inline void pushdown(reg int k){
		if(tCov(k)[0].x){
			add(lson,0,tCov(k)[0]);
			add(rson,0,tCov(k)[0]);
			tCov(k)[0].x=0;
		}
		if(tCov(k)[1].x){
			add(lson,1,tCov(k)[1]);
			add(rson,1,tCov(k)[1]);
			tCov(k)[1].x=0;
		}
		if(tCov(k)[2].x){
			add(lson,2,tCov(k)[2]);
			add(rson,2,tCov(k)[2]);
			tCov(k)[2].x=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int id,modInt Val){
		if(L<=l&&r<=R){
			add(k,id,Val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,id,Val);
		if(R>mid)
			update(rson,mid+1,r,L,R,id,Val);
		pushup(k);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
	#undef val
	#undef tCov
}

int n;

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
};

int top[3];
Node S[3][MAXN];

inline void update(reg int id,reg int pos,reg int val){
	while(top[id]&&S[id][top[id]].val<val)
		--top[id];
	SegmentTree::update(1,1,n,S[id][top[id]].id+1,pos,id,val);
	S[id][++top[id]]=Node(pos,val);
	return;
}

int main(void){
	n=read();
	SegmentTree::build(1,1,n);
	modInt ans1=0;
	for(reg int i=1;i<=n;++i){
		static int tmp[3];
		tmp[0]=read(),tmp[1]=read(),tmp[2]=read();
		sort(tmp,tmp+3);
		update(0,i,tmp[0]),update(1,i,tmp[1]),update(2,i,tmp[2]);
		ans1+=SegmentTree::unit[1].val[7];
	}
	modInt ans2=modInt(n)*modInt(n+1)*inv2;
	modInt ans=ans1*fpow(ans2,mod-2);
	printf("%d\n",ans.x);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}
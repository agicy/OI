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

const int MAXN=1e5+5;
const int mod=1e9+7;

struct mInt{
	int val;
	inline mInt(reg int x=0){
		val=x;
		return;
	}
	inline mInt operator+(const mInt& a)const{
		reg int res=val+a.val;
		return res>=mod?res-mod:res;
	}
	inline mInt operator-(const mInt& a)const{
		reg int res=val-a.val;
		return res<0?res+mod:res;
	}
	inline mInt operator-(void)const{
		if(val)
			return mod-val;
		else
			return 0;
	}
	inline mInt operator*(const mInt& a)const{
		return 1ll*val*a.val%mod;
	}
};

const mInt inv6=166666668;

inline mInt sqr(mInt x){
	return x*x;
}

int n,m;
mInt x[MAXN];
mInt sumx[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	struct Node{
		mInt v,vi,vii,viii;
		inline Node(mInt v=0,mInt vi=0,mInt vii=0,mInt viii=0):v(v),vi(vi),vii(vii),viii(viii){
			return;
		}
		inline Node operator+(const Node& a)const{
			return Node(v+a.v,vi+a.vi,vii+a.vii,viii+a.viii);
		}
	};
	int n;
	Node unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,const Node& val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]=unit[i]+val;
		return;
	}
	inline Node query(reg int id){
		Node res;
		for(reg int i=id;i;i^=lowbit(i))
			res=res+unit[i];
		return res;
	}
}

inline void update(reg int pos,mInt val){
	mInt val1=val,val2=val1*pos,val3=val2*pos,val4=val3*pos;
	BIT::update(pos,BIT::Node(val1,val2,val3,val4));
	return;
}

inline mInt query(reg int n){
	BIT::Node res=BIT::query(n);
	mInt t=n;
	return inv6*(res.v*(t*(t*(t+6)+11)+6)-res.vi*(t*(t*3+12)+11)+res.vii*(t*3+6)-res.viii);
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read(),sumx[i]=sumx[i-1]+x[i];
	BIT::Init(n);
	while(m--){
		static int opt,l,r;
		static mInt a,tmp;
		opt=read(),l=read(),r=read();
		switch(opt){
			case 1:{
				a=read(),tmp=a+r-l+1;
				update(l,sqr(a)),update(l+1,-a*(a-1)*2+1),update(l+2,sqr(a-1));
				update(r+1,-sqr(tmp)),update(r+2,tmp*(tmp-1)*2-1),update(r+3,-sqr(tmp-1));
				break;
			}
			case 2:{
				writeln((sumx[r]-sumx[l-1]+query(r)-query(l-1)).val);
				break;
			}
		}
	}
	flush();
	return 0;
}
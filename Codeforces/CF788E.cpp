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

inline void writeln(reg ll x){
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

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n,m;
int a[MAXN];
int pre[MAXN],suf[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int unit[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

namespace SegmentTree{
	const int MAXSIZE=MAXN*50;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int sum;
		int B,D;
		int BC,CD;
		int BCD;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sum(x) unit[(x)].sum
		#define B(x) unit[(x)].B
		#define D(x) unit[(x)].D
		#define BC(x) unit[(x)].BC
		#define CD(x) unit[(x)].CD
		#define BCD(x) unit[(x)].BCD
	};
	int tot;
	Node unit[MAXSIZE];
	inline int New(void){
		return ++tot;
	}
	inline void pushup(reg int p){
		sum(p)=add(sum(lson(p)),sum(rson(p)));
		B(p)=add(B(lson(p)),B(rson(p)));
		D(p)=add(D(lson(p)),D(rson(p)));
		BC(p)=add(add(BC(lson(p)),BC(rson(p))),1ll*B(lson(p))*sum(rson(p))%mod);
		CD(p)=add(add(CD(lson(p)),CD(rson(p))),1ll*sum(lson(p))*D(rson(p))%mod);
		BCD(p)=add(add(BCD(lson(p)),BCD(rson(p))),add(1ll*B(lson(p))*CD(rson(p))%mod,1ll*BC(lson(p))*D(rson(p))%mod));
		return;
	}
	inline void update(reg int &p,reg int l,reg int r,reg int pos,reg int Pre,reg int Suf,reg int val){
		if(!p)
			p=New();
		if(l==r){
			B(p)=Pre,D(p)=Suf,sum(p)+=val;
			return;
		}
		if(pos<=mid)
			update(lson(p),l,mid,pos,Pre,Suf,val);
		else
			update(rson(p),mid+1,r,pos,Pre,Suf,val);
		pushup(p);
		return;
	}
	#undef mid
}

int rt[MAXN];
vector<int> V;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		V.push_back(a[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	reg int S=V.size();
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	BIT::Init(S);
	for(reg int i=1;i<=n;++i)
		pre[i]=BIT::query(a[i]),BIT::update(a[i],1);
	BIT::Init(S);
	for(reg int i=n;i>=1;--i)
		suf[i]=BIT::query(a[i]),BIT::update(a[i],1);
	for(reg int i=1;i<=n;++i)
		SegmentTree::update(rt[a[i]],1,n,i,pre[i],suf[i],1);
	reg int ans=0;
	for(reg int i=1;i<=S;++i)
		ans=add(ans,SegmentTree::BCD(rt[i]));
	m=read();
	while(m--){
		static int opt,x;
		opt=read(),x=read();
		ans=sub(ans,SegmentTree::BCD(rt[a[x]]));
		switch(opt){
			case 1:{
				SegmentTree::update(rt[a[x]],1,n,x,0,0,-1);
				break;
			}
			case 2:{
				SegmentTree::update(rt[a[x]],1,n,x,pre[x],suf[x],1);
				break;
			}
		}
		ans=add(ans,SegmentTree::BCD(rt[a[x]]));
		writeln(ans);
	}
	flush();
	return 0;
}
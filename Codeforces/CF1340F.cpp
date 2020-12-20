#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll
inline int read(void){
	int t;
	scanf("%lld",&t);
	return t;
}

const int MAXN=1e5+5;
const int K=500;
const int mod=998244353;
const int p=19260817;
const int invp=494863259;

int n,m;
int basep[MAXN],invbasep[MAXN];
int a[MAXN];

struct Node{
	int *S,len;
	inline Node(void){
		S=NULL,len=0;
		return;
	}
	inline int val(void){
		return S[len];
	}
	inline int calc(reg int x){
		return 1ll*(S[len]-S[len-x]+mod)*invbasep[len-x]%mod;
	}
	inline bool del(reg int v,reg int x){
		return calc(x)==v&&(len-=x,true);
	}
	inline int ins(reg int x){
		if(x>0)
			return S[len+1]=(1ll*x*basep[len]+S[len])%mod,++len;
		else
			return !len||calc(1)==-x&&len--;
	}
};

int top;
Node S[MAXN];

inline bool get(reg int l,reg int r,reg int d,reg Node& res){
	static int p,tmp[4][K+1];
	if(res.S==NULL)
		res.S=tmp[p],p=p+1&3;
	for(res.len=0;l!=r+d;l+=d)
		if(!res.ins(a[l]*d))
			return false;
	return true;
}

inline bool pop(Node x){
	for(reg int len;top&&x.len;x.len-=len){
		len=min(x.len,S[top].len);
		if(!S[top].del(x.calc(len),len))
			return false;
		top-=!S[top].len;
	}
	return !x.len;
}

inline void push(const Node& a){
	if(a.len)
		S[++top]=a;
	return;
}

struct Block{
	int L,R;
	bool re,tag;
	int f[K+1],g[K+1];
	Node pre,suf;
	inline void init(reg int l,reg int r){
		L=l,R=r,re=true,pre.S=f,suf.S=g;
		return;
	}
	inline void build(void){
		if(re)
			re=false,tag=get(R,L,-1,pre)&&get(L,R,1,suf);
		return;
	}
	inline bool solve(reg int l,reg int r){
		if(R<l||L>r)
			return true;
		reg bool res;
		static Node x,y;
		l=max(L,l),r=min(R,r);
		if(L==l&&r==R)
			build(),x=pre,y=suf,res=tag;
		else
			res=get(r,l,-1,x)&&get(l,r,1,y);
		return res&&pop(x)&&(push(y),true);
	}
};

Block b[MAXN/K+1];

inline bool query(reg int l,reg int r){
	if(top=0,(r-l+1)&1)
		return false;
	for(reg int i=1;i<=m;++i)
		if(!b[i].solve(l,r))
			return false;
	return !top;
}

signed main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	basep[0]=invbasep[0]=1;
	for(reg int i=1;i<=n;++i){
		basep[i]=1ll*basep[i-1]*p%mod;
		invbasep[i]=1ll*invbasep[i-1]*invp%mod;
	}
	m=0;
	for(reg int l=1,r;l<=n;l=r+1){
		r=min(n,l+K-1);
		b[++m].init(l,r);
	}
	reg int q=read();
	while(q--){
		static int opt,x,y;
		opt=read(),x=read(),y=read();
		switch(opt){
			case 1:{
				a[x]=y;
				b[(x-1)/K+1].re=true;
				break;
			}
			case 2:{
				puts(query(x,y)?"Yes":"No");
				break;
			}
		}
	}
	return 0;
}
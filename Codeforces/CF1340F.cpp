#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;
const int MAXSQRTN=317+5;
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
	inline int del(reg int v,reg int x){
		return calc(x)==v&&(len-=x,1);
	}
	inline int ins(reg int x){
		if(x>0){
			++len;
			S[len]=(1ll*x*basep[len-1]+S[len-1])%mod;
			return true;
		}
		else
			if(!len)
				return true;
			else
				return calc(1)==-x&&len--;
	}
};

int top;
Node S[MAXN];

const int nex[]={1,2,3,0};

inline bool getLtoR(reg int l,reg int r,reg Node& res){
	static int p,tmp[4][MAXSQRTN];
	if(res.S==NULL)
		res.S=tmp[p],p=nex[p];
	for(res.len=0;l<=r;++l)
		if(!res.ins(a[l]))
			return false;
	return true;
}

inline bool getRtoL(reg int l,reg int r,reg Node& res){
	static int p,tmp[4][MAXSQRTN];
	if(res.S==NULL)
		res.S=tmp[p],p=nex[p];
	for(res.len=0;l>=r;--l)
		if(!res.ins(-a[l]))
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
	int f[MAXSQRTN],g[MAXSQRTN];
	Node pre,suf;
	inline void init(reg int l,reg int r){
		L=l,R=r,re=true,pre.S=f,suf.S=g;
		return;
	}
	inline void build(void){
		if(re)
			re=false,tag=getRtoL(R,L,pre)&&getLtoR(L,R,suf);
		return;
	}
	inline bool solve(reg int l,reg int r){
		reg bool res;
		static Node x,y;
		l=max(L,l),r=min(R,r);
		if(L==l&&r==R)
			build(),x=pre,y=suf,res=tag;
		else
			res=getRtoL(r,l,x)&&getLtoR(l,r,y);
		return res&&pop(x)&&(push(y),1);
	}
};

Block b[MAXSQRTN];

inline bool query(reg int l,reg int r){
	if((r-l+1)&1)
		return false;
	for(reg int i=1;i<=m;++i)
		if(l<=b[i].R&&b[i].L<=r&&!b[i].solve(l,r))
			return false;
	return !top;
}

int main(void){
	n=read(),read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	basep[0]=invbasep[0]=1,m=0;
	reg int B=ceil(sqrt(n));
	for(reg int i=1;i<=n;++i){
		basep[i]=1ll*basep[i-1]*p%mod;
		invbasep[i]=1ll*invbasep[i-1]*invp%mod;
	}
	for(reg int l=1,r;l<=n;l=r+1){
		r=min(n,l+B-1);
		b[++m].init(l,r);
	}
	reg int q=read();
	while(q--){
		static int opt,x,y;
		opt=read(),x=read(),y=read();
		switch(opt){
			case 1:{
				a[x]=y;
				b[(x-1)/B+1].re=true;
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
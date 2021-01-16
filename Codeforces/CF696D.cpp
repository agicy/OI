#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=200+5;
const int MAXS=200+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

namespace AC{
	struct Node{
		int ch[26],fail;
		int val;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define val(x) unit[(x)].val
	};
	int tot;
	Node unit[MAXS];
	inline void insert(reg char *s,reg int len,reg int v){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=s[i]-'a';
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		val(p)+=v;
		return;
	}
	queue<int> Q;
	inline void build(void){
		for(reg int i=0;i<26;++i)
			if(ch(0)[i])
				Q.push(ch(0)[i]);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=0;i<26;++i)
				if(ch(u)[i])
					fail(ch(u)[i])=ch(fail(u))[i],Q.push(ch(u)[i]);
				else
					ch(u)[i]=ch(fail(u))[i];
			val(u)+=val(fail(u));
		}
		return;
	}
}

const int MAXSIZE=200+15;

struct Matrix{
	int n,m;
	ll unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int N=0,reg int M=0,reg ll x=-inf){
		n=N,m=M;
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:-inf;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n,a.m);
		reg ll r;
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]=max(res.unit[i][j],r+a.unit[k][j]);
			}
		return res;
	}
	inline Matrix operator^(reg ll exp){
		Matrix res(n,n,0),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
};

int n;
ll l;
int a[MAXN];
char s[MAXS];

int main(void){
	n=read(),l=readll();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i){
		read(s);
		AC::insert(s,strlen(s),a[i]);
	}
	AC::build();
	Matrix A(1,1+AC::tot),B(1+AC::tot,1+AC::tot);
	for(reg int p=0;p<=AC::tot;++p)
		for(reg int i=0;i<26;++i)
			B.unit[p][AC::ch(p)[i]]=max(B.unit[p][AC::ch(p)[i]],0ll+AC::val(AC::ch(p)[i]));
	A.unit[0][0]=0;
	A=A*(B^l);
	reg ll ans=0;
	for(reg int p=0;p<=AC::tot;++p)
		ans=max(ans,0ll+A.unit[0][p]);
	printf("%lld\n",ans);
	return 0;
}
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

const int MAXN=1e5+5;

int n,m;
int w[MAXN];
unordered_map<int,int> M;

inline int phi(reg int x){
	if(M[x])
		return M[x];
	reg int res=x;
	for(reg int i=2;1ll*i*i<=x;++i)
		if(!(x%i)){
			res=res/i*(i-1);
			while(!(x%i))
				x/=i;
		}
	if(x>1)
		res=res/x*(x-1);
	return M[x]=res;
}

inline int getMod(reg ll x,reg int p){
	return x>=p?x%p+p:x;
}

inline int fpow(reg int x,reg int exp,reg int p){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=getMod(1ll*res*x,p);
		x=getMod(1ll*x*x,p);
		exp>>=1;
	}
	return res;
}

inline int getVal(reg int l,reg int r,reg int p){
	if(l==r||p==1)
		return getMod(w[l],p);
	else
		return fpow(w[l],getVal(l+1,r,phi(p)),p);
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		w[i]=read();
	reg int q=read();
	while(q--){
		static int l,r;
		l=read(),r=read();
		writeln(getVal(l,r,m)%m);
	}
	flush();
	return 0;
}
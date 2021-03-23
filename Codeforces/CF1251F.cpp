#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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

namespace Poly{
	const int p=998244353;
	const int g=3;
	const int invg=332748118;
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=p?a-p:a;
	}
	inline int sub(reg int a,reg int b){
		a-=b;
		return a<0?a+p:a;
	}
	inline int fpow(reg int x,reg int exp){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%p;
			x=1ll*x*x%p;
			exp>>=1;
		}
		return res;
	}
	vector<int> rev;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		rev.resize(limit);
		for(reg int i=0;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	typedef vector<int> poly;
	inline void NTT(reg poly& a,reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			reg int w=fpow(flag==1?g:invg,(p-1)/(i<<1));
			for(reg int j=0;j<limit;j+=(i<<1)){
				reg int e=1;
				for(reg int k=0;k<i;++k,e=1ll*e*w%p){
					reg int x=a[j+k],y=1ll*e*a[i+j+k]%p;
					a[j+k]=add(x,y),a[i+j+k]=sub(x,y);
				}
			}
		}
		if(flag==-1){
			reg int inv=fpow(limit,p-2);
			for(reg int i=0;i<limit;++i)
				a[i]=1ll*a[i]*inv%p;
		}
		return;
	}
	const int B=50;
	inline poly mul(poly a,poly b){
		reg int s=a.size()+b.size()-1;
		if(s<=B){
			poly res;
			res.resize(s);
			for(reg int i=0,siza=a.size();i<siza;++i)
				for(reg int j=0,sizb=b.size();j<sizb;++j)
					res[i+j]=add(res[i+j],1ll*a[i]*b[j]%p);
			return res;
		}
		else{
			reg int limit=getRev(s);
			a.resize(limit),b.resize(limit);
			NTT(a,limit,1),NTT(b,limit,1);
			for(reg int i=0;i<limit;++i)
				a[i]=1ll*a[i]*b[i]%p;
			NTT(a,limit,-1);
			a.resize(s);
			return a;
		}
	}
}

using namespace Poly;

const int MAXN=3e5+5;
const int MAXA=3e5+5;

int n,k,Q;
int cnt[MAXA];
int fac[MAXN<<1],invfac[MAXN<<1];

inline void Init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%p;
	invfac[n]=fpow(fac[n],p-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	return;
}

inline int binom(reg int n,reg int m){
	return 1ll*fac[n]*invfac[m]%p*invfac[n-m]%p;
}

int main(void){
	n=read(),k=read();
	Init(n<<1);
	for(reg int i=1;i<=n;++i)
		++cnt[read()];
	poly ans;
	ans.resize(6e5+1);
	for(reg int i=1;i<=k;++i){
		reg int b=read();
		reg int cnt1=0,cnt2=0;
		for(reg int j=1;j<b;++j)
			switch(cnt[j]){
				case 0:{
					break;
				}
				case 1:{
					++cnt1;
					break;
				}
				default:{
					++cnt2;
					break;
				}
			}
		poly f,g;
		f.resize(cnt1+1),g.resize((cnt2<<1)+1);
		for(reg int j=0,bas=1;j<=cnt1;++j,bas=add(bas,bas))
			f[j]=1ll*bas*binom(cnt1,j)%p;
		for(reg int j=0;j<=(cnt2<<1);++j)
			g[j]=binom(cnt2<<1,j);
		poly tmp=mul(f,g);
		for(reg int j=0;j<=cnt1+(cnt2<<1);++j)
			ans[b+j+1]=add(ans[b+j+1],tmp[j]);
	}
	Q=read();
	while(Q--)
		writeln(ans[read()>>1]);
	flush();
	return 0;
}
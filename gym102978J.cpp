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

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int mod=998244353;

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
	inline modInt operator-(void)const{
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
	modInt res(1);
	while(exp){
		if(exp&1)
			res*=x;
		x*=x;
		exp>>=1;
	}
	return res;
}

namespace Poly{
	const modInt g=3;
	const modInt invg=332748118;
	vector<int> rev;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		if(rev.size()!=(unsigned)limit){
			rev.resize(limit);
			for(reg int i=0;i<limit;++i)
				rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		}
		return limit;
	}
	typedef vector<modInt> poly;
	inline void NTT(reg poly& a,reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			modInt w(fpow(flag==1?g:invg,(mod-1)/(i<<1)));
			for(reg int j=0;j<limit;j+=(i<<1)){
				modInt e(1);
				for(reg int k=0;k<i;++k,e*=w){
					modInt x(a[j+k]),y(e*a[i+j+k]);
					a[j+k]=x+y,a[i+j+k]=x-y;
				}
			}
		}
		if(flag==-1){
			modInt inv=fpow(limit,mod-2);
			for(reg int i=0;i<limit;++i)
				a[i]*=inv;
		}
		return;
	}
	inline void print(const poly& a){
		for(reg int i=0,siz=a.size();i<siz;++i)
			printf("%d%c",a[i].x,i==siz-1?'\n':' ');
		return;
	}
	inline poly add(poly a,poly b){
		a.resize(max(a.size(),b.size()));
		for(reg int i=0,siz=b.size();i<siz;++i)
			a[i]+=b[i];
		return a;
	}
	inline poly mul(poly a,poly b){
		if(a.size()==1u&&b.size()==1u)
			return poly{a[0]*b[0]};
		reg int s=a.size()+b.size()-1;
		reg int limit=getRev(s);
		a.resize(limit),b.resize(limit);
		NTT(a,limit,1),NTT(b,limit,1);
		for(reg int i=0;i<limit;++i)
			a[i]*=b[i];
		NTT(a,limit,-1);
		a.resize(s);
		return a;
	}
	inline poly shiftL(poly a,reg int k){
		poly res;
		res.resize(a.size()-k);
		for(reg int i=0,siz=res.size();i<siz;++i)
			res[i]=a[i+k];
		return res;
	}
	inline poly shiftR(poly a,reg int k){
		poly res;
		res.resize(a.size()+k);
		for(reg int i=0,siz=a.size();i<siz;++i)
			res[i+k]=a[i];
		return res;
	}
}

using namespace Poly;

const int MAXN=2.5e5+5;

int n;
int a[MAXN];
modInt fac[MAXN],invfac[MAXN];

inline modInt binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return fac[n]*invfac[m]*invfac[n-m];
}

inline poly getMov(poly f,reg int k){
	if(!k)
		return f;
	else{
		printf("mov f=:"),print(f);
		reg int siz=f.size();
		reverse(f.begin(),f.end());
		poly tmp;
		tmp.resize(siz);
		printf("k=%d\n",k);
		for(reg int i=0;i<siz;++i)
			tmp[i]=fac[i+k-1]*invfac[i];
		poly g=mul(f,tmp);
		g.resize(siz);
		for(reg int i=0;i<siz;++i)
			g[i]=g[i]*invfac[k-1];
		printf("mov g=:"),print(g);
		return g;
	}
}

inline poly solve(reg int l,reg int r,poly rig){
	if(l==r){
		modInt sum=0;
		for(modInt x:rig)
			sum=sum+x;
		poly res=vector<modInt>{sum};
		printf("l=%d r=%d rig:",l,r),print(rig),printf("res:"),print(res);
		return res;
	}
	reg int mid=(l+r)>>1;
	reg int val=a[mid];
	for(reg int i=mid+1;i<=r;++i)
		a[i]-=val;
	poly urdn=solve(mid+1,r,shiftL(rig,val));
	for(reg int i=mid+1;i<=r;++i)
		a[i]+=val;
	printf("urdn=:"),print(urdn);
	for(reg int i=0,siz=urdn.size();i<siz;++i)
		urdn[i]=urdn[i]*invfac[i];
	printf("proces urdn=:"),print(urdn);
	poly pod;
	reg int delta=r-(mid+1);
	pod.resize(delta+a[mid]+1);
	for(reg int i=-(r-(mid+1));i<=a[mid];++i)
		pod[i+delta]=fac[val-i];
	printf("proces pod=:"),print(pod);
	poly g=mul(urdn,pod);
	printf("proces g=:"),print(g);
	g=shiftL(g,delta);
	g.resize(a[mid]+1);
	for(reg int i=0,siz=g.size();i<siz;++i)
		g[i]=g[i]*fac[val-i];
	poly pat=rig; pat.resize(a[mid]+1);
	g=add(g,getMov(pat,r-(mid+1)));
	printf("g=:"),print(g);
	g=getMov(g,1);
	printf("g=:"),print(g);
	poly ldn=solve(l,mid,g),rdn=getMov(urdn,a[mid]);
	poly res=add(ldn,shiftR(rdn,mid-l+1));
	printf("l=%d r=%d rig:",l,r),print(rig),printf("res:"),print(res);
	return res;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read()-1;
	fac[0]=1;
	for(reg int i=1;i<MAXN;++i)
		fac[i]=fac[i-1]*i;
	invfac[MAXN-1]=fpow(fac[MAXN-1],mod-2);
	for(reg int i=MAXN-2;i>=0;--i)
		invfac[i]=invfac[i+1]*(i+1);
	vector<modInt> rig;
	rig.resize(a[n]+1,modInt(0));
	rig[a[n]]=1;
	poly ans=solve(1,n,rig);
	for(reg int i=0;i<n;++i)
		write(ans[i].x),putchar(' ');
	write(1),putchar('\n');
	flush();
	return 0;
}
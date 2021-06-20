#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e5+10,MAXK=12,inf=1e9+10;

const int mod=1e9+7;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		assert(0<=x&&x<mod);
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
	modInt res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x,exp>>=1;
	}
	return res;
}

int n,k;
int w[MAXK];
int pos[MAXN],dir[MAXN];
int l[MAXK],r[MAXK],ptr[MAXK];
int s[MAXK];
modInt strling2[MAXK][MAXK];
modInt fac[MAXK],invfac[MAXK],inv[MAXK];
modInt poly[MAXK];

inline bool check(void){
	static int Max[MAXK],Min[MAXK];
	for(reg int i=1;i<=k;++i)
		ptr[i]=Max[i]=Min[i]=0;
	for(reg int i=1;i<=n;++i){
		ptr[pos[i]]+=dir[i];
		Max[pos[i]]=max(Max[pos[i]],ptr[pos[i]]),Min[pos[i]]=min(Min[pos[i]],ptr[pos[i]]);
	}
	for(reg int i=1;i<=k;++i)
		if(1-Min[i]>w[i]-Max[i]||ptr[i])
			return false;
	return true;
}

inline modInt calc(reg int x,reg int exp){
	modInt fac=x+1,res=0;
	for(reg int i=0;i<=exp;++i){
		res+=strling2[exp][i]*fac*inv[i+1];
		fac*=modInt(x)-modInt(i);
	}
	return res;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=k;++i)
		w[i]=read();
	for(reg int i=1;i<=n;++i)
		pos[i]=read(),dir[i]=read();
	if(check())
		puts("-1");
	else{
		strling2[0][0]=1;
		for(reg int i=1;i<=k+1;++i){
			strling2[i][0]=0;
			for(reg int j=1;j<=i;++j)
				strling2[i][j]=strling2[i-1][j-1]+strling2[i-1][j]*j;
		}
		fac[0]=1;
		for(reg int i=1;i<=k+1;++i)
			fac[i]=fac[i-1]*i;
		invfac[k+1]=fpow(fac[k+1],mod-2);
		for(reg int i=k;i>=0;--i)
			invfac[i]=invfac[i+1]*(i+1);
		for(reg int i=1;i<=k+1;++i)
			inv[i]=invfac[i]*fac[i-1];
		for(reg int i=1;i<=k;++i)
			l[i]=1,r[i]=w[i],ptr[i]=0;
		modInt ans=0;
		for(reg int i=1;i<=n;++i)
			if(l[pos[i]]<=r[pos[i]]){
				reg bool flag=false;
				ptr[pos[i]]+=dir[i];
				if(r[pos[i]]+ptr[pos[i]]>w[pos[i]])
					--r[pos[i]],flag=true;
				if(l[pos[i]]+ptr[pos[i]]<1)
					++l[pos[i]],flag=true;
				if(flag){
					modInt res=1;
					for(reg int j=1;j<=k;++j)
						if(j!=pos[i])
							res*=modInt(r[j]-l[j]+1);
					ans+=res*i;
				}
			}
		for(reg int i=1;i<=k;++i)
			s[i]=abs(ptr[i]);
		for(reg int i=1;i<=n;++i)
			if(l[pos[i]]<=r[pos[i]]){
				reg bool flag=false;
				ptr[pos[i]]+=dir[i];
				if(r[pos[i]]+ptr[pos[i]]>w[pos[i]])
					--r[pos[i]],flag=true;
				if(l[pos[i]]+ptr[pos[i]]<1)
					++l[pos[i]],flag=true;
				if(flag){
					reg int lim=inf;
					for(reg int j=1;j<=k;++j)
						if(s[j])
							lim=min(lim,(r[j]-l[j]+1<0)?-1:(r[j]-l[j]+1)/s[j]);
					fill(poly,poly+k+1,0);
					poly[0]=i+n,poly[1]=n;
					for(reg int j=1;j<=k;++j)
						if(j!=pos[i]){
							modInt b=r[j]-l[j]+1,a=-modInt(s[j]);
							for(reg int l=k;l>=0;--l){
								poly[l]*=b;
								if(l>=1)
									poly[l]+=poly[l-1]*a;
							}
						}
					for(reg int j=0;j<=k;++j)
						ans+=poly[j]*calc(lim,j);
				}
			}
		printf("%d\n",ans.x);
	}
	return 0;
}
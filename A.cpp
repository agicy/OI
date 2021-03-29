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

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=5e5+5;
const int MAXK=500+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

char n[MAXN];
int len;
int k,a[MAXK];

namespace Subtask1{
	int binom[MAXK][MAXK];
	int tag[MAXN];
	int suma[MAXK],sumb[MAXK];
	int delta[MAXN];
	inline void Solve(void){
		binom[0][0]=1;
		for(reg int i=1;i<=k;++i){
			binom[i][0]=1;
			for(reg int j=1;j<=i;++j)
				binom[i][j]=add(binom[i-1][j-1],binom[i-1][j]);
		}
		reg int flag=1;
		for(reg int i=0;i<len;++i)
			if(n[i]=='1'){
				tag[i]=flag?1:-1;
				flag^=1;
			}
		reg int bas=1;
		suma[0]=1,sumb[0]=0;
		reg int ans=0;
		for(reg int i=0,tmp=0;i<len;++i){
			delta[i]=tmp;
			if(n[i]=='1')
				tmp=add(tmp,fpow(2,len-i-1));
		}
		for(reg int i=0;i<len;++i){
			switch(tag[len-i-1]){
				case 1:{
					reg int sum=0;
					for(reg int j=0;j<k;++j){
						reg int tmp=0;
						for(reg int l=0;l<=j;++l)
							tmp=add(tmp,1ll*binom[j][l]*sumb[l]%mod*fpow(delta[len-i-1],j-l)%mod);
						sum=add(sum,1ll*tmp*a[j]%mod);
					}
					ans=add(ans,sum);
					break;
				}
				case -1:{
					reg int sum=0;
					for(reg int j=0;j<k;++j){
						reg int tmp=0;
						for(reg int l=0;l<=j;++l)
							tmp=add(tmp,1ll*binom[j][l]*suma[l]%mod*fpow(delta[len-i-1],j-l)%mod);
						sum=add(sum,1ll*tmp*a[j]%mod);
					}
					ans=add(ans,sum);
					break;
				}
				default:{
					break;
				}
			}
			static int tmpa[MAXK],tmpb[MAXK];
			for(reg int j=0;j<k;++j)
				tmpa[j]=suma[j],tmpb[j]=sumb[j];
			for(reg int j=0;j<k;++j){
				for(reg int l=0;l<=j;++l)
					sumb[j]=add(sumb[j],1ll*binom[j][l]*tmpa[l]%mod*fpow(bas,j-l)%mod);
				for(reg int l=0;l<=j;++l)
					suma[j]=add(suma[j],1ll*binom[j][l]*tmpb[l]%mod*fpow(bas,j-l)%mod);
			}
			bas=add(bas,bas);
		}
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask2{
	namespace Poly{
		const int p=1e9+7;
		const int B=sqrt(p);
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
		int las;
		inline int getRev(reg int n){
			reg int limit=1,l=0;
			while(limit<n)
				limit<<=1,++l;
			if(limit==las)
				return limit;
			rev.resize(limit);
			for(reg int i=0;i<limit;++i)
				rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
			return las=limit;
		}
		const long double pi=acos(-1.0);
		struct Complex{
			long double x,y;
			inline Complex(reg long double x=0,reg long double y=0):x(x),y(y){
				return;
			}
			inline Complex operator+(const Complex& a)const{
				return Complex(x+a.x,y+a.y);
			}
			inline Complex operator-(const Complex& a)const{
				return Complex(x-a.x,y-a.y);
			}
			inline Complex operator*(const Complex& a)const{
				return Complex(x*a.x-y*a.y,x*a.y+y*a.x);
			}
		};
		typedef vector<int> poly;
		inline void FFT(reg vector<Complex>& a,reg int limit,reg int flag){
			for(reg int i=0;i<limit;++i)
				if(i<rev[i])
					swap(a[i],a[rev[i]]);
			for(reg int i=1;i<limit;i<<=1){
				Complex w(cos(pi/i),flag*sin(pi/i));
				for(reg int j=0;j<limit;j+=(i<<1)){
					Complex e(1,0);
					for(reg int k=0;k<i;++k,e=e*w){
						Complex x=a[j+k],y=e*a[i+j+k];
						a[j+k]=x+y,a[i+j+k]=x-y;
					}
				}
			}
			if(flag==-1)
				for(reg int i=0;i<limit;++i)
					a[i].x/=limit;
			return;
		}
		inline int Mod(reg long double x){
			if(x<0)
				return (ll)(x+0.5)%p+p;
			else
				return (ll)(x+0.5)%p;
		}
		inline poly add(poly a,poly b){
			reg int s=max(a.size(),b.size());
			a.resize(s),b.resize(s);
			for(reg int i=0;i<s;++i)
				a[i]=add(a[i],b[i]);
			return a;
		}
		inline poly mul(poly a,poly b){
			vector<Complex> pA,qA,pB,qB;
			reg int s=a.size()+b.size()-1;
			reg int limit=getRev(s);
			pA.resize(limit),qA.resize(limit),pB.resize(limit),qB.resize(limit);
			for(reg int i=0,siz=a.size();i<siz;++i)
				pA[i]=Complex(a[i]/B,0),qA[i]=Complex(a[i]%B,0);
			for(reg int i=0,siz=b.size();i<siz;++i)
				pB[i]=Complex(b[i]/B,0),qB[i]=Complex(b[i]%B,0);
			FFT(pA,limit,1),FFT(qA,limit,1),FFT(pB,limit,1),FFT(qB,limit,1);
			vector<Complex> p1,p2,p3;
			p1.resize(limit),p2.resize(limit),p3.resize(limit);
			for(reg int i=0;i<limit;++i){
				p1[i]=pA[i]*pB[i];
				p2[i]=pA[i]*qB[i]+qA[i]*pB[i];
				p3[i]=qA[i]*qB[i];
			}
			FFT(p1,limit,-1),FFT(p2,limit,-1),FFT(p3,limit,-1);
			poly res;
			res.resize(s);
			for(reg int i=0;i<s;++i)
				res[i]=add(1ll*Mod(p1[i].x)*B%p*B%p,add(1ll*Mod(p2[i].x)*B%p,Mod(p3[i].x)));
			return res;
		}
	}
	using namespace Poly;
	int fac[MAXK],invfac[MAXK];
	int tag[MAXN];
	int delta[MAXN];
	inline void Solve(void){
		fac[0]=1;
		for(reg int i=1;i<=k;++i)
			fac[i]=1ll*fac[i-1]*i%mod;
		invfac[k]=fpow(fac[k],mod-2);
		for(reg int i=k-1;i>=0;--i)
			invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
		reg int flag=1;
		for(reg int i=0;i<len;++i)
			if(n[i]=='1'){
				tag[i]=flag?1:-1;
				flag^=1;
			}
		reg int bas=1;
		poly suma,sumb;
		suma.resize(k),sumb.resize(k);
		suma[0]=1;
		reg int ans=0;
		for(reg int i=0,tmp=0;i<len;++i){
			delta[i]=tmp;
			if(n[i]=='1')
				tmp=add(tmp,fpow(2,len-i-1));
		}
		for(reg int i=0;i<len;++i){
			switch(tag[len-i-1]){
				case 1:{
					poly tmp;
					tmp.resize(k);
					for(reg int j=0;j<k;++j)
						tmp[j]=delta[len-i-1]?fpow(delta[len-i-1],j):0;
					poly res=mul(sumb,tmp);
					reg int sum=0;
					for(reg int j=0;j<k;++j)
						sum=add(sum,1ll*res[j]*a[j]%mod*fac[j]%mod);
					ans=add(ans,sum);
					break;
				}
				case -1:{
					reg int sum=0;
					poly tmp;
					tmp.resize(k);
					for(reg int j=0;j<k;++j)
						tmp[j]=delta[len-i-1]?fpow(delta[len-i-1],j):0;
					poly res=mul(suma,tmp);
					for(reg int j=0;j<k;++j)
						sum=add(sum,1ll*res[j]*a[j]%mod*fac[j]%mod);
					ans=add(ans,sum);
					break;
				}
				default:{
					break;
				}
			}
			poly tmpa=suma,tmpb=sumb;
			poly tmp;
			tmp.resize(k);
			for(reg int i=0;i<k;++i)
				tmp[i]=fpow(bas,i);
			sumb=add(sumb,mul(tmpa,tmp));
			sumb.resize(k);
			suma=add(suma,mul(tmpb,tmp));
			suma.resize(k);
			bas=add(bas,bas);
		}
		printf("%d\n",ans);
		return;
	}
}

int main(void){
	//freopen("angry.in","r",stdin);
	//freopen("angry.out","w",stdout);
	read(n),len=strlen(n);
	k=read();
	for(reg int i=0;i<k;++i)
		a[i]=read();
	if(1ll*len*len*k<=5e8)
		puts("S1"),
		Subtask1::Solve();
	//else
		puts("S2"),
		Subtask2::Solve();
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
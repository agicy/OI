#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=4e5+5;

namespace Poly{
	const int p=998244353;
	const int g=3;
	const int invg=332748118;
	int r[MAXSIZE<<2];
	inline int pow(reg int x,reg int exp,reg int mod){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%mod;
			x=1ll*x*x%mod;
			exp>>=1;
		}
		return res;
	}
	inline int Init(reg int len){
		reg int limit=1,l=0;
		while(limit<len)
			limit<<=1,++l;
		for(reg int i=1;i<limit;++i)
			r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	inline void NTT(reg int a[],reg int limit,reg int type){
		for(reg int i=0;i<limit;++i)
			if(i<r[i])
				swap(a[i],a[r[i]]);
		for(reg int i=1;i<limit;i<<=1){
			reg int w=pow(type==1?g:invg,(p-1)/(i<<1),p);
			for(reg int j=0;j<limit;j+=(i<<1)){
				reg int e=1;
				for(reg int k=0;k<i;++k,e=1ll*e*w%p){
					reg int x=a[j+k],y=1ll*e*a[j+k+i]%p;
					a[j+k]=(x+y)%p,a[j+k+i]=(x-y+p)%p;
				}
			}
		}
		if(type==-1){
			reg int inv=pow(limit,p-2,p);
			for(reg int i=0;i<limit;++i)
				a[i]=1ll*a[i]*inv%p;
		}
		return;
	}
}

const int Base=10;
const int LgBase=1;

struct BigNumber{
	int l;
	int unit[MAXSIZE];
	inline BigNumber(void){
		l=1;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void GetVal(reg char str[],reg int len){
		l=0;
		memset(unit,0,sizeof(unit));
		for(reg int i=len-1;i>=0;i-=LgBase){
			for(reg int j=max(i-LgBase+1,0);j<=i;++j)
				unit[l]=10*unit[l]+str[j]-'0';
			++l;
		}
		return;
	}
	inline BigNumber operator+(const int a){
		BigNumber res=*this;
		res.unit[0]+=a;
		for(reg int i=0;i<res.l;++i)
			if(res.unit[i]>=Base){
				res.unit[i+1]+=res.unit[i]/Base;
				res.unit[i]%=Base;
			}
			else
				break;
		if(res.unit[res.l])
			++res.l;
		return res;
	}
	inline BigNumber operator*(const BigNumber& a){
		static int A[MAXSIZE<<2],B[MAXSIZE<<2];
		memset(A,0,sizeof(A)),memset(B,0,sizeof(B));
		BigNumber res;
		for(reg int i=0;i<l;++i)
			A[i]=unit[i];
		for(reg int i=0;i<a.l;++i)
			B[i]=a.unit[i];
		reg int limit=Poly::Init(l+a.l);
		Poly::NTT(A,limit,1),Poly::NTT(B,limit,1);
		for(reg int i=0;i<limit;++i)
			A[i]=1ll*A[i]*B[i]%Poly::p;
		Poly::NTT(A,limit,-1);
		for(reg int i=0;i<l+a.l;++i)
			res.unit[i]=A[i];
		res.l=l+a.l;
		for(reg int i=0;i<res.l;++i)
			if(res.unit[i]>=Base){
				res.unit[i+1]+=res.unit[i]/Base;
				res.unit[i]%=Base;
				res.l=max(res.l,i+1);
			}
		while(!res.unit[res.l-1])
			--res.l;
		if(res.l==0)
			res.l=1;
		return res;
	}
	inline void Div(reg int a){
		reg int tmp=0;
		for(reg int i=l-1;i>=0;--i){
			unit[i]=unit[i]+tmp*Base;
			tmp=unit[i]%a;
			unit[i]/=a;
		}
		while(!unit[l-1])
			--l;
		if(l==0)
			l=1;
		return;
	}
	inline void Print(void){
		printf("%d",unit[l-1]);
		for(reg int i=l-2;i>=0;--i)
			printf("%0*d",LgBase,unit[i]);
		putchar('\n');
		return;
	}
};

BigNumber a,b,c,d,ans;
char str[MAXSIZE];

int main(void){
	scanf("%s",str);
	a.GetVal(str,strlen(str));
	a=a+1,b=a+1,c=a+2,d=a+3;
	ans=a*b*c*d;
	ans.Div(24);
	ans.Print();
	return 0;
}
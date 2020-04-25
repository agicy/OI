#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXSIZE=50+5;
const int BASE=1000;
const int LGBASE=3;

struct BigNumber{
	int len,unit[MAXSIZE];
	inline BigNumber(void){
		len=0;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline BigNumber(reg int val){
		len=0;
		memset(unit,0,sizeof(unit));
		for(reg int i=0;i<MAXSIZE;++i){
			unit[i]=val%BASE;
			val/=BASE;
			if(!val){
				len=i;
				break;
			}
		}
		return;
	}
	inline void Fresh(void){
		len=0;
		for(reg int i=0;i<MAXSIZE;++i)
			if(unit[i]>=BASE){
				unit[i+1]+=unit[i]/BASE;
				unit[i]%=BASE;
			}
		for(reg int i=MAXSIZE-1;i>=0;--i){
			if(unit[i]){
				len=i;
				break;
			}
		}
		len=max(len,0);
		return;
	}
	inline BigNumber operator+(const BigNumber& a){
		BigNumber res;
		reg int l=max(len,a.len);
		for(reg int i=0;i<=l;++i)
			res.unit[i]=unit[i]+a.unit[i];
		res.Fresh();
		return res;
	}
	inline BigNumber operator-(const BigNumber& a){
		BigNumber res;
		reg int l=max(len,a.len);
		for(reg int i=0;i<=l;++i)
			res.unit[i]=unit[i]-a.unit[i];
		for(reg int i=0;i<MAXSIZE-1;++i){
			while(res.unit[i]<0){
				--res.unit[i+1];
				res.unit[i]+=BASE;
			}
		}
		res.Fresh();
		return res;
	}
	inline BigNumber operator*(const BigNumber& a){
		BigNumber res;
		for(reg int i=0;i<=len;++i)
			for(reg int j=0;j<=a.len;++j)
				res.unit[i+j]+=unit[i]*a.unit[j];
		res.Fresh();
		return res;
	}
	inline void Print(void)const{
		printf("%d",unit[len]);
		for(reg int i=len-1;i>=0;--i)
            printf("%0*d",LGBASE,unit[i]);
        putchar('\n');
        return;
	}
	inline void operator=(const BigNumber& a){
		len=a.len;
		memcpy(unit,a.unit,sizeof(unit));
		return;
	}
};

int n;
BigNumber Ans1(1),Ans2(3),Ans;
BigNumber four(4);

int main(void){
	scanf("%d",&n);
    for(reg int i=3;i<=n;++i){
		if(i&1)
			Ans1=Ans1+Ans2;
        else
			Ans2=Ans2+Ans1;
	}
    if(n%2)
		Ans=Ans1;
    else
		Ans=Ans2;
	Ans=Ans*Ans;
    if((n&1)==0)
		Ans=Ans-four;
    Ans.Print();
    return 0;
}

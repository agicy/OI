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

namespace Cipolla{
	int alpha,a,mod;
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=mod?a-mod:a;
	}
	inline int sub(reg int a,reg int b){
		a-=b;
		return a<0?a+mod:a;
	}
	struct complex{
		int x,y;
		inline complex(reg int x=0,reg int y=0):x(x),y(y){
			return;
		}
	};
	inline complex operator*(const complex& a,const complex& b){
		return complex(add(1ll*a.x*b.x%mod,1ll*a.y*b.y%mod*alpha%mod),add(1ll*a.y*b.x%mod,1ll*a.x*b.y%mod));
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
	inline complex fpow(complex x,int exp){
		complex res=complex(1,0);
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
	inline pair<int,int> solve(reg int x){
		if(fpow(x,(mod-1)>>1)==mod-1)
			return make_pair(-1,-1);
		srand(time(0));
		while(true){
			a=rand()%mod;
			alpha=sub(1ll*a*a%mod,x);
			if(fpow(alpha,(mod-1)>>1)==mod-1)
				break;
		}
		complex res=fpow(complex(a,1),(mod+1)>>1);
		return make_pair(min(res.x,mod-res.x),max(res.x,mod-res.x));
	}
}

int n;

int main(void){
	reg int T=read();
	while(T--){
		n=read();
		Cipolla::mod=read();
		if(!n)
			puts("0");
		else{
			pair<int,int> ans=Cipolla::solve(n);
			if(~ans.first)
				if(ans.first==ans.second)
					printf("%d\n",ans.first);
				else
					printf("%d %d\n",ans.first,ans.second);
			else
				puts("Hola!");
		}
	}
	return 0;
}
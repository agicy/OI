#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

namespace Mker
{
//  Powered By Kawashiro_Nitori
//  Made In Gensokyo, Nihon
	#include<climits>
	#define ull unsigned long long
	#define uint unsigned int
	ull sd;int op;
	inline void init() {scanf("%llu %d", &sd, &op);}
	inline ull ull_rand()
	{
		sd ^= sd << 43;
		sd ^= sd >> 29;
		sd ^= sd << 34;
		return sd;
	}
	inline ull rand()
	{
		if (op == 0) return ull_rand() % USHRT_MAX + 1;
		if (op == 1) return ull_rand() % UINT_MAX + 1;
		if (op == 2) return ull_rand();
	}
}

const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

const int inv32=281250002;
const int B=31622;

int baby_step[B+5];
int gaint_step[mod/B+5];

int main(void){
	baby_step[0]=1;
	for(reg int i=1;i<B;++i)
		baby_step[i]=3ll*baby_step[i-1]%mod;
	reg int step=3ll*baby_step[B-1]%mod;
	gaint_step[0]=1;
	for(reg int i=1;i<=mod/B;++i)
		gaint_step[i]=1ll*step*gaint_step[i-1]%mod;
	int t;
	scanf("%d",&t);
	Mker::init();
	reg int ans=0;
	while(t--){
		reg ull n=Mker::rand();
		reg int pn=n%(mod-1),cn=n%mod;
		reg int res;
		if(n&1)
			res=1ll*add(1ll*gaint_step[pn/B]*baby_step[pn%B]%mod*sub(36ll*cn%mod,117)%mod,51)*inv32%mod;
		else
			res=1ll*add(1ll*gaint_step[pn/B]*baby_step[pn%B]%mod*sub(36ll*cn%mod,117)%mod,21)*inv32%mod;
		ans^=res;
	}
	printf("%d\n",ans);
	return 0;
}
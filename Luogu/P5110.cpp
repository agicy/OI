#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

namespace Mker
{
	unsigned long long SA,SB,SC;
	void init(){scanf("%llu%llu%llu",&SA,&SB,&SC);}
	inline unsigned long long rand(void)
	{
		SA^=SA<<32,SA^=SA>>13,SA^=SA<<1;
		unsigned long long t=SA;
		SA=SB,SB=SC,SC^=t^SA;return SC;
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

int T;
int bas_94153035[65536],chk_94153035[65536];
int bas_905847205[65536],chk_905847205[65536];

inline int fpow_94153035(reg int x){
	return 1ll*chk_94153035[x>>16]*bas_94153035[x&65535]%mod;
}

inline int fpow_905847205(reg int x){
	return 1ll*chk_905847205[x>>16]*bas_905847205[x&65535]%mod;
}

int main(void){
	bas_94153035[0]=bas_905847205[0]=chk_94153035[0]=chk_905847205[0]=1;
	for(reg int i=1;i<65536;++i){
		bas_94153035[i]=bas_94153035[i-1]*94153035ll%mod;
		chk_94153035[i]=chk_94153035[i-1]*64353223ll%mod;
		bas_905847205[i]=bas_905847205[i-1]*905847205ll%mod;
		chk_905847205[i]=chk_905847205[i-1]*847809841ll%mod;
	}
	scanf("%d",&T),Mker::init();
	reg int ans=0;
	while(T--){
		reg int n=Mker::rand()%(mod-1);
		ans^=233230706ll*sub(fpow_94153035(n),fpow_905847205(n))%mod;
	}
	printf("%d\n",ans);
	return 0;
}
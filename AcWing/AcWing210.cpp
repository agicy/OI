#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

int n,q;

namespace basis{
	const int MAXLOG2A=63;
	ll unit[MAXLOG2A];
	bool flag;
	inline void Init(void){
		flag=false;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void insert(reg ll x){
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if((x>>i)&1){
				if(!unit[i]){
					unit[i]=x;
					return;
				}
				x^=unit[i];
			}
		flag=true;
		return;
	}
	inline ll querykth(reg ll k){
		if(flag)
			--k;
		if(!k)
			return 0;
		reg int cnt=0;
		static ll tmp[MAXLOG2A];
		for(reg int i=0;i<MAXLOG2A;++i){
			for(reg int j=i-1;j>=0;--j)
				if((unit[i]>>j)&1)
					unit[i]^=unit[j];
			if(unit[i])
				tmp[cnt++]=unit[i];
		}
		if(k>=(1ll<<cnt))
			return -1;
		reg ll res=0;
		for(reg int i=0;i<cnt;++i)
			if((k>>i)&1)
				res^=tmp[i];
		return res;
	}
}

int main(void){
	reg int T=read();
	for(reg int Case=1;Case<=T;++Case){
		printf("Case #%d:\n",Case);
		n=read();
		basis::Init();
		for(reg int i=1;i<=n;++i){
			static ll a;
			a=read();
			basis::insert(a);
		}
		q=read();
		while(q--){
			static ll k;
			k=read();
			printf("%lld\n",basis::querykth(k));
		}
	}
	return 0;
}
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

ll l[7],r[7];

const int MAXLOG2A=64;

ll Max[3];
int f[MAXLOG2A][2][2][2];

inline int dfs(reg int dep,reg int k0,reg int k1,reg int k2){
	if(dep==-1)
		return 1;
	if(f[dep][k0][k1][k2]!=-1)
		return f[dep][k0][k1][k2];
	reg int res=0;
	reg int c0=(Max[0]>>dep)&1;
	reg int c1=(Max[1]>>dep)&1;
	reg int c2=(Max[2]>>dep)&1;
	for(reg int p0=0;p0<2;++p0)
	for(reg int p1=0;p1<2;++p1)
	for(reg int p2=0;p2<2;++p2){
		if(p0^p1^p2)
			continue;
		if((k0&&(p0>c0))||(k1&&(p1>c1))||(k2&&(p2>c2)))
			continue;
		res=add(res,dfs(dep-1,k0&&(p0==c0),k1&&(p1==c1),k2&&(p2==c2)));
	}
	return f[dep][k0][k1][k2]=res;
}

inline int getVal(reg int S){
	for(reg int i=0;i<3;++i)
		if(((S>>i)&1)&&!l[i])
			return 0;
	for(reg int i=0;i<3;++i)
		if((S>>i)&1)
			Max[i]=l[i]-1;
		else
			Max[i]=r[i];
	memset(f,-1,sizeof(f));
	return dfs(60,1,1,1);
}

bool ed;

int main(void){
	for(reg int i=0;i<7;++i)
		scanf("%lld%lld",&l[i],&r[i]);
	reg int pod=1,cnt=0;
	for(reg int i=0;i<7;++i)
		pod=1ll*pod*((r[i]-l[i]+1)%mod)%mod;
	reg ll Max0=*min_element(r,r+3),Min0=*max_element(l,l+3);
	reg ll Max1=*min_element(r+3,r+4),Min1=*max_element(l+3,l+4);
	reg ll Max2=*min_element(r+4,r+7),Min2=*max_element(l+4,l+7);
	if(Min0<=Max0&&Min1<=Max1&&Min2<=Max2){
		l[0]=Min0,r[0]=Max0;
		l[1]=Min1,r[1]=Max1;
		l[2]=Min2,r[2]=Max2;
		for(reg int S=0;S<(1<<3);++S)
			if(__builtin_parity(S))
				cnt=sub(cnt,getVal(S));
			else
				cnt=add(cnt,getVal(S));
	}
	printf("%d\n",sub(pod,cnt));
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}
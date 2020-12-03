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

const int MAXN=2e5+5;

int n;
ll s[MAXN],e[MAXN],d[MAXN];

inline ll calc(ll pos){
	reg ll res=0;
	for(reg int i=1;i<=n;++i)
		if(pos>=s[i])
			res+=(min(pos,e[i])-s[i])/d[i]+1ll;
	return res;
}

inline bool check(reg ll mid){
	return calc(mid)&1;
}

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			s[i]=read(),e[i]=read(),d[i]=read();
		reg ll l=0,r=2147483647,mid;
		if(!(calc(r)&1))
			puts("Poor QIN Teng:(");
		else{
			while(l<r){
				mid=(l+r)>>1;
				if(check(mid))
					r=mid;
				else
					l=mid+1;
			}
			if(calc(r)^calc(r-1))
				printf("%lld %lld\n",r,calc(r)-calc(r-1));
		}
	}
	return 0;
}
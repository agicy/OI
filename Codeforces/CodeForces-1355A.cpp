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
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline ll Get(reg ll a){
	int Min=10,Max=0;
	while(a){
		Max=max(Max,(int)(a%10)),
		Min=min(Min,(int)(a%10));
		a/=10;
	}
	return Max*Min;
}

int main(void){
	reg int T=read();
	while(T--){
		reg ll a=read(),K=read();
		while(--K){
			reg ll sum=Get(a);
			if(!sum)
				break;
			else
				a+=sum;
		}
		printf("%lld\n",a);
	}
	return 0;
}
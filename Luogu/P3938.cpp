#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}
inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

const int MAXSIZE=60;

ll f[MAXSIZE];

inline void Init(void){
	f[1]=f[2]=1;
	for(reg int i=3;i<MAXSIZE;++i)
		f[i]=f[i-1]+f[i-2];
	return;
}

int main(void){
	Init();
	reg int m=read();
	while(m--){
		ll a=readll(),b=readll();
		while(a!=b){
			if(a>b)
				swap(a,b);
			reg int p=lower_bound(f+1,f+MAXSIZE,b)-f;
			b-=f[p-1];
		}
		printf("%lld\n",a);
	}
	return 0;
}
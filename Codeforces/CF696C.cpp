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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int p=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-=p:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+p:a;
}

inline int fpow(reg int x,reg ll exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

int main(void){
	reg int k=read();
	reg bool flag=true;
	reg int fa=2,fb=2;
	for(reg int i=1;i<=k;++i){
		static ll a;
		a=readll();
		flag=flag&&(a&1);
		fa=fpow(fa,a),fb=fpow(fb,a);
	}
	fa=1ll*fa*fpow(2,p-2)%p,fb=1ll*fb*fpow(2,p-2)%p;
	if(flag)
		fa=sub(fa,1);
	else
		fa=add(fa,1);
	fa=1ll*fa*fpow(3,p-2)%p;
	printf("%d/%d\n",fa,fb);
	return 0;
}
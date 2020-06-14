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

ll a,b,c,d;

int main(void){
	reg int T=read();
	while(T--){
		a=read(),b=read(),c=read(),d=read();
		if(b<a&&c<=d)
			puts("-1");
		else if(a<=b)
			printf("%lld\n",b);
		else{
			reg ll ans=b+((((a-b)%(c-d))!=0?((a-b)/(c-d)+1):((a-b)/(c-d)))*c);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
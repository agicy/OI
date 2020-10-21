#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	bool f=false;
	char ch=getchar();
	ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return f?-res:res;
}

inline ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}

ll a,b,c,d;

int main(void){
	int T=read();
	while(T--){
		a=read(),b=read(),c=read(),d=read();
		a=abs(a),b=abs(b),c=abs(c),d=abs(d);
		if(a==0&&b==0&&c==0)
			puts(d?"NO":"YES");
		else if(a==0){
			if(d%gcd(b,c)==0)
				puts("YES");
			else
				puts("NO");
		}
		else if(b==0){
			if(d%gcd(a,c)==0)
				puts("YES");
			else
				puts("NO");
		}
		else if(c==0){
			if(d%gcd(a,b)==0)
				puts("YES");
			else
				puts("NO");
		}
		else{
			if(d%gcd(a,b)==0)
				puts("YES");
			else if(d%gcd(b,c)==0)
				puts("YES");
			else if(d%gcd(a,c)==0)
				puts("YES");
			else{
				if(gcd(a,b)!=1&&gcd(c,gcd(a,b))==1)
					puts("YES");
				else if(gcd(b,c)!=1&&gcd(a,gcd(b,c))==1)
					puts("YES");
				else if(gcd(a,c)!=1&&gcd(b,gcd(a,c))==1)
					puts("YES");
				else
					puts("NO");
			}
		}
	}
	return 0;
}
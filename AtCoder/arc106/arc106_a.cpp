#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10ll*res+ch-'0',ch=getchar();
	return f?-res:res;
}

int main(void){
	reg ll n=read();
	for(reg ll i=5,j=1;i<=n;i*=5,++j){
		reg ll res=n-i,cnt=0;
		while(res>1&&res%3==0)
			res/=3,++cnt;
		if(res==1&&cnt>0){
			printf("%lld %lld\n",cnt,j);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
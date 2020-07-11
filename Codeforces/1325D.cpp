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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

ll u,v;

int main(void){
	u=read(),v=read();
	if(u>v)
		puts("-1");
	else if(u==v){
		if(v==0)
			puts("0");
		else
			printf("1\n%lld\n",v);
	}
	else
		if((u&1)!=(v&1))
			puts("-1");
		else{
			reg ll x=(v-u)>>1;
			if((x&u)==0)
				printf("2\n%lld %lld\n",x,x+u);
			else
				printf("3\n%lld %lld %lld\n",x,x,u);
		}
	return 0;
}

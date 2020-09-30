#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXSIZE=50+5;

int f[MAXSIZE];

int main(void){
	reg int T=read();
	while(T--){
		int n=read();
		f[1]=f[2]=1;
		reg ll sum=0;
		for(reg int i=3;i<MAXSIZE;++i){
			f[i]=f[i-1]+f[i-2];
			if(f[i]>n)
				break;
			if(!(f[i]&1))
				sum+=f[i];
		}
		printf("%lld\n",sum);
	}
	return 0;
}
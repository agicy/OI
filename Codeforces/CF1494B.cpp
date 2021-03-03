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

int n,u,r,d,l;

int main(void){
	reg int t=read();
	while(t--){
		n=read(),u=read(),r=read(),d=read(),l=read();
		reg bool flag=false;
		for(reg int S=0;S<16;++S){
			reg int cu=u,cr=r,cl=l,cd=d;
			for(reg int i=0;i<4;++i)
				if((S>>i)&1)
					switch(i){
						case 0:{
							--cu,--cr;
							break;
						}
						case 1:{
							--cu,--cl;
							break;
						}
						case 2:{
							--cd,--cr;
							break;
						}
						case 3:{
							--cd,--cl;
							break;
						}
					}
			if(cu<0||cr<0||cl<0||cd<0)
				continue;
			if(cu>n-2||cr>n-2||cl>n-2||cd>n-2)
				continue;
			flag=true;
			break;
		}
		puts(flag?"YES":"NO");
	}
	return 0;
}
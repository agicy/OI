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

int main(void){
	reg int t=read();
	while(t--){
		reg int n=read();
		reg bool flag=true;
		reg ll sum=0,need=0;
		for(reg int i=0;i<n;++i){
			sum+=read();
			need+=i;
			if(sum<need)
				flag=false;
		}
		puts(flag?"Yes":"No");
	}
	return 0;
}
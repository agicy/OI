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

double a[8];

int main(void){
	reg double sum=0;
	for(reg int i=1;i<=7;++i){
		a[i]=read();
		sum+=a[i];
	}
	reg double ans=1;
	for(reg int i=1;i<=6;++i)
		ans*=a[i]/(sum+1-i)*i;
	ans*=a[7]*7.0;
	printf("%.3lf\n",ans);
	return 0;
}
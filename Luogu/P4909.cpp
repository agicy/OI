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

const int MAXN=5e3+5;
const double inf=1e20;

int n,k;
int h[MAXN];
int f[MAXN];

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		h[i]=read();
	f[1]=1;
	for(reg int i=2;i<=n;++i){
		f[i]=f[i-1]+1;
		reg double slope=h[i]-h[i-1];
		for(reg int j=i-2;j>=max(1,i-k);--j){
			reg double val=1.0*(h[j]-h[i])/(j-i);
			if(val<=slope)
				f[i]=min(f[i],f[j]+1),slope=val;
		}
	}
	printf("%d\n",f[n]);
	return 0;
}
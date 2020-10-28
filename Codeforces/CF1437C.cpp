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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=200+5;

int n;
int t[MAXN];
int f[MAXN];

int main(void){
	reg int q=read();
	while(q--){
		n=read();
		for(reg int i=1;i<=n;++i)
			t[i]=read();
		sort(t+1,t+n+1);
		memset(f,0x3f,sizeof(f));
		f[0]=0;
		for(reg int i=1;i<=2*n;++i)
			for(reg int j=n;j>=1;--j)
				f[j]=min(f[j],f[j-1]+abs(t[j]-i));
		printf("%d\n",f[n]);
	}
	return 0;
}
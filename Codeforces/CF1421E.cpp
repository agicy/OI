#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

inline void cMax(reg ll &a,reg ll b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=2e5+5;

int n;
int a[MAXN];
ll f[MAXN][3][2];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	if(n==1)
		printf("%d\n",a[1]);
	else{
		memset(f,-0x3f,sizeof(f));
		f[0][0][1]=0;
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<3;++j){
				cMax(f[i+1][(j+2)%3][0],f[i][j][0]-a[i+1]);
				cMax(f[i+1][(j+1)%3][0],f[i][j][0]+a[i+1]);
				cMax(f[i+1][(j+2)%3][(i&1)],f[i][j][1]-a[i+1]);
				cMax(f[i+1][(j+1)%3][!(i&1)],f[i][j][1]+a[i+1]);
			}
		printf("%lld\n",f[n][1][0]);
	}
	return 0;
}
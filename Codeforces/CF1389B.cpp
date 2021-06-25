#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXK=MAXN;
const int MAXZ=5+5;

int n,k,z;
int a[MAXN];
int f[MAXZ][MAXK];

int main(void){
	reg int t=read();
	while(t--){
		n=read(),k=read(),z=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		f[0][0]=a[1];
		for(reg int i=0;i<=z;++i)
			for(reg int j=1;j<=k;++j){
				f[i][j]=f[i][j-1]+a[j-i*2+1];
				if(i!=0)
					f[i][j]=max(f[i][j],f[i-1][j-1]+a[j-i*2+1]);
			}
		int ans=0;
		for(reg int i=0;i<=z;++i)
			ans=max(ans,f[i][k]);
		printf("%d\n",ans);
	}
	return 0;
}
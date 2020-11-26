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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=3830+5;

int n,b;
int u[MAXN];
int f[MAXN][2];

int main(void){
	n=read(),b=read();
	for(reg int i=1;i<=n;++i)
		u[i]=read();
	memset(f,-0x3f,sizeof(f));
	f[0][0]=0,f[1][1]=0;
	for(reg int i=2;i<=n;++i)
		for(reg int j=i;j>=1;--j){
			f[j][0]=max(f[j][0],f[j][1]);
			f[j][1]=max(f[j-1][0],f[j-1][1]+u[i]);
		}
	int ans=max(f[b][0],f[b][1]);
	memset(f,-0x3f,sizeof(f));
	f[1][1]=u[1];
	for(reg int i=2;i<=n;++i)
		for(reg int j=i;j>=1;--j){
			f[j][0]=max(f[j][0],f[j][1]);
			f[j][1]=max(f[j-1][0],f[j-1][1]+u[i]);
		}
	ans=max(ans,f[b][1]);
	printf("%d\n",ans);
	return 0;
}
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

const int MAXN=2e5+10;
const int MAXA=2.5e6+5;

int n;
int a[MAXN];
int x[MAXA<<1],y[MAXA<<1];
bool vis[MAXA<<1];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=i+1;j<=n;++j)
			if(vis[a[i]+a[j]]){
				if(x[a[i]+a[j]]!=i&&y[a[i]+a[j]]!=i&&x[a[i]+a[j]]!=j&&y[a[i]+a[j]]!=j){
					printf("YES\n%d %d %d %d\n",i,j,x[a[i]+a[j]],y[a[i]+a[j]]);
					return 0;
				}
			}
			else{
				vis[a[i]+a[j]]=true;
				x[a[i]+a[j]]=i,y[a[i]+a[j]]=j;
			}
	puts("NO");
	return 0;
}
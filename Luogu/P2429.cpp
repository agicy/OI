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

const int MAXN=20+5;
const int mod=376544743;

int n,m;
int p[MAXN];
map<int,bool> M;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		p[i]=read();
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		for(int j=p[i];j<=m;j+=p[i])
			if(!M[j]){
				M[j]=true;
				ans=(ans+j)%mod;
			}
	printf("%d\n",ans);
	return 0;
}
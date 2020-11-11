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

const int MAXN=2e5+5;

int n;
int a[MAXN],b[MAXN];

namespace Subtask2{
	const int MAXSIZE=4e6+5;
	bool vis[MAXSIZE];
	inline void Solve(void){
		reg int res=0;
		memset(vis,false,sizeof(vis));
		for(reg int i=1;i<=n;++i)
			vis[a[i]]=vis[b[i]]=true;
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				res^=(vis[a[i]^b[j]]);
		printf("%d!\n",res);
		return;
	}
}

namespace Subtask4{
	inline void Solve(void){
		puts("0!");
		return;
	}
}

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		for(reg int i=1;i<=n;++i)
			b[i]=read();
		if(n<=2000)
			Subtask2::Solve();
		else
			Subtask4::Solve();
	}
	return 0;
}
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

const int MAXN=2e3+5;
const int MAXK=2e3+5;
const int p=1e9+7;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

int n,k;
int f[MAXN],g[MAXN];

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		f[i]=1;
	for(reg int i=2;i<=k;++i){
		memset(g,0,sizeof(g));
		for(reg int j=1;j<=n;++j)
			for(reg int l=j;l<=n;l+=j)
				g[l]=add(g[l],f[j]);
		memcpy(f,g,sizeof(f));
	}
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		ans=add(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
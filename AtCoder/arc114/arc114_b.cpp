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

const int MAXN=2e5+5;
const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

int n;
int fa[MAXN];

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		fa[i]=i;
	for(reg int i=1;i<=n;++i)
		fa[find(read())]=find(i);
	reg int ans=1;
	for(reg int i=1;i<=n;++i)
		if(i==fa[i])
			ans=add(ans,ans);
	printf("%d\n",ans-1);
	return 0;
}
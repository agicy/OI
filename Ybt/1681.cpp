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

const int MAXN=32;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=mod?sum-mod:sum;
}

int n,p,c;
int a[MAXN];
map<int,int> M;

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

int ans;

inline void dfs1(reg int dep,int pod){
	if(dep==(n>>1))
		++M[pod];
	else{
		dfs1(dep+1,pod);
		dfs1(dep+1,1ll*pod*a[dep]%p);
	}
	return;
}

inline void dfs2(reg int dep,reg int pod){
	if(dep==n){
		int v=1ll*c*fpow(pod,p-2)%p;
		if(M.count(v))
			ans=add(ans,M[v]);
	}
	else{
		dfs2(dep+1,pod);
		dfs2(dep+1,1ll*pod*a[dep]%p);
	}
	return;
}

int main(void){
	n=read(),p=read(),c=read();
	reg int mid=(n>>1);
	for(reg int i=0;i<n;++i)
		a[i]=read();
	if(c>=p)
		puts("0");
	else{
		dfs1(0,1);
		dfs2(mid,1);
		if(c==1)
			ans=add(ans,mod-1);
		printf("%d\n",ans);
	}
	return 0;
}
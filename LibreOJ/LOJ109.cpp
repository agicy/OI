#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=4e6+5;
const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

namespace UnionFind{
	int fa[MAXN];
	inline void Init(reg int n){
		for(reg int i=0;i<n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		fa[find(b)]=find(a);
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n,m;

int main(void){
	n=read(),m=read();
	UnionFind::Init(n);
	reg int ans=0;
	while(m--){
		static int opt,u,v;
		opt=read(),u=read(),v=read();
		switch(opt){
			case 0:{
				UnionFind::merge(u,v);
				break;
			}
			case 1:{
				ans=add(add(ans,ans),UnionFind::search(u,v));
				break;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
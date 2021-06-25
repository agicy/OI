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

const int MAXN=1e3+5;
const int inf=0x3f3f3f3f;

int n;
int fa[MAXN],dep[MAXN];
int id[MAXN];
int Min[MAXN];

inline bool cmp(reg int a,reg int b){
	return dep[a]>dep[b];
}

int main(void){
	n=read();
	id[1]=1;
	for(reg int i=2;i<=n;++i){
		fa[i]=read();
		dep[i]=dep[fa[i]]+1;
		id[i]=i;
	}
	sort(id+1,id+n+1,cmp);
	reg int ans=0;
	fill(Min,Min+n+1,inf);
	for(reg int i=1;i<=n;++i){
		reg int u=id[i];
		reg int f=fa[u],ff=fa[f];
		Min[u]=min(Min[u],min(Min[f]+1,Min[ff]+2));
		if(Min[u]>2){
			Min[ff]=0;
			++ans;
			Min[fa[ff]]=min(Min[fa[ff]],1),Min[fa[fa[ff]]]=min(Min[fa[fa[ff]]],2);
		}
	}
	printf("%d\n",ans);
	return 0;
}
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

const int MAXV=5e4+5;
const int MAXE=1e5+5;

struct Edge{
	int s,t,c,col;
	inline bool operator<(const Edge& a)const{
		return c<a.c||(c==a.c&&col<a.col);
	}
};

int v,e,need;
Edge E[MAXE];

namespace UnionFind{
	int fa[MAXV];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
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
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int main(void){
	v=read(),e=read(),need=read();
	for(reg int i=1;i<=e;++i)
		E[i].s=read()+1,E[i].t=read()+1,E[i].c=read(),E[i].col=read();
	reg int l=-(100+1),r=100+1,mid;
	reg int ans=0;
	while(l<=r){
		mid=(l+r)>>1;
		UnionFind::Init(v);
		for(reg int i=1;i<=e;++i)
			if(!E[i].col)
				E[i].c+=mid;
		reg int sum=0,cnt=0;
		sort(E+1,E+e+1);
		for(reg int i=1;i<=e;++i)
			if(!UnionFind::search(E[i].s,E[i].t)){
				sum+=E[i].c;
				if(!E[i].col)
					++cnt;
				UnionFind::merge(E[i].s,E[i].t);
			}
		for(reg int i=1;i<=e;++i)
			if(!E[i].col)
				E[i].c-=mid;
		if(cnt>=need)
			l=mid+1,ans=sum-need*mid;
		else
			r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
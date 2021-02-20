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

struct Node{
	int id,fa,cnt0,cnt1;
	inline Node(reg int id=0,reg int fa=0,reg int cnt0=0,reg int cnt1=0):id(id),fa(fa),cnt0(cnt0),cnt1(cnt1){
		return;
	}
	inline bool operator<(const Node& a)const{
		if(1ll*cnt0*a.cnt1==1ll*cnt1*a.cnt0)
			return cnt0==a.cnt0?(cnt1==a.cnt1?id<a.id:cnt1<a.cnt1):cnt0<a.cnt0;
		else
			return 1ll*cnt0*a.cnt1<1ll*cnt1*a.cnt0;
	}
	inline bool operator==(const Node& a)const{
		return id==a.id&&cnt0==a.cnt0&&cnt1==a.cnt1;
	}
};

namespace Heap{
	priority_queue<Node,vector<Node>,less<Node>/**/> P,Q;
	inline void push(const Node& x){
		P.push(x);
		return;
	}
	inline void pop(const Node& x){
		Q.push(x);
		return;
	}
	inline Node top(void){
		while(!Q.empty()&&P.top()==Q.top())
			P.pop(),Q.pop();
		return P.top();
	}
}

namespace UnionFind{
	int fa[MAXN];
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
}

int n;
int fa[MAXN];
Node p[MAXN];

int main(void){
	n=read();
	for(reg int i=2;i<=n;++i)
		fa[i]=read();
	for(reg int i=1;i<=n;++i){
		static int v;
		v=read();
		if(!v)
			p[i]=Node(i,fa[i],0,1);
		else
			p[i]=Node(i,fa[i],1,0);
	}
	UnionFind::Init(n);
	for(reg int i=2;i<=n;++i)
		Heap::push(p[i]);
	reg ll ans=0;
	for(reg int i=1;i<n;++i){
		static Node s,fa;
		s=Heap::top();
		Heap::pop(s);
		fa=p[UnionFind::find(s.fa)];
		if(fa.id!=1) Heap::pop(fa);
		ans+=1ll*s.cnt0*fa.cnt1;
		fa.cnt0+=s.cnt0,fa.cnt1+=s.cnt1;
		UnionFind::merge(fa.id,s.id);
		p[fa.id]=fa;
		if(fa.id!=1) Heap::push(fa);
	}
	printf("%lld\n",ans);
	return 0;
}
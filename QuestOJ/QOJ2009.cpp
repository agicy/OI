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
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXM=3e5+5;

struct Node{
	int l,r,a;
	inline Node(reg int l=0,reg int r=0,reg int a=0):l(l),r(r),a(a){
		return;
	}
	inline bool operator<(const Node& a)const{
		return l<a.l||(l==a.l&&r>a.r);
	}
};

int n,m;
Node L[MAXM];
int cnt,head[MAXM],to[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

multiset<ll> f[MAXM];

inline void merge(multiset<ll> &u,multiset<ll> &v){
	if(u.size()<v.size())
		swap(u,v);
	vector<ll> tmp;
	tmp.resize(v.size());
	reg int id=0;
	for(multiset<ll>::iterator it=v.begin();it!=v.end();++it){
		tmp[id++]=*it+*u.begin();
		u.erase(u.begin());
	}
	for(reg int i=0;i<id;++i)
		u.insert(tmp[i]);
	return;
}

inline void dfs(reg int u){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dfs(v);
		merge(f[u],f[v]);
	}
	f[u].insert(-L[u].a);
	return;
}

int main(void){
	//freopen("cover.in","r",stdin);
	//freopen("cover.out","w",stdout);
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int l,r,a;
		l=read(),r=read(),a=read();
		L[i]=Node(l,r,a);
	}
	sort(L+1,L+m+1);
	static int S[MAXM];
	reg int top=0;
	S[++top]=0;
	for(reg int i=1;i<=m;++i){
		while(S[top]&&L[S[top]].r<L[i].r)
			--top;
		Add_Edge(S[top],i);
		S[++top]=i;
	}
	dfs(0);
	reg ll ans=0;
	for(reg int i=1;i<=m;++i){
		if(f[0].size())
			ans-=*f[0].begin(),f[0].erase(f[0].begin());
		printf("%lld%c",ans,i==m?'\n':' ');
	}
	return 0;
}
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

inline int max(reg int a,reg int b){
	return a<b?b:a;
}

const int MAXN=1e5+5;
const int inf=0x7f7f7f7f;

namespace UnionFind{
	int fa[MAXN],siz[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i){
			fa[i]=i;
			siz[i]=1;
		}
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
		if(ra!=rb){
			fa[rb]=ra;
			siz[ra]+=siz[rb];
		}
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n,c;
pair<int,int> a[MAXN];
set<pair<int,int>/**/> S;

int main(void){
	n=read(),c=read();
	for(reg int i=1;i<=n;++i){
		static int x,y;
		x=read(),y=read();
		a[i]=make_pair(x+y,x-y);
	}
	using namespace UnionFind;
	sort(a+1,a+n+1);
	S.insert(make_pair(-inf,0)),S.insert(make_pair(inf,0));
	S.insert(make_pair(a[1].second,1));
	Init(n);
	for(int l=1,i=2;i<=n;++i){
		while(a[i].first-a[l].first>c)
			S.erase(make_pair(a[l].second,l)),++l;
		auto it=S.lower_bound(make_pair(a[i].second,0));
		if(it->first-a[i].second<=c)
			merge(i,it->second);
		--it;
		if(a[i].second-it->first<=c)
			merge(i,it->second);
		S.insert(make_pair(a[i].second,i));
	}
	reg int ans=0,Max=0;
	for(reg int i=1;i<=n;++i)
		if(i==find(i)){
			++ans;
			Max=max(Max,siz[find(i)]);
		}
	printf("%d %d\n",ans,Max);
	return 0;
}
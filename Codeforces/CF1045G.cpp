#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

struct Node{
	int l,r,len,x,q;
	inline bool operator<(const Node &a)const{
		return q<a.q;
	}
};

inline bool cmp(const Node& a,const Node& b){
	return a.len>b.len;
}

int n,k;
Node a[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline int query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
}

ll ans;

inline void solve(reg int l,reg int r){
	if(l==r)
		return;
	reg int mid=(l+r)>>1;
	solve(l,mid),solve(mid+1,r);
	reg int L=l,R=l-1;
	for (reg int i=mid+1;i<=r;++i){
		while(L<=mid&&a[i].q-a[L].q>k)
			BIT::update(a[L++].x,-1);
		while(R<mid&&a[R+1].q-a[i].q<=k)
			BIT::update(a[++R].x,1);
		ans+=BIT::query(a[i].l,a[i].r);
	}
	for(reg int i=L;i<=R;++i)
		BIT::update(a[i].x,-1);
	sort(a+l,a+r+1);
	return;
}


int main(void){
	n=read(),k=read();
	vector<int> V;
	for(reg int i=1;i<=n;++i){
		a[i].x=read(),a[i].len=read(),a[i].q=read();
		V.push_back(a[i].x);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i){
		a[i].l=lower_bound(V.begin(),V.end(),a[i].x-a[i].len)-V.begin()+1;
		a[i].r=upper_bound(V.begin(),V.end(),a[i].x+a[i].len)-V.begin();
		a[i].x=lower_bound(V.begin(),V.end(),a[i].x)-V.begin()+1;
	}
	sort(a+1,a+n+1,cmp);
	BIT::Init(V.size());
	solve(1,n);
	printf("%lld\n",ans);
	return 0;
}
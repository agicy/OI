#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF (1e8+5)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=300000+5;
const int MAXQ=300000+5;

int n,k,Q;
vector<int> V;

inline int GetID(int x){
	return lower_bound(V.begin(),V.end(),x)-V.begin()+1;
}

struct Heap{
	priority_queue<int,vector<int>,greater<int>/**/> a,b;
	inline void push(int x){
		a.push(x);
		return;
	}
	inline void del(int x){
		b.push(x);
		return;
	}
	inline int top(void){
		while(!b.empty()&&a.top()==b.top())
			a.pop(),b.pop();
		return a.top();
	}
};

namespace SegmentTree{
	const int T=(1<<19)+MAXN;
	Heap q[MAXN];
	struct Node{
		int Max,Min;
		#define Max(x) unit[(x)].Max
		#define Min(x) unit[(x)].Min
	};
	Node unit[T];
	int n,d;
	inline void Build(reg int size,reg int k){
		n=size;
		d=1;
		while(d<n)
			d<<=1;
		--d;
		for(reg int i=n+d+1;i>=1;--i)
			Min(i)=INF;
		for(reg int i=1;i<=n;++i)
			q[i].push(INF);
		for(reg int i=1;i<=k;++i)
			q[n].push(-INF);
		for(reg int i=n+d;i;i>>=1)
			Min(i)=-INF;
		for(reg int i=1;i<n;++i)
			Max(d+i)=V[i-1];
		Max(d+n)=2*INF;
		for(reg int i=d;i>=1;--i)
			Max(i)=max(Max(i<<1),Max(i<<1|1));
		return;
	}
	inline int Solve(reg int x){
		if(Min(n+d)==-INF)
			return -1;
		reg int i=1;
		int now=INF;
		while(i<=d)
			if(x>Max(i<<1))
				i=(i<<1|1);
			else if(Max(i<<1)+1+min(Min(i<<1|1),now)<=2*x)
				i=i<<1|1;
			else{
				now=min(Min(i<<1|1),now);
				i=i<<1;
			}
		return min(2*x-min(now,Min(i)),Max(i))-x;
	}
	inline void Update(reg int i){
		Min(i+d)=q[i].top();
		i+=d;
		while(i>>=1){
			if(Min(i)==min(Min(i<<1),Min(i<<1|1)))
				break;
			Min(i)=min(Min(i<<1),Min(i<<1|1));
		}
		return;
	}
	inline void Add(reg int i,reg int x){
		q[i].push(x);
		Update(i);
		return;
	}
	inline void Del(reg int i,reg int x){
		q[i].del(x);
		Update(i);
		return;
	}
	inline void Modify(reg int i,reg int x0,reg int x){
		q[i].del(x0),q[i].push(x);
		Update(i);
		return;
	}
}

multiset<int> S[MAXN];

inline void Add(multiset<int> &S,int x){
	multiset<int>::iterator it1=S.insert(x),it2=it1;
	--it1,++it2;
	SegmentTree::Add(GetID(x),*it1);
	SegmentTree::Modify(GetID(*it2),*it1,x);
	return;
}

inline void Del(multiset<int> &S,int x){
	multiset<int>::iterator it=S.find(x),it1=it,it2=it;
	--it1,++it2;
	SegmentTree::Del(GetID(x),*it1);
	SegmentTree::Modify(GetID(*it2),x,*it1);
	S.erase(it);
	return;
}

struct Node{
	int x,t,a;
	inline Node(reg int x=0,reg int t=0,reg int a=0):x(x),t(t),a(a){
		return;
	}
	inline bool operator<(const Node& x)const{
		return a<x.a;
	}
	inline void add(void){
		Add(S[t],x);
		return;
	}
	inline void del(void){
		Del(S[t],x);
		return;
	}
};

Node qa[MAXN],qb[MAXN],q[MAXQ];

int ans[MAXQ];

int main(void){
	n=read(),k=read(),Q=read();
	for(reg int i=1;i<=n;++i){
		static int x,t,a,b;
		x=read(),t=read(),a=read(),b=read();
		qa[i]=Node(x,t,a);
		qb[i]=Node(x,t,b);
		V.push_back(x);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	reg int m=V.size();
	SegmentTree::Build(m+1,k);
	for(reg int i=1;i<=Q;++i){
		static int x,a;
		x=read(),a=read();
		q[i]=Node(x,i,a);
	}
	sort(qa+1,qa+n+1);
	sort(qb+1,qb+n+1);
	sort(q+1,q+Q+1);
	for(reg int i=1;i<=k;++i)
		S[i].insert(-INF),S[i].insert(INF);
	for(reg int i=1,lptr=1,rptr=1;i<=Q;++i){
		while(lptr<=n&&qa[lptr].a<=q[i].a)
			qa[lptr++].add();
		while(rptr<=n&&qb[rptr].a<q[i].a)
			qb[rptr++].del();
		ans[q[i].t]=SegmentTree::Solve(q[i].x);
	}
	for(reg int i=1;i<=Q;++i)
		printf("%d\n",ans[i]);
	return 0;
}
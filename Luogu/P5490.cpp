#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

struct Event{
	int x,l,r,val;
	inline Event(void){return;}
	inline Event(const int& x,const int& l,const int& r,const int& val):x(x),l(l),r(r),val(val){return;}
	inline bool operator<(const Event& a)const{return x<a.x;}
};

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int len;
		int tag;
		int sum;
		#define len(x) unit[(x)].len
		#define tag(x) unit[(x)].tag
		#define sum(x) unit[(x)].sum
	};
	Node unit[MAXN<<3];
	inline void build(reg int k,reg int l,reg int r,const vector<int> &V){
		len(k)=V[r+1]-V[l];
		tag(k)=0;
		if(l==r)
			return;
		build(lson,l,mid,V),build(rson,mid+1,r,V);
		return;
	}
	inline void pushup(reg int k,reg int l,reg int r){
		if(tag(k))
			sum(k)=len(k);
		else if(l==r)
			sum(k)=0;
		else
			sum(k)=sum(lson)+sum(rson);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			tag(k)+=val;
			pushup(k,l,r);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k,l,r);
		return;
	}
}

int n;

bool ed;

int main(void){
	n=read();
	vector<int> Vx,Vy;
	Vx.reserve(n<<1),Vy.reserve(n<<1);
	vector<Event> E;
	E.reserve(n<<1);
	for(reg int i=1;i<=n;++i){
		static int x1,y1,x2,y2;
		x1=read(),y1=read(),x2=read(),y2=read();
		Vx.push_back(x1),Vx.push_back(x2);
		Vy.push_back(y1),Vy.push_back(y2);
		E.push_back(Event(x1,y1,y2,1));
		E.push_back(Event(x2,y1,y2,-1));
	}
	sort(Vx.begin(),Vx.end()),Vx.erase(unique(Vx.begin(),Vx.end()),Vx.end());
	sort(Vy.begin(),Vy.end()),Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
	for(reg int i=0,siz=E.size();i<siz;++i){
		E[i].x=lower_bound(Vx.begin(),Vx.end(),E[i].x)-Vx.begin();
		E[i].l=lower_bound(Vy.begin(),Vy.end(),E[i].l)-Vy.begin();
		E[i].r=lower_bound(Vy.begin(),Vy.end(),E[i].r)-Vy.begin();
		assert(E[i].l<E[i].r);
	}
	sort(E.begin(),E.end());
	SegmentTree::build(1,0,Vy.size()-2,Vy);
	reg ll ans=0;
	for(reg int i=0,j=0,siz=Vx.size();i<siz-1;++i){
		while(j<(int)E.size()&&E[j].x<=i){
			SegmentTree::update(1,0,Vy.size()-2,E[j].l,E[j].r-1,E[j].val);
			++j;
		}
		ans+=1ll*(Vx[i+1]-Vx[i])*SegmentTree::unit[1].sum;
	}
	printf("%lld\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}
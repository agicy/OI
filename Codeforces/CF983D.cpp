#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;

struct Line{
	int l,r,w,c;
	Line(reg int l=0,reg int r=0,reg int w=0,reg int c=0):l(l),r(r),w(w),c(c){
		return;
	}
	inline bool operator<(const Line& a)const{
		return w<a.w;
	}
};

int n;
Line a[MAXN<<1];
pair<int,int> inv[MAXN];
bool ins[MAXN],vis[MAXN];

struct Heap{
	priority_queue<int> p,q;
	inline void pop(int x){
		q.push(x);
		while(!q.empty()&&p.top()==q.top())
			p.pop(),q.pop();
		return;
	}
	inline bool empty(void){
		return p.empty();
	}
	inline void push(int x){
		p.push(x);
		while(!q.empty()&&p.top()==q.top())
			p.pop(),q.pop();
		return;
	}
	inline int top(void){
		return p.top();
	}
};

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max,Min;
		Heap Q;
		#define Max(x) unit[(x)].Max
		#define Min(x) unit[(x)].Min
		#define Q(x) unit[(x)].Q
	};
	Node unit[MAXN<<3];
	inline void pushup(reg int k,reg bool flag){
		if(flag)
			Max(k)=Min(k)=0;
		else
			Max(k)=max(Max(lson),Max(rson)),Min(k)=min(Min(lson),Min(rson));
		if(!Q(k).empty()){
			if(vis[Q(k).top()])
				Min(k)=max(Min(k),Q(k).top());
			else
				Max(k)=max(Max(k),Q(k).top());}
		if(Max(k)<Min(k))
			Max(k)=0;
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int w){
		if(L<=l&&r<=R){
			if(w){
				if(ins[w])
					Q(k).pop(w);
				else
					Q(k).push(w);
			}
			pushup(k,l==r);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,w);
		if(R>mid)
			update(rson,mid+1,r,L,R,w);
		pushup(k,false);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
	#undef Max
	#undef Min
	#undef Q
}


int main(void){
	n=read();
	reg int m=n<<1;
	vector<int> V;
	V.resize(m);
	for(reg int i=0;i<n;++i){
		static int lx,ly,rx,ry;
		lx=read(),ly=read(),rx=read(),ry=read();
		a[i<<1]=Line(ly,ry,lx,i+1);
		a[i<<1|1]=Line(ly,ry,rx,i+1);
		V[i<<1]=ly,V[i<<1|1]=ry;
		inv[i+1]=make_pair(ly,ry);
	}
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=0;i<m;++i){
		a[i].l=lower_bound(V.begin(),V.end(),a[i].l)-V.begin()+1;
		a[i].r=lower_bound(V.begin(),V.end(),a[i].r)-V.begin()+1;
	}
	sort(a,a+m);
	for(reg int i=1;i<=n;++i){
		inv[i].first=lower_bound(V.begin(),V.end(),inv[i].first)-V.begin()+1;
		inv[i].second=lower_bound(V.begin(),V.end(),inv[i].second)-V.begin()+1;
	}
	reg int ans=1;
	for(reg int l=0,r;l<m;l=r+1){
		r=l;
		while(r+1<m&&a[r+1].w==a[l].w)
			++r;
		for(reg int i=l;i<=r;++i){
			SegmentTree::update(1,1,V.size(),a[i].l,a[i].r-1,a[i].c);
			ins[a[i].c]=true;
		}
		while(SegmentTree::unit[1].Max){
			reg int v=SegmentTree::unit[1].Max;
			vis[v]=true;
			++ans;
			SegmentTree::update(1,1,V.size(),inv[v].first,inv[v].second-1,0);
		}
	}
	printf("%d\n",ans);
	return 0;
}
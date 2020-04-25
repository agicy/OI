#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1000000+5;
const int MAXP=1000+5;

int n,m,B,p;

namespace Subtask1{
	namespace SegmentTree{
		#define lson ( (k) << 1 )
		#define rson ( (k) << 1 | 1 )
		#define mid ( ( (l) + (r) ) >> 1 )
		int Max[MAXN<<2],lMax[MAXN<<2],rMax[MAXN<<2],len[MAXN<<2];
		int tag[MAXN<<2];
		inline void pushup(reg int k){
			if(tag[k]){
				lMax[k]=rMax[k]=Max[k]=0;
				return;
			}
			if(len[k]==1){
				lMax[k]=rMax[k]=Max[k]=1;
				return;
			}
			if(lMax[lson]==len[lson])
				lMax[k]=lMax[lson]+lMax[rson];
			else
				lMax[k]=lMax[lson];
			if(rMax[rson]==len[rson])
				rMax[k]=rMax[rson]+rMax[lson];
			else
				rMax[k]=rMax[rson];
			Max[k]=max(rMax[lson]+lMax[rson],max(Max[lson],Max[rson]));
		}
		inline void Build(reg int k,reg int l,reg int r){
			Max[k]=lMax[k]=rMax[k]=len[k]=r-l+1;
			if(l==r)
				return;
			Build(lson,l,mid);
			Build(rson,mid+1,r);
			return;
		}
		inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
			if(L<=l&&r<=R){
				tag[k]+=val;
				pushup(k);
				return;
			}
			if(L<=mid)
				Update(lson,l,mid,L,R,val);
			if(R>mid)
				Update(rson,mid+1,r,L,R,val);
			pushup(k);
			return;
		}
		#undef mid
		#undef lson
		#undef rson
	}
	using namespace SegmentTree;
	struct Node{
		int l,r;
		inline Node(reg int l=0,reg int r=0):l(l),r(r){
			return;
		}
	};
	vector<Node> st[MAXN],ed[MAXN];
	inline void Solve(void){
		for(reg int i=1;i<=p;++i){
			static int x1,y1,x2,y2;
			x1=read(),y1=read(),x2=read(),y2=read(),read();
			st[x1].push_back(Node(y1,y2));
			ed[x2].push_back(Node(y1,y2));
		}
		Build(1,1,m);
		reg int j=0;
		int ans=0;
		for(reg int i=1;i<=n;++i){
			while(Max[1]>=j-i+1&&j<=n){
				++j;
				for(reg int k=0,size=st[j].size();k<size;++k)
					Update(1,1,m,st[j][k].l,st[j][k].r,1);
			}
			for(reg int j=0,size=ed[i].size();j<size;++j)
				Update(1,1,m,ed[i][j].l,ed[i][j].r,-1);
			ans=max(ans,j-i);
		}
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask2{
	struct Node{
		int x1,y1,x2,y2,c;
		inline void Read(void){
			x1=read(),y1=read(),x2=read(),y2=read(),c=read();
			return;
		}
	};
	struct Line{
		int l,r,w;
		inline Line(reg int l=0,reg int r=0,reg int w=0):l(l),r(r),w(w){
			return;
		}
	};
	namespace SegmentTree{
		#define lson ( (k) << 1 )
		#define rson ( (k) << 1 | 1 )
		#define mid ( ( (l) + (r) ) >> 1 )
		int Min[MAXN<<2],tag[MAXN<<2];
		inline void Build(reg int k,reg int l,reg int r){
			Min[k]=tag[k]=0;
			if(l==r)
				return;
			Build(lson,l,mid);
			Build(rson,mid+1,r);
			return;
		}
		inline void Add(reg int k,reg int val){
			Min[k]+=val;
			tag[k]+=val;
			return;
		}
		inline void pushdown(reg int k){
			if(tag[k]){
				Add(lson,tag[k]);
				Add(rson,tag[k]);
				tag[k]=0;
			}
			return;
		}
		inline void pushup(reg int k){
			Min[k]=min(Min[lson],Min[rson]);
			return;
		}
		inline void Update(reg int k,reg int l,reg int r,const Line& N){
			if(N.l<=l&&r<=N.r){
				Add(k,N.w);
				return;
			}
			pushdown(k);
			if(N.l<=mid)
				Update(lson,l,mid,N);
			if(N.r>mid)
				Update(rson,mid+1,r,N);
			pushup(k);
			return;
		}
		#undef lson
		#undef rson
		#undef mid
	}
	using namespace SegmentTree;
	Node a[MAXN];
	vector<Line> st[MAXN],ed[MAXN];
	inline bool check(reg int l){
		for(reg int i=1;i<=n-l+1;++i){
			st[i].clear();
			ed[i].clear();
		}
		Build(1,1,m-l+1);
		for(reg int i=1;i<=p;++i){
			static int x1,y1,x2,y2,c;
			x1=a[i].x1-l+1,y1=a[i].y1-l+1;
			x2=a[i].x2,y2=a[i].y2,c=a[i].c;
			x1=max(x1,1),y1=max(y1,1);
			x2=min(x2,n-l+1),y2=min(y2,m-l+1);
			if(x1>x2||y1>y2)
				continue;
			st[x1].push_back(Line(y1,y2,c));
			ed[x2].push_back(Line(y1,y2,-c));
		}
		for(reg int i=1;i<=n-l+1;++i){
			for(reg int j=0,size=st[i].size();j<size;++j)
				Update(1,1,m-l+1,st[i][j]);
			if(Min[1]<=B)
				return true;
			for(reg int j=0,size=ed[i].size();j<size;++j)
				Update(1,1,m-l+1,ed[i][j]);
		}
		return false;
	}
	inline void Solve(void){
		for(reg int i=1;i<=p;++i)
			a[i].Read();
		reg int l=1,r=min(n,m),mid;
		int ans=0;
		while(l<=r){
			mid=(l+r)>>1;
			if(check(mid))
				ans=mid,l=mid+1;
			else
				r=mid-1;
		}
		printf("%d\n",ans);
		return;
	}
}

int main(void){
	n=read(),m=read(),B=read(),p=read();
	if(!B)
		Subtask1::Solve();
	else
		Subtask2::Solve();
	return 0;
}

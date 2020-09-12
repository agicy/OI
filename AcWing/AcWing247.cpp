#include <bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e4+5;

struct Line{
	double x,y1,y2;
	int k;
	inline Line(reg double x=0,reg double y1=0,reg double y2=0,reg int k=0):x(x),y1(y1),y2(y2),k(k){
		return;
	}
	inline bool operator<(const Line& a)const{
		return x<a.x;
	}
};

int n;
Line L[MAXN*2];
vector<double> V;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int cnt;
		double len;
		#define cnt(x) unit[(x)].cnt
		#define len(x) unit[(x)].len
	};
	Node unit[MAXN<<3];
	inline void pushup(reg int k,reg int l,reg int r){
		if(cnt(k))
			len(k)=V[r+1]-V[l];
		else if(l!=r)
			len(k)=len(lson)+len(rson);
		else
			len(k)=0;
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pl,reg int pr,reg int val){
		if(pl<=l&&r<=pr){
			cnt(k)+=val;
			pushup(k,l,r);
			return;
		}
		if(pl<=mid)
			update(lson,l,mid,pl,pr,val);
		if(pr>mid)
			update(rson,mid+1,r,pl,pr,val);
		pushup(k,l,r);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

inline int getId(double x){
	return lower_bound(V.begin(),V.end(),x)-V.begin();
}

int main(void){
	reg int C=0;
	while(scanf("%d",&n)!=EOF&&n!=0){
		V.clear();
		reg int tot=0;
		for(reg int i=0;i<n;++i){
			static double x1,y1,x2,y2;
			scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
			L[tot++]=Line(x1,y1,y2,1);
			L[tot++]=Line(x2,y1,y2,-1);
			V.push_back(y1),V.push_back(y2);
		}
		sort(V.begin(),V.end());
		V.erase(unique(V.begin(),V.end()),V.end());
		reg int m=V.size()-2;
		sort(L,L+tot);
		reg double ans=0.0;
		for(reg int i=0;i<tot;++i){
			if(i>0)
				ans+=SegmentTree::unit[1].len*(L[i].x-L[i-1].x);
			SegmentTree::update(1,0,m,getId(L[i].y1),getId(L[i].y2)-1,L[i].k);
		}
		printf("Test case #%d\nTotal explored area: %.2lf\n\n",++C,ans);
	}
	return 0;
}
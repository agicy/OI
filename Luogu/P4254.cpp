#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=1000000+500;

int n;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	int tot,tag[MAXN<<2];
	struct Node{
		double k,b;
		inline Node(reg double k=0.0,reg double b=0.0):k(k),b(b){
			return;
		}
		inline double GetVal(reg int x){
			return k*(x-1)+b;
		}
	};
	Node L[MAXN<<2];
	inline void Update(reg int k,reg int l,reg int r,reg int id){
		if(l==r){
			if(L[id].GetVal(l)>L[tag[k]].GetVal(l))
				tag[k]=id;
			return;
		}
		reg int mid=(l+r)>>1;
		if(L[id].k>L[tag[k]].k)
			if(L[id].GetVal(mid)>L[tag[k]].GetVal(mid)){
				Update(lson,l,mid,tag[k]);
				tag[k]=id;
			}
			else
				Update(rson,mid+1,r,id);
		else
			if(L[id].GetVal(mid)>L[tag[k]].GetVal(mid)){
				Update(rson,mid+1,r,tag[k]);
				tag[k]=id;
			}
			else
				Update(lson,l,mid,id);
		return;
	}
	inline void Insert(reg double k,reg double b){
		L[++tot]=Node(k,b);
		Update(1,1,MAXN,tot);
		return;
	}
	inline double Query(reg int k,reg int l,reg int r,reg int x){
		if(l==r)
			return L[tag[k]].GetVal(l);
		double res=L[tag[k]].GetVal(x);
		reg int mid=(l+r)>>1;
		if(x<=mid)
			res=max(res,Query(lson,l,mid,x));
		else
			res=max(res,Query(rson,mid+1,r,x));
		return res;
	}
};

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		static char opt[16];
		static int t;
		static double s,p;
		scanf("%s",opt);
		switch(opt[0]){
			case 'P':{
				scanf("%lf%lf",&p,&s);
				SegmentTree::Insert(s,p);
				break;
			}
			case 'Q':{
				scanf("%d",&t);
				double ans=SegmentTree::Query(1,1,MAXN,t);
				printf("%d\n",(int)ans/100);
				break;
			}
			default:break;
		}
	}
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
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

const int MAXN=100000+5;

struct Node{
	int x,y;
	inline void Read(void){
		x=read(),y=read();
		return;
	}
	inline bool operator<(const Node &a)const{
		return y==a.y?x<a.x:y>a.y;
	}
};

struct SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int val;
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k].val=unit[lson].val+unit[rson].val;
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			unit[k].val+=val;
			return;
		}
		if(pos<=mid)
			Update(lson,l,mid,pos,val);
		if(pos>mid)
			Update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			return unit[k].val;
		}
		reg int res=0;
		if(L<=mid)
			res+=Query(lson,l,mid,L,R);
		if(R>mid)
			res+=Query(rson,mid+1,r,L,R);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
};

int n;
int up[MAXN],down[MAXN];
Node P[MAXN];
SegmentTree T;
vector<int> V;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		P[i].Read();
		V.push_back(P[i].x);
		up[i]=-INF;
		down[i]=INF;
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	sort(P+1,P+n+1);
	for(reg int i=1;i<=n;++i){
		P[i].x=lower_bound(V.begin(),V.end(),P[i].x)-V.begin()+1;
		up[P[i].x]=max(P[i].y,up[P[i].x]);
		down[P[i].x]=min(P[i].y,down[P[i].x]);
	}
	reg int lptr=P[1].x;
	P[n+1].y=INF;
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		if(P[i].y==up[P[i].x])
			T.Update(1,1,V.size(),P[i].x,1);
		if(P[i].y==down[P[i].x]){
			++ans;
			T.Update(1,1,V.size(),P[i].x,-1);
		}
		if(P[i].y!=P[i+1].y){
			ans+=T.Query(1,1,V.size(),lptr,P[i].x);
			lptr=P[i+1].x;
		}
	}
	printf("%d\n",ans);
	return 0;
}

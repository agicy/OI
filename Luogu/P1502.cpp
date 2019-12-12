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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=50000+5;

struct Node{
	int x,y1,y2,val;
	inline Node(void){
		x=y1=y2=val=0;
		return;
	}
	inline Node(reg int a,reg int b,reg int c,reg int d){
		x=a,y1=b,y2=c,val=d;
		return;
	}
	inline bool operator<(const Node& a)const{
		return x==a.x?val<a.val:x<a.x;
	}
};

struct SegmentTree{
	#define lson (k<<1)
	#define rson (k<<1|1)
	#define mid ((l+r)>>1)
	struct Node{
		int val,tag;
		inline Node(void){
			val=tag=0;
			return;
		}
		inline Node(reg int a,reg int b){
			val=a,tag=b;
			return;
		}
	};
	Node unit[MAXN<<4];
	inline void pushup(reg int k){
		unit[k].val=max(unit[lson].val,unit[rson].val);
		return;
	}
	inline void Add(reg int k,reg int val){
		unit[k].val+=val;
		unit[k].tag+=val;
		return;
	}
	inline void pushdown(reg int k){
		if(unit[k].tag){
			Add(lson,unit[k].tag);
			Add(rson,unit[k].tag);
			unit[k].tag=0;
		}
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			Add(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			Update(lson,l,mid,L,R,val);
		if(R>mid)
			Update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].val;
		pushdown(k);
		int res=0;
		if(L<=mid)
			res=max(res,Query(lson,l,mid,L,R));
		if(R>mid)
			res=max(res,Query(rson,mid+1,r,L,R));
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
};

int n,W,H;
int x[MAXN],y[MAXN],l[MAXN];
int cnt;
Node a[MAXN<<1];
SegmentTree T;
vector<int> Vx,Vy;

inline void Init(void);
inline void Read(void);
inline void Work(void);

int main(void){
	int T=read();
	while(T--){
		Init();
		Read();
		Work();
	}
	return 0;
}

inline void Init(void){
	cnt=0;
	Vx.clear(),Vy.clear();
	return;
}

inline void Read(void){
	n=read(),W=read(),H=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read(),y[i]=read(),l[i]=read();
	return;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i){
		Vx.push_back(x[i]);
		Vx.push_back(x[i]-W+1);
		Vy.push_back(y[i]);
		Vy.push_back(y[i]-H+1);
	}
	sort(Vx.begin(),Vx.end());
	sort(Vy.begin(),Vy.end());
	Vx.erase(unique(Vx.begin(),Vx.end()),Vx.end());
	Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
	reg int size=Vy.size()+1;
	for(reg int i=1;i<=n;++i){
		static int tx1,tx2,ty1,ty2;
		tx1=lower_bound(Vx.begin(),Vx.end(),x[i]-W+1)-Vx.begin()+1,
		tx2=lower_bound(Vx.begin(),Vx.end(),x[i])-Vx.begin()+1,
		ty1=lower_bound(Vy.begin(),Vy.end(),y[i]-H+1)-Vy.begin()+1,
		ty2=lower_bound(Vy.begin(),Vy.end(),y[i])-Vy.begin()+1,
		a[++cnt]=Node(tx1,ty1,ty2,l[i]),
		a[++cnt]=Node(tx2+1,ty1,ty2,-l[i]);
	}
	reg int ans=0;
	sort(a+1,a+cnt+1);
	for(reg int i=1;i<=cnt;++i){
		T.Update(1,1,size,a[i].y1,a[i].y2,a[i].val);
		ans=max((int)ans,T.Query(1,1,size,1,size));
	}
	printf("%d\n",ans);
	return;
}

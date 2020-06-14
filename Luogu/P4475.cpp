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

const int MAXN=500000+5;

int n,m;

struct Point{
	int x[2],val;
	inline void Read(void){
		x[0]=read(),x[1]=read(),val=read();
		return;
	}
};

Point p[MAXN];

namespace kD_Tree{
	#define mid ( ( (l) + (r) ) >> 1 )
	#define cMax(x,y) ( (x) < (y) ? ( (x) = (y) ) : 0 )
	#define cMin(x,y) ( (x) > (y) ? ( (x) = (y) ) : 0 )
	struct Node{
		int lson,rson;
		ll sum;
		int Max[2],Min[2];
		Point val;
	};
	int root;
	int tot;
	Node T[MAXN];
	int WD;
	inline bool cmp(const Point& a,const Point& b){
		return a.x[WD]<b.x[WD];
	}
	inline void pushup(reg int k){
		reg int l=T[k].lson,r=T[k].rson;
		if(l){
			cMin(T[k].Min[0],T[l].Min[0]),
			cMin(T[k].Min[1],T[l].Min[1]),
			cMax(T[k].Max[0],T[l].Max[0]),
			cMax(T[k].Max[1],T[l].Max[1]);
		}
		if(r){
			cMin(T[k].Min[0],T[r].Min[0]),
			cMin(T[k].Min[1],T[r].Min[1]),
			cMax(T[k].Max[0],T[r].Max[0]),
			cMax(T[k].Max[1],T[r].Max[1]);
		}
		T[k].sum=T[l].sum+T[r].sum+T[k].val.val;
		return;
	}
	inline int Build(reg int l,reg int r,reg int wd){
		if(l>r)
			return 0;
		reg int k=++tot;
		WD=wd;
		nth_element(p+l,p+mid,p+r+1,cmp);
		T[k].val=p[mid];
		T[k].Max[0]=T[k].Min[0]=T[k].val.x[0];
		T[k].Max[1]=T[k].Min[1]=T[k].val.x[1];
		T[k].lson=Build(l,mid-1,wd^1);
		T[k].rson=Build(mid+1,r,wd^1);
		pushup(k);
		return k;
	}
	ll a,b,c;
	inline bool check(reg ll x,reg ll y){
		return x*a+y*b<c;
	}
	inline ll Query(reg int k){
		reg int chk=check(T[k].Max[0],T[k].Max[1])+check(T[k].Min[0],T[k].Max[1])+check(T[k].Max[0],T[k].Min[1])+check(T[k].Min[0],T[k].Min[1]);
		if(chk==4)
			return T[k].sum;
		else if(chk==0)
			return 0; 
		reg ll res=0;
		if(check(T[k].val.x[0],T[k].val.x[1]))
			res+=T[k].val.val;
		if(T[k].lson)
			res+=Query(T[k].lson);
		if(T[k].rson)
			res+=Query(T[k].rson);
		return res;
	}
	#undef mid
	#undef cMax
	#undef cMin
}

using namespace kD_Tree;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		p[i].Read();
	root=Build(1,n,0);
	while(m--){
		a=read(),b=read(),c=read();
		printf("%lld\n",Query(root));
	}
	return 0;
}
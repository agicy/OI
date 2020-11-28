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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=5e4+5;
const int MAXM=1.5e5+5;
const int MAXX=1e5+5;
const int X=1e5;
const double inf=1e20;

int n,m;

struct Line{
	double k,b;
	inline Line(reg double k=0,reg double b=0):k(k),b(b){
		return;
	}
	inline double getVal(reg double x){
		return k*x+b;
	}
};

int tot;
Line L[MAXN+MAXM];
double Max[MAXX];

inline double calc(reg int id,reg int x){
	return L[id].getVal(x);
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int id;
		#define id(x) unit[(x)].id
	};
	Node unit[MAXX<<2];
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int Id){
		if(L<=l&&r<=R){
			if(!id(k)){
				id(k)=Id;
				return;
			}
			reg double lval=calc(id(k),l),rval=calc(id(k),r);
			reg double plval=calc(Id,l),prval=calc(Id,r);
			if(lval>=plval&&rval>=prval)
				return;
			if(lval<=plval&&rval<=prval){
				id(k)=Id;
				return;
			}
		}
		if(L<=mid)
			update(lson,l,mid,L,R,Id);
		if(R>mid)
			update(rson,mid+1,r,L,R,Id);
		return;
	}
	inline void query(reg int k,reg int l,reg int r,reg int pos,reg double& res){
		if(id(k))
			res=max(res,calc(id(k),pos));
		if(l==r)
			return;
		if(pos<=mid)
			query(lson,l,mid,pos,res);
		else
			query(rson,mid+1,r,pos,res);
		return;
	}
}

inline void insert(int x1,double y1,int x2,double y2){
	if(x1==x2){
		if(1<=x1&&x1<=X)
			Max[x1]=max(Max[x1],max(y1,y2));
	}
	else{
		reg double k=(y2-y1)/(x2-x1);
		L[++tot]=Line(k,y1-x1*k);
		if(x1>x2)
			swap(x1,x2);
		reg int l=max(1,x1),r=min(X,x2);
		if(l<=r)
			SegmentTree::update(1,1,X,l,r,tot);
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=X;++i)
		Max[i]=-inf;
	for(reg int i=1;i<=n;++i){
		static int x1,y1,x2,y2;
		x1=read(),y1=read(),x2=read(),y2=read();
		insert(x1,y1,x2,y2);
	}
	for(reg int i=1;i<=m;++i){
		static int opt,x1,y1,x2,y2;
		opt=read();
		switch(opt){
			case 0:{
				x1=read(),y1=read(),x2=read(),y2=read();
				insert(x1,y1,x2,y2);
				break;
			}
			case 1:{
				x1=read();
				double res=Max[x1];
				SegmentTree::query(1,1,X,x1,res);
				if(res==-inf)
					puts("0");
				else
					printf("%.5lf\n",res);
				break;
			}
		}
	}
	return 0;
}
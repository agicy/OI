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

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=2e5+5;

int n;

namespace kD_Tree{
	const double alpha=0.75;
	struct Point{
		int x[2];
		int w;
		inline Point(void){
			x[0]=x[1]=w=0;
			return;
		}
		inline Point(reg int a,reg int b,reg int c){
			x[0]=a,x[1]=b,w=c;
			return;
		}
	};

	int WD,tot;
	Point p[MAXN];

	int rt;
	int top,S[MAXN];
	struct Node{
		int lson,rson;
		int Max[2],Min[2];
		int sum,siz;
		Point val;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define Max(x) unit[(x)].Max
		#define Min(x) unit[(x)].Min
		#define sum(x) unit[(x)].sum
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
	};
	Node unit[MAXN];
	inline bool operator<(const Point& a,const Point& b){
		return a.x[WD]<b.x[WD];
	}
	inline int NewNode(void){
		return top?S[top--]:++tot;
	}
	inline void pushup(reg int k){
		reg int l=lson(k),r=rson(k);
		sum(k)=sum(l)+sum(r)+val(k).w;
		siz(k)=siz(l)+siz(r)+1;
		Max(k)[0]=Min(k)[0]=val(k).x[0];
		Max(k)[1]=Min(k)[1]=val(k).x[1];
		if(l){
			cMax(Max(k)[0],Max(l)[0]),cMax(Max(k)[1],Max(l)[1]);
			cMin(Min(k)[0],Min(l)[0]),cMin(Min(k)[1],Min(l)[1]);
		}
		if(r){
			cMax(Max(k)[0],Max(r)[0]),cMax(Max(k)[1],Max(r)[1]);
			cMin(Min(k)[0],Min(r)[0]),cMin(Min(k)[1],Min(r)[1]);
		}
		return;
	}
	inline int build(reg int l,reg int r,reg int wd){
		if(l>r)
			return 0;
		reg int mid=(l+r)>>1;
		reg int k=NewNode();
		WD=wd;
		nth_element(p+l,p+mid,p+r+1);
		val(k)=p[mid];
		lson(k)=build(l,mid-1,wd^1);
		rson(k)=build(mid+1,r,wd^1);
		pushup(k);
		return k;
	}
	inline void reBuild(reg int k,reg int num){
		if(lson(k))
			reBuild(lson(k),num);
		p[siz(lson(k))+num+1]=val(k);
		S[++top]=k;
		if(rson(k))
			reBuild(rson(k),num+siz(lson(k))+1);
		return;
	}
	inline void check(reg int &k,reg int wd){
		if(siz(k)*alpha<max(siz(lson(k)),siz(rson(k)))){
			reBuild(k,0);
			k=build(1,siz(k),wd);
		}
		return;
	}
	inline void insert(reg int &k,const Point& P,reg int wd){
		if(!k){
			k=NewNode();
			lson(k)=rson(k)=0;
			val(k)=P;
			pushup(k);
			return;
		}
		if(P.x[wd]<=val(k).x[wd])
			insert(lson(k),P,wd^1);
		else
			insert(rson(k),P,wd^1);
		pushup(k);
		check(k,wd);
		return;
	}
	inline bool in(reg int k,reg int x0,reg int y0,reg int x1,reg int y1){
		return x0<=Min(k)[0]&&Max(k)[0]<=x1&&y0<=Min(k)[1]&&Max(k)[1]<=y1;
	}
	inline bool check(reg int k,reg int x0,reg int y0,reg int x1,reg int y1){
		return x0<=val(k).x[0]&&val(k).x[0]<=x1&&y0<=val(k).x[1]&&val(k).x[1]<=y1;
	}
	inline bool out(reg int k,reg int x0,reg int y0,reg int x1,reg int y1){
		return Max(k)[0]<x0||Min(k)[0]>x1||Max(k)[1]<y0||Min(k)[1]>y1;
	}
	inline int query(reg int k,reg int x0,reg int y0,reg int x1,reg int y1){
		if(!k)
			return 0;
		reg int res=0;
		if(in(k,x0,y0,x1,y1))
			return sum(k);
		if(out(k,x0,y0,x1,y1))
			return 0;
		if(check(k,x0,y0,x1,y1))
			res+=val(k).w;
		res+=query(lson(k),x0,y0,x1,y1)+query(rson(k),x0,y0,x1,y1);
		return res;
	}
}

using namespace kD_Tree;

int main(void){
	read();
	n=read();
	while(n--){
		static int opt,x,y,w,x1,y1,x2,y2;
		opt=read();
		switch(opt){
			case 1:{
				x=read(),y=read(),w=read();
				insert(rt,Point(x,y,w),0);
				break;
			}
			case 2:{
				x1=read(),y1=read(),x2=read(),y2=read();
				reg int ans=query(rt,x1,y1,x2,y2);
				printf("%d\n",ans);
				break;
			}
		}
	}
	return 0;
}
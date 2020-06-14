#include<bits/stdc++.h>
using namespace std;
#define reg register
#define eps 1e-6
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

long double sina,cosa;

inline long double sqr(reg long double x){
	return x*x;
}

const int MAXN=300000+5;

int n,ans[MAXN];

namespace kD_Tree{
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Point{
		long double x[2],r;
		int id;
		inline void Read(reg int i){
			static double X,Y;
			id=i;
			X=read(),Y=read();
			x[0]=X*cosa-Y*sina;
			x[1]=X*sina+Y*cosa;
			r=read();
			return;
		}
		inline bool operator<(const Point& a)const{
			return r==a.r?id<a.id:r>a.r;
		}
	};
	int root,tot;
	int lson[MAXN],rson[MAXN];
	long double Min[MAXN][2],Max[MAXN][2];
	Point p[MAXN],val[MAXN];
	int WD;
	inline bool cmp(const Point& a,const Point& b){
		return a.x[WD]<b.x[WD];
	}
	inline void pushup(reg int k){
		reg long double x=val[k].x[0],y=val[k].x[1],R=val[k].r;
		Min[k][0]=x-R;Max[k][0]=x+R;
		Min[k][1]=y-R;Max[k][1]=y+R;
		reg int l=lson[k],r=rson[k];
		if(l){
			Min[k][0]=min(Min[k][0],Min[l][0]);
			Max[k][0]=max(Max[k][0],Max[l][0]);
			Min[k][1]=min(Min[k][1],Min[l][1]);
			Max[k][1]=max(Max[k][1],Max[l][1]);
		}
		if(r){
			Min[k][0]=min(Min[k][0],Min[r][0]);
			Max[k][0]=max(Max[k][0],Max[r][0]);
			Min[k][1]=min(Min[k][1],Min[r][1]);
			Max[k][1]=max(Max[k][1],Max[r][1]);
		}
		return;
	}
	inline int Build(reg int l,reg int r,reg int wd){
		if(l>r)
			return 0;
		reg int k=++tot;
		WD=wd;
		nth_element(p+l,p+mid,p+r+1,cmp);
		val[k]=p[mid];
		lson[k]=Build(l,mid-1,wd^1);
		rson[k]=Build(mid+1,r,wd^1);
		pushup(k);
		return k;
	}
	inline bool check(reg int k,const Point& a){
		return sqr(a.r+val[k].r)-(sqr(a.x[0]-val[k].x[0])+sqr(a.x[1]-val[k].x[1]))>=-eps;
	}
	inline bool far(reg int k,reg const Point& a){
		return (a.x[0]+a.r<Min[k][0])||(a.x[0]-a.r>Max[k][0])||(a.x[1]+a.r<Min[k][1])||(a.x[1]-a.r>Max[k][1]);
	}
	inline void Query(reg int k,reg const Point& a){
		if(far(k,a))
			return;
		if(!ans[val[k].id]&&check(k,a))
			ans[val[k].id]=a.id;
		if(lson[k])
			Query(lson[k],a);
		if(rson[k])
			Query(rson[k],a);
		return;
	}
}

using namespace kD_Tree;

int main(void){
	n=read();
	srand(time(0));
	sina=sin((long double)rand()),cosa=sqrt(1-sina*sina);
	for(reg int i=1;i<=n;++i)
		p[i].Read(i);
	root=Build(1,n,0);
	sort(p+1,p+n+1);
	for(reg int i=1;i<=n;++i)
		if(!ans[p[i].id])	
			Query(root,p[i]);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXM=1e5+5;
const int MAXQ=2e5+5;

struct Vector{
	int x,y;
	inline Vector(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
};

inline int dot(const Vector& a,const Vector& b){
	return a.x*b.x+a.y*b.y;
}

inline int cross(const Vector& a,const Vector& b){
	return a.x*b.y-a.y*b.x;
}

typedef Vector Point;

inline bool operator<(const Point& a,const Point& b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}

inline bool check(const Point& a,const Point& b,const Point& c){
	return cross(b-a,c-a)>0;
}

inline double getDis(const Point& a,const Point& b){
	return sqrt(dot(a-b,a-b));
}

namespace FHQTreap{
	const int MAXSIZE=MAXM;
	struct Node{
		int ch[2];
		int siz;
		int pre,suf;
		double len;
		Point poi;
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define pre(x) unit[(x)].pre
		#define suf(x) unit[(x)].suf
		#define len(x) unit[(x)].len
		#define poi(x) unit[(x)].poi
		#define lson(x) ch(x)[0]
		#define rson(x) ch(x)[1]
	};
	int tot;
	Node unit[MAXSIZE];
	inline int New(const Point& v){
		reg int p=++tot;
		lson(p)=rson(p)=0;
		siz(p)=1;
		pre(p)=suf(p)=p;
		poi(p)=v;
		len(p)=0;
		return p;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		if(lson(p))
			pre(p)=pre(lson(p));
		else
			pre(p)=p;
		if(rson(p))
			suf(p)=suf(rson(p));
		else
			suf(p)=p;
		len(p)=len(lson(p))+len(rson(p));
		if(lson(p))
			len(p)+=getDis(poi(suf(lson(p))),poi(p));
		if(rson(p))
			len(p)+=getDis(poi(pre(rson(p))),poi(p));
		return;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		if(rand()%(siz(x)+siz(y))<siz(x)){
			rson(x)=merge(rson(x),y);
			pushup(x);
			return x;
		}
		else{
			lson(y)=merge(x,lson(y));
			pushup(y);
			return y;
		}
	}
	inline void split_v(reg int p,reg int v,reg int &x,reg int &y){
		if(!p){
			x=y=0;
			return;
		}
		if(poi(p)<poi(v)){
			x=p;
			split_v(rson(x),v,rson(x),y);
			pushup(x);
		}
		else{
			y=p;
			split_v(lson(y),v,x,lson(y));
			pushup(y);
		}
		return;
	}
	inline void split_s(reg int p,reg int k,reg int &x,reg int &y){
		if(!p){
			x=y=0;
			return;
		}
		if(siz(lson(p))<k){
			x=p;
			split_s(rson(x),k-siz(lson(p))-1,rson(x),y);
			pushup(x);
		}
		else{
			y=p;
			split_s(lson(y),k,x,lson(y));
			pushup(y);
		}
		return;
	}
}

struct querys{
	int opt,x;
};

int n,x,y,m,q;
bool vis[MAXM];
double ans[MAXQ];
Point a[MAXM];
int rt;
querys Q[MAXQ];

inline void build(reg int l,reg int r,reg Point val[]){
	using namespace FHQTreap;
	sort(val+l,val+r+1);
	reg int top=0;
	static int S[MAXM];
	for(reg int i=l;i<=r;++i){
		while(top>1&&check(val[S[top-1]],val[S[top]],val[i]))
			--top;
		S[++top]=i;
	}
	for(reg int i=1;i<=top;++i)
		rt=merge(rt,New(val[S[i]]));
	return;
}

inline void insert(reg int id){
	using namespace FHQTreap;
	static int x,y;
	split_v(rt,id,x,y);
	if(check(poi(suf(x)),poi(id),poi(pre(y)))){
		rt=merge(x,y);
		return;
	}
	while(siz(x)>1){
		static int x1,x2;
		split_s(x,siz(x)-1,x1,x2);
		if(check(poi(suf(x1)),poi(x2),poi(id)))
			x=x1;
		else{
			x=merge(x1,x2);
			break;
		}
	}
	while(siz(y)>1){
		static int y1,y2;
		split_s(y,1,y1,y2);
		if(check(poi(id),poi(y1),poi(pre(y2))))
			y=y2;
		else{
			y=merge(y1,y2);
			break;
		}
	}
	rt=merge(merge(x,id),y);
	return;
}

int main(void){
	n=read(),x=read(),y=read(),m=read();
	a[m+1]=Point(0,0),a[m+2]=Point(n,0),a[m+3]=Point(x,y);
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		a[i]=Point(x,y);
	}
	q=read();
	for(reg int i=1;i<=q;++i){
		Q[i].opt=read();
		if(Q[i].opt==1)
			Q[i].x=read(),vis[Q[i].x]=true;
	}
	reg int cnt=0;
	static Point val[MAXM];
	for(reg int i=1;i<=m+3;++i)
		if(!vis[i])
			val[++cnt]=a[i];
	build(1,cnt,val);
	reg int tot=0;
	for(reg int i=q;i>=1;--i)
		if(Q[i].opt==1)
			insert(FHQTreap::New(a[Q[i].x]));
		else
			ans[++tot]=FHQTreap::len(rt);
	for(reg int i=tot;i>=1;--i)
		printf("%.2lf\n",ans[i]);
	return 0;
}
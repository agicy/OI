#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline ll readll(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(const char* s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

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

inline ll dot(const Vector& a,const Vector& b){
	return 1ll*a.x*b.x+1ll*a.y*b.y;
}

inline ll cross(const Vector& a,const Vector& b){
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}

typedef Vector Point;

inline bool operator<(const Point& a,const Point& b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}

const int MAXN=1e5+5;
const int MAXQ=1e5+5;
const ll inf=5e18;

struct updates{
	int tim;
	Point p;
};

struct querys{
	int tim;
	int A,B;
	ll C;
	ll Max,Min;
};

int n,q;
int totu,totq;
updates up[MAXN+MAXQ];
querys qu[MAXQ];

inline ll getVal(const querys& q,const Point& p){
	return 1ll*q.A*p.x+1ll*q.B*p.y-q.C;
}

inline void solve(reg int l,reg int r,reg int lu,reg int ru,reg int lq,reg int rq){
	if(l==r)
		return;
	if(lu>ru||lq>rq)
		return;
	reg int mid=(l+r)>>1;
	reg int midu,midq;
	if(up[lu].tim<=mid){
		reg int __l=lu,__r=ru,__mid;
		while(__l<__r){
			__mid=(__l+__r)>>1;
			if(up[__mid+1].tim<=mid)
				__l=__mid+1;
			else
				__r=__mid;
		}
		midu=__l;
	}
	else
		midu=lu-1;
	if(qu[lq].tim<=mid){
		reg int __l=lq,__r=rq,__mid;
		while(__l<__r){
			__mid=(__l+__r)>>1;
			if(qu[__mid+1].tim<=mid)
				__l=__mid+1;
			else
				__r=__mid;
		}
		midq=__l;
	}
	else
		midq=lq-1;
	solve(l,mid,lu,midu,lq,midq);
	if(lu<=midu&&midq+1<=rq){
		reg int tot=0;
		static Point tmp[MAXN+MAXQ];
		for(reg int i=lu;i<=midu;++i)
			tmp[++tot]=up[i].p;
		sort(tmp+1,tmp+tot+1);
		reg int top;
		static Point S[MAXN+MAXQ];
		top=0;
		for(reg int i=1;i<=tot;++i){
			while(top>1&&cross(S[top]-S[top-1],tmp[i]-S[top-1])>=0)
				--top;
			S[++top]=tmp[i];
		}
		for(reg int i=midq+1;i<=rq;++i)
			if(qu[i].Max<=0){
				reg int __l=1,__r=top,__mid;
				while(__l<__r){
					__mid=(__l+__r)>>1;
					if(getVal(qu[i],S[__mid])<getVal(qu[i],S[__mid+1]))
						__l=__mid+1;
					else
						__r=__mid;
				}
				qu[i].Max=max(qu[i].Max,getVal(qu[i],S[__l]));
			}
		top=0;
		for(reg int i=1;i<=tot;++i){
			while(top>1&&cross(S[top]-S[top-1],tmp[i]-S[top-1])<=0)
				--top;
			S[++top]=tmp[i];
		}
		for(reg int i=midq+1;i<=rq;++i)
			if(qu[i].Min>=0){
				reg int __l=1,__r=top,__mid;
				while(__l<__r){
					__mid=(__l+__r)>>1;
					if(getVal(qu[i],S[__mid])>getVal(qu[i],S[__mid+1]))
						__l=__mid+1;
					else
						__r=__mid;
				}
				qu[i].Min=min(qu[i].Min,getVal(qu[i],S[__l]));
			}
	}
	solve(mid+1,r,midu+1,ru,midq+1,rq);
	return;
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i){
		++totu;
		up[totu].tim=0,up[totu].p.x=read(),up[totu].p.y=read();
	}
	for(reg int i=1;i<=q;++i){
		static int opt;
		opt=read();
		switch(opt){
			case 1:{
				++totu;
				up[totu].tim=i,up[totu].p.x=read(),up[totu].p.y=read();
				break;
			}
			case 2:{
				++totq;
				qu[totq].tim=i,qu[totq].A=read(),qu[totq].B=read(),qu[totq].C=readll(),qu[totq].Max=-inf,qu[totq].Min=inf;
				if(qu[totq].B<0)
					qu[totq].A=-qu[totq].A,qu[totq].B=-qu[totq].B,qu[totq].C=-qu[totq].C;
				else if((!qu[totq].B)&&qu[totq].A<0)
					qu[totq].A=-qu[totq].A,qu[totq].C=-qu[totq].C;
				break;
			}
		}
	}
	solve(0,q,1,totu,1,totq);
	for(reg int i=1;i<=totq;++i)
		writeln((!qu[i].Max||!qu[i].Min||((qu[i].Max^qu[i].Min)>>63))?"NO":"YES");
	flush();
	return 0;
}
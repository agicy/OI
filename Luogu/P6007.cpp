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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXP=1e5+5;
const int MAXV=2*MAXP;

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int unit[MAXV];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]=min(unit[i],val);
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res=min(res,unit[i]);
		return res;
	}
}

struct Node{
	int id,x,y,pos;
	inline bool operator<(const Node& a)const{
		return x<a.x||(x==a.x&&y<a.y);
	}
};

inline bool cmp(const Node& a,const Node& b){
	return a.y<b.y;
}

int n,p;
int u[MAXP],v[MAXP];
Node a[MAXP<<1];
int Min[MAXV];

int main(void){
	n=read(),p=read();
	for(reg int i=1;i<=p;++i){
		a[i].x=read(),a[i].y=read();
		a[i+p].x=read(),a[i+p].y=read();
		a[i].id=i,a[i+p].id=i;
	}
	sort(a+1,a+2*p+1,cmp);
	a[0].y=-1;
	for(reg int i=1;i<=2*p;++i)
		a[i].pos=a[i-1].pos+(a[i-1].y!=a[i].y);
	sort(a+1,a+2*p+1);
	for(reg int i=1;i<=2*p;++i)
		if(u[a[i].id])
			v[a[i].id]=i;
		else
			u[a[i].id]=i;
	reg int ans=0;
	BIT::Init(2*p);
	for(reg int i=1;i<=2*p;++i){
		Min[i]=min(Min[i],BIT::query(a[i].pos));
		if(u[a[i].id]==i)
			Min[v[a[i].id]]=min(Min[v[a[i].id]],Min[i]+a[i].x+a[i].y-a[v[a[i].id]].x-a[v[a[i].id]].y);
		BIT::update(a[i].pos,Min[i]);
		ans=min(ans,Min[i]);
	}
	printf("%d\n",2*n+ans);
	return 0;
}
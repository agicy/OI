#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef double db;
#define eps 1e-12
#define INF 1e32
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=5000000+5;

struct Node{
	ll x,r;
	int v;
	inline void Read(void){
		x=read(),r=read(),v=read();
		return;
	}
};

int n;
ll m;
db dp[MAXN],ans;
Node a[MAXN];

struct SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1)
	struct Node{
		int son[2];
		db k,b;
	};
	int tot;
	Node unit[MAXN];
	inline db f(reg db x,reg db kk,reg db bb){
		return kk*x+bb;
	}
	inline void Query(reg ll l,reg ll r,reg int x,reg int y){
		if(x==0)
			return;
		dp[y]=min(dp[y],f(a[y].x,unit[x].k,unit[x].b));
		if(a[y].x<=mid)
			Query(l,mid,unit[x].son[0],y);
		else
			Query(mid+1,r,unit[x].son[1],y);
		return;
	}
	inline void Add(reg ll l,reg ll r,reg int x,db& k,db& b){
		if(x==0){
			++tot;
			unit[tot].k=k;
			unit[tot].b=b;
			return;
		}
		reg bool fl=(f(l,k,b)-f(l,unit[x].k,unit[x].b)>eps);
		reg bool fr=(f(r,k,b)-f(r,unit[x].k,unit[x].b)>eps);
		reg bool fm=(f(mid,k,b)-f(mid,unit[x].k,unit[x].b)>eps);
		if((fl)&&(fr)&&(fm))
			return;
		if((!fl)&&(!fr)&&(!fm)){
			unit[x].k=k;
			unit[x].b=b;
			return;
		}
		reg bool s=(fm^fr);
		if(!fm){
			swap(unit[x].k,k);
			swap(unit[x].b,b);
		}
		if(s)
			Add(mid+1,r,unit[x].son[s],k,b);
		else
			Add(l,mid,unit[x].son[s],k,b);
		if(!unit[x].son[s])
			unit[x].son[s]=tot;
		return;
	}
	#undef mid
};

SegmentTree T;

int main(void){
	n=read(),m=read();
	a[1].x=read(),a[1].r=read(),a[1].v=read();
	for(reg int i=2;i<=n;++i)
		a[i].x=read(),a[i].r=read(),a[i].v=read();
	T.unit[1].k=1/(sqrt((db)a[1].r)*2);
	T.unit[1].b=(db)(-a[1].x)/(sqrt((db)a[1].r)*2)+a[1].v;
	dp[1]=a[1].v;
	T.tot=1;
	for(reg int i=2;i<=n;++i){
		dp[i]=INF;
		T.Query(a[1].x,a[n].x,1,i);
		dp[i]+=a[i].v;
		db k=1/(sqrt((db)a[i].r)*2);
		db b=(db)(-a[i].x)/(sqrt((db)a[i].r)*2)+dp[i];
		T.Add(a[1].x,a[n].x,1,k,b);
	}
	ans=INF;
	for(reg int i=1;i<=n;++i)
		if(a[i].x+a[i].r>=m)
			ans=min(ans,dp[i]);
	printf("%.3lf\n",ans);
	return 0;
}

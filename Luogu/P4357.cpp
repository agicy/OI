#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X7F7F7F7F7F7F7F7F
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

inline ll sqr(reg ll x){
	return x*x;
}

const int MAXN=100000+5;

namespace KD_Tree{
	#define mid ( ( (l) + (r) ) >> 1 )
	priority_queue<ll,vector<ll>,greater<ll>/**/> Q;
	struct Point{
		int x[2];
		inline void Read(void){
			x[0]=read(),x[1]=read();
			return;
		}
	};
	int WD;
	inline bool cmp(const Point& a,const Point& b){
		return a.x[WD]<b.x[WD];
	}
	Point p[MAXN];
	int tot,root;
	int Max[MAXN][2],Min[MAXN][2];
	int lson[MAXN],rson[MAXN];
	Point val[MAXN];
	inline void pushup(reg int k){
		reg int l=lson[k],r=rson[k];
		if(l){
			Min[k][0]=min(Min[k][0],Min[l][0]);
			Min[k][1]=min(Min[k][1],Min[l][1]);
			Max[k][0]=max(Max[k][0],Max[l][0]);
			Max[k][1]=max(Max[k][1],Max[l][1]);
		}
		if(r){
			Min[k][0]=min(Min[k][0],Min[r][0]);
			Min[k][1]=min(Min[k][1],Min[r][1]);
			Max[k][0]=max(Max[k][0],Max[r][0]);
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
		Min[k][0]=Max[k][0]=val[k].x[0];
		Min[k][1]=Max[k][1]=val[k].x[1];
		lson[k]=Build(l,mid-1,wd^1);
		rson[k]=Build(mid+1,r,wd^1);
		pushup(k);
		return k;
	}
	inline ll dis(reg int k,const Point& p){
		return sqr(val[k].x[0]-p.x[0])+sqr(val[k].x[1]-p.x[1]);
	}
	inline ll MaxDis(reg int k,const Point& p){
		return max(sqr(Min[k][0]-p.x[0]),sqr(Max[k][0]-p.x[0]))+max(sqr(Min[k][1]-p.x[1]),sqr(Max[k][1]-p.x[1]));
	}
	inline void Query(reg int k,const Point& p){
		static ll N;
		N=dis(k,p);
		if(N>Q.top()){
			Q.pop();
			Q.push(N);
		}
		reg ll dl=-INF,dr=-INF;
		if(lson[k])
			dl=MaxDis(lson[k],p);
		if(rson[k])
			dr=MaxDis(rson[k],p);
		if(dl>dr){
			if(dl>=Q.top())
				Query(lson[k],p);
			if(dr>=Q.top())
				Query(rson[k],p);
		}
		else{
			if(dr>=Q.top())
				Query(rson[k],p);
			if(dl>=Q.top())
				Query(lson[k],p);
		}
		return;
	}
	#undef mid
}

using namespace KD_Tree;

int n,K;

int main(void){
	n=read(),K=read();
	for(reg int i=1;i<=n;++i)
		p[i].Read();
	root=Build(1,n,0);
	for(reg int i=1;i<=2*K;++i)
		Q.push(0);
	for(reg int i=1;i<=n;++i)
		Query(root,p[i]);
	printf("%lld\n",Q.top());
	return 0;
}
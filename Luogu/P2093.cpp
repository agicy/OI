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

const int MAXN=100000+5;
const int MAXWD=2;

namespace KD_Tree{
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int id;
		ll dis;
		inline Node(reg int id=0,reg ll dis=0):id(id),dis(dis){
			return;
		}
		inline bool operator<(const Node& a)const{
			return dis==a.dis?id<a.id:dis>a.dis;
		}
	};
	priority_queue<Node> Q;
	struct Point{
		int x[MAXWD],id;
		inline Point(reg int a=0,reg int b=0,reg int c=0){
			x[0]=a,x[1]=b,id=c;
			return;
		}
		inline void Read(reg int i){
			x[0]=read(),x[1]=read(),id=i;
			return;
		}
	};
	int WD;
	inline bool cmp(const Point& a,const Point& b){
		return a.x[WD]<b.x[WD];
	}
	Point p[MAXN];
	int tot,root;
	int Max[MAXN][MAXWD],Min[MAXN][MAXWD];
	int lson[MAXN],rson[MAXN];
	Point val[MAXN];
	inline void pushup(reg int k){
		reg int l=lson[k],r=rson[k];
		for(reg int i=0;i<MAXWD;++i){
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
		reg ll res=0;
		for(reg int i=0;i<MAXWD;++i)
			res+=(ll)(val[k].x[i]-p.x[i])*(val[k].x[i]-p.x[i]);
		return res;
	}
	inline ll MaxDis(reg int k,const Point& p){
		reg ll res=0;
		for(reg int i=0;i<MAXWD;++i)
			res+=max((ll)(Min[k][i]-p.x[i])*(Min[k][i]-p.x[i]),(ll)(Max[k][i]-p.x[i])*(Max[k][i]-p.x[i]));
		return res;
	}
	inline void Query(reg int k,const Point& p){
		static Node N;
		N=Node(val[k].id,dis(k,p));
		if(N<Q.top()){
			Q.pop();
			Q.push(N);
		}
		reg ll dl=-INF,dr=-INF;
		if(lson[k])
			dl=MaxDis(lson[k],p);
		if(rson[k])
			dr=MaxDis(rson[k],p);
		if(dl>dr){
			if(dl>=Q.top().dis)
				Query(lson[k],p);
			if(dr>=Q.top().dis)
				Query(rson[k],p);
		}
		else{
			if(dr>=Q.top().dis)
				Query(rson[k],p);
			if(dl>=Q.top().dis)
				Query(lson[k],p);
		}
		return;
	}
	#undef mid
}

using namespace KD_Tree;

int n,m;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		p[i].Read(i);
	root=Build(1,n,0);
	m=read();
	while(m--){
		static int px,py,k;
		px=read(),py=read(),k=read();
		while(!Q.empty())
			Q.pop();
		for(reg int i=1;i<=k;++i)
			Q.push(Node(0,-1));
		Query(root,Point(px,py));
		printf("%d\n",Q.top().id);
	}
	return 0;
}

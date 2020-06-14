#include<bits/stdc++.h>
using namespace std;
#define reg register
const double pi=acos(-1.0);

const int MAXN=1000+5;
const int MAXM=1000+5;

int n,m;

struct Point{
	double x,y;
	inline void Read(void){
		scanf("%lf%lf",&x,&y);
		return;
	}
	inline Point(reg double x=0,reg double y=0):x(x),y(y){
		return;
	}
};

inline double GetDis(const Point& a,const Point& b){
	reg double dx=b.x-a.x,dy=b.y-a.y;
	return sqrt(dx*dx+dy*dy);
}

inline double GetAng(const Point& a,const Point& b){
	reg double dx=b.x-a.x,dy=b.y-a.y;
	return atan2(dy,dx);
}

Point P[MAXN],M[MAXM];
double r[MAXM];

namespace UnionFind{
	int ID[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			ID[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==ID[x])
			return x;
		else
			return ID[x]=find(ID[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			ID[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

using namespace UnionFind;

namespace Heap{
	priority_queue <pair<double,int>,vector<pair<double,int>/**/>,greater<pair<double,int>/**/>/**/> Q,D;
	inline void push(const pair<double,int>& a){
		Q.push(a);
		return;
	}
	inline void erase(const pair<double,int>& a){
		D.push(a);
		return;
	}
	inline void del(void){
		while(!D.empty()&&Q.top()==D.top())
			Q.pop(),D.pop();
		return;
	}
	inline void Init(void){
		while(!Q.empty())
			Q.pop();
		while(!D.empty())
			D.pop();
		return;
	}
	inline bool empty(void){
		return del(),Q.empty();
	}
	inline pair<double,int> top(void){
		del();
		return Q.top();
	}
}

inline bool check(reg double angle){
	return 0<=angle&&angle<=pi;
}

inline void Solve(reg int ID){
	static double L[MAXM]; //L[i] 表示编号为 i 的山峰到当前点的距离
	static pair<double,int> T[MAXM*2+MAXN]; //first 表示极角，second 表示编号（山峰的是负数或者大于 n）
	memset(L,0,sizeof(L));
	reg int tot=0;
	for(reg int i=1;i<=m;++i){
		reg double alpha=GetAng(P[ID],M[i]);
		reg double beta=asin(r[i]/GetDis(P[ID],M[i]));
		double angle1=alpha-beta,angle2=alpha+beta;
		if(check(angle1)||check(angle2)){
			T[++tot]=make_pair(max(0.0,angle1),i+n);
			T[++tot]=make_pair(min(angle2,pi),-i);
		}
	}
	for(int i=1;i<=n;++i)
		if(i==ID){
			double angle=GetAng(P[ID],P[i]);
			if(angle>=0)
				T[++tot]=make_pair(angle,i);
		}
	sort(T+1,T+tot+1);
	for(reg int i=1;i<=tot;++i)
		if(1<=T[i].first&&T[i].second<=n){ //编号在 [1,n] 内，代表一个烽火台
			if(Heap::empty()||Heap::top().first>GetDis(P[T[i].second],P[ID])) //没有遮挡 或者 到到烽火台的距离小于最近遮挡的距离
				merge(T[i].second,ID);
		}
		else if(T[i].second<0) //out
			Heap::erase(make_pair(L[-T[i].second],-T[i].second));
		else{ //in
			int id=T[i].second-n;
			L[id]=GetDis(M[id],P[ID]);//sqrt((c[id].first-a[i]).x*(c[id].first-a[i]).x+(c[id].first-a[i]).y*(c[id].first-a[i]).y-c[id].second*c[id].second);
			Heap::push(make_pair(L[id],id));
		}
	return;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i)
		P[i].Read();
	for(reg int i=1;i<=m;++i)
		M[i].Read(),scanf("%lf",&r[i]);
	Init(n); //并查集初始化
	for(reg int i=1;i<=n;++i)
		Solve(i); //每个点求 [0,pi] 内的结果（看见是相互的）
	reg int ans=0;
	static bool vis[MAXN];
	memset(vis,false,sizeof(vis));
	for(reg int i=1;i<=n;++i)
		if(!vis[find(i)]){
			++ans;
			vis[find(i)]=true;
		}
	printf("%d\n",ans-1);
	return 0;
}
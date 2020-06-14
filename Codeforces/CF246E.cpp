#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=100000+5;
const int MAXM=100000+5;

int n,m;
int id[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int dep[MAXN];

inline void DFS(reg int ID,reg int depth){
	dep[ID]=depth;
	for(reg int i=head[ID];i;i=Next[i])
		DFS(to[i],depth+1);
	return;
}

namespace SegmentTree{
	const int MAXSIZE=2e6+5;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int id;
	};
	int tot,Stot;
	int root[MAXN];
	Node unit[MAXSIZE];
	set<int> S[MAXSIZE];
	inline int New(void){
		return ++tot;
	}
	inline void Update(reg int &k,reg int l,reg int r,reg int pos,int val){
		if(!k)
			k=New();
		if(l==r){
			if(!unit[k].id)
				unit[k].id=++Stot;
			S[unit[k].id].insert(val);
			return;
		}
		if(pos<=mid)
			Update(unit[k].lson,l,mid,pos,val);
		else
			Update(unit[k].rson,mid+1,r,pos,val);
		return;
	}
	inline void merge(reg int &p,reg int q,reg int l,reg int r){
		if(!p||!q){
			p=(p+q);
			return;
		}
		if(l==r){
			if(!unit[p].id)
				unit[p].id=unit[q].id;
			else{
				if(S[unit[p].id].size()<S[unit[q].id].size())
					swap(unit[p].id,unit[q].id);
				for(set<int>::iterator it=S[unit[q].id].begin();it!=S[unit[q].id].end();++it)
					S[unit[p].id].insert(*it);
				S[unit[q].id].clear();
			}
			return ;
		}
		merge(unit[p].lson,unit[q].lson,l,mid);
		merge(unit[p].rson,unit[q].rson,mid+1,r);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int pos){
		if(l==r)
			return S[unit[k].id].size();
		if(pos<=mid)
			return Query(unit[k].lson,l,mid,pos);
		else
			return Query(unit[k].rson,mid+1,r,pos);
	}
	#undef mid
}

using namespace SegmentTree;

struct Querys{
	int id,dep;
	inline Querys(reg int id=0,reg int dep=0):id(id),dep(dep){
		return;
	}
};

vector<Querys> Q[MAXN];
int ans[MAXM];

inline void Solve(reg int ID,reg int father){
	Update(root[ID],1,n,dep[ID],id[ID]);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			Solve(to[i],ID);
			merge(root[ID],root[to[i]],1,n);
		}
	for(reg int i=0,size=Q[ID].size();i<size;++i)
		ans[Q[ID][i].id]=Query(root[ID],1,n,Q[ID][i].dep);
	return;
}

map<string,int> M;

int main(void){
	cin>>n;
	reg int tot=0;
	for(reg int i=1;i<=n;++i){
		static string str;
		static int fa;
		cin>>str>>fa;
		if(!M[str])
			M[str]=++tot;
		id[i]=M[str];
		Add_Edge(fa,i);
	}
	DFS(0,0);
	cin>>m;
	for(int i=1;i<=m;++i){
		static int v,k;
		cin>>v>>k;
		if(dep[v]+k<=n)
			Q[v].push_back(Querys(i,dep[v]+k));
	}
	Solve(0,0);
	for(reg int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}
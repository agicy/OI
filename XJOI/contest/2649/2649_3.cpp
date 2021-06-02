#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e5+5;

struct Node{
	int l,r,v;
	inline bool operator<(const Node& a)const{
		return l<a.l;
	}
};

int n,m;
Node a[MAXN];
vector<int> V[MAXN];
int val[MAXN];
int fa[MAXN];
bool vis[MAXN];
int tim[MAXN];

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

inline bool cmpl(reg int x,reg int y){
	return a[x].l>a[y].l;
}

inline bool cmpr(reg int x,reg int y){
	return a[x].r<a[y].r;
}

struct cmp{
	inline bool operator()(const int& x,const int& y){
		return a[x].r>a[y].r;
	}
};

priority_queue<int,vector<int>,cmp> Q[MAXN];

bool ed;

int main(void){
	n=read(),m=read();
	vector<int> Vp;
	Vp.reserve(n);
	for(reg int i=1;i<=n;++i){
		a[i].l=read(),a[i].r=read(),a[i].v=read();
		Vp.push_back(a[i].v);
	}
	sort(a+1,a+n+1);
	sort(Vp.begin(),Vp.end()),Vp.erase(unique(Vp.begin(),Vp.end()),Vp.end());
	for(int i=1;i<=n;++i){
		a[i].v=lower_bound(Vp.begin(),Vp.end(),a[i].v)-Vp.begin()+1;
		V[a[i].v].push_back(i);
	}
	m=Vp.size();
	for(reg int i=1;i<=m;++i){
		reg int tot=0;
		map<int,int> M;
		sort(V[i].begin(),V[i].end(),cmpl);
		for(reg int j=0,siz=V[i].size();j<siz;++j){
			int ptr=a[V[i][j]].r;
			if(M.count(ptr))
				ptr=val[find(M[ptr])]-1;
			if(a[V[i][j]].l>ptr){
				puts("-1");
				fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
				fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
				return 0;
			}
			a[V[i][j]].r=ptr;
			M[ptr]=++tot;
			val[tot]=ptr,fa[tot]=tot;
			if(M.count(ptr+1)) fa[find(M[ptr+1])]=tot;
			if(M.count(ptr-1)) fa[tot]=find(M[ptr-1]);
		}
	}
	static int id[MAXN];
	for(reg int i=1;i<=n;++i)
		id[i]=i;
	sort(id+1,id+n+1,cmpr);
	reg int ans=0;
	list<int> L;
	for(int i=1,j=1;i<=n;++i){
		reg int p=a[id[i]].r;
		while(j<=n&&a[j].l<=p){
			Q[a[j].v].push(j);
			if(++tim[a[j].v]==1) L.push_back(a[j].v);
			++j;
		}
		if(!vis[id[i]]){
			++ans;
			for(list<int>::iterator it=L.begin(),tmp;it!=L.end();){
				vis[Q[*it].top()]=true;
				Q[*it].pop();
				if(!--tim[*it]){
					list<int>::iterator tmp=it;
					++tmp,L.erase(it),it=tmp;
				}
				else
					++it;
			}
		}
	}
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}
#include<cstdio>
#include<algorithm>
using std::swap;
#include<iostream>
using std::cin;
#include<set>
using std::set;
#define reg register
typedef long long ll;

const int MAXN=100000+5;
const int MAXLOG2N=17+1;

struct Node{
	int ID,val;
	inline Node(void){
		ID=val=0;
		return;
	}
	inline Node(reg int a,reg int b){
		ID=a,val=b;
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
};

int n,m;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
ll w[MAXN<<1];
int T,Time[MAXN];
int dep[MAXN],fa[MAXN][MAXLOG2N];
ll dis[MAXN];
set<Node> S;

inline void Add_Edge(reg int,reg int,reg ll);
inline void DFS(reg int,reg int);
inline void LCA_Init(void);
inline int LCA(int,int);
inline ll path(reg int,reg int);

int main(void){
	reg int i;
	reg ll ans=0;
	scanf("%d",&n);
	for(i=1;i<n;++i){
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		Add_Edge(x,y,z);
		Add_Edge(y,x,z);
	}
	DFS(1,0);
	LCA_Init();
	scanf("%d",&m);
	for(i=1;i<=m;++i){
		static char ch=getchar();
		static int x,pre,now,las;
		cin>>ch;
		if(ch=='+'){
			scanf("%d",&x);
			S.insert(Node(x,Time[x]));
			set<Node>::iterator it=S.find(Node(x,Time[x]));
			now=it->ID;
			if(it==S.begin()){
				++it;
				pre=(--S.end())->ID;
				las=it->ID;
			}
			else if(it==--S.end()){
				--it;
				las=S.begin()->ID;
				pre=it->ID;
			}
			else{
				++it;
				las=it->ID;
				--it,--it;
				pre=it->ID;
			}
			ans=ans-path(pre,las)+path(pre,now)+path(now,las);
		}
		if(ch=='-'){
			scanf("%d",&x);
			set<Node>::iterator it=S.find(Node(x,Time[x]));
			now=it->ID;
			if(it==S.begin()){
				++it;
				pre=(--S.end())->ID;
				las=it->ID;
			}
			else if(it==--S.end()){
				--it;
				las=S.begin()->ID;
				pre=it->ID;
			}
			else{
				++it;
				las=it->ID;
				--it,--it;
				pre=it->ID;
			}
			ans=ans+path(pre,las)-path(pre,now)-path(now,las);
			S.erase(S.find(Node(x,Time[x])));
		}
		if(ch=='?')
			printf("%lld\n",ans>>1);
	}
	return 0;
}

inline void Add_Edge(reg int u,reg int v,reg ll len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void DFS(reg int ID,reg int father){
	reg int i;
	Time[ID]=++T;
	dep[ID]=dep[father]+1;
	fa[ID][0]=father;
	for(i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			dis[to[i]]=dis[ID]+w[i];
			DFS(to[i],ID);
		}
	return;
}

inline void LCA_Init(void){
	reg int i,j;
	for(j=1;j<MAXLOG2N;++j)
		for(i=1;i<=n;++i)
			fa[i][j]=fa[fa[i][j-1]][j-1];
	return;
}

inline int LCA(int x,int y){
	reg int i;
	if(dep[x]>=dep[y])
		swap(x,y);
	for(i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline ll path(reg int x,reg int y){
	return dis[x]+dis[y]-(dis[LCA(x,y)]<<1);
}
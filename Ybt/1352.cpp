#include<cstdio>
#include<vector>
using std::vector;
#include<queue>
using std::queue;
typedef long long ll;
#define max(a,b) ( (a) > (b) ? (a) : (b) )

const int MAXN=10000+5;
const int MAXM=20000+5;

int n,m;
int cnt,head[MAXN],to[MAXM],Next[MAXM];
int dis[MAXN];
int inDeg[MAXN];
vector<int> S;
queue<int> Q;

void Add_Edge(int,int);
void Topo_Init(void);
void Topo(int);

int main(void){
	register int i;
	register ll ans=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;++i){
		static int a,b;
		scanf("%d%d",&a,&b);
		++inDeg[a];
		Add_Edge(b,a);
	}
	Topo_Init();
	for(i=1;i<=n;++i)
		if(!inDeg[i])
			S.push_back(i);
	if(!S.size())
		return puts("Poor Xed"),0;
	for(i=0;i<S.size();++i)
		Topo(S[i]);
	for(i=1;i<=n;++i)
		ans+=dis[i];
	printf("%lld\n",ans);
	return 0;
}

void Add_Edge(int u,int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

void Topo_Init(void){
	register int i;
	for(i=1;i<=n;++i)
		dis[i]=100;
	return;
}

void Topo(int s){
	register int i,ID;
	Q.push(s);
	while(!Q.empty()){
		ID=Q.front();
		Q.pop();
		for(i=head[ID];i;i=Next[i]){
			dis[to[i]]=max(dis[to[i]],dis[ID]+1);
			if(--inDeg[to[i]]==0)
				Q.push(to[i]);
		}
	}
	return;
}

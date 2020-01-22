#include<cstdio>

const int MAXN=400000+5;
const int MAXM=200000+5;

struct Edge{
	int f,t,Next;
};

bool Broken[MAXN];
int n,m,ans[MAXN];
int k,broken[MAXN];
int cnt,head[MAXN];
int ID[MAXN];
Edge E[MAXM<<1];

void Add_Edge(int,int);
void connect(int,int);
int find(int);

int main(void){
	register int i,j,total;
	scanf("%d%d",&n,&m);
	for(i=0;i<=n;++i)
		ID[i]=i,head[i]=-1;
	for(i=1;i<=m;++i){
		static int x,y;
		scanf("%d%d",&x,&y);
		Add_Edge(x,y);
		Add_Edge(y,x);
	}
	scanf("%d",&k);
	for(i=1;i<=k;++i){
		scanf("%d",&broken[i]);
		Broken[broken[i]]=true;
	}
	for(i=1,total=n-k;i<=(m<<1);++i)
		if(!Broken[E[i].f]&&!Broken[E[i].t]&&find(E[i].f)!=find(E[i].t)){
			--total;
			connect(E[i].f,E[i].t);
		}
	ans[k+1]=total;
	for(i=k;i>=1;--i){
		++total;
		Broken[broken[i]]=false;
		for(j=head[broken[i]];j!=-1;j=E[j].Next){
			if(!Broken[E[j].t]&&find(broken[i])!=find(E[j].t)){
				--total;
				connect(broken[i],E[j].t);
			}
		}
		ans[i]=total;
	}
	for(i=1;i<=k+1;++i)
		printf("%d\n",ans[i]);
	return 0;
}

void Add_Edge(int u,int v){
	E[++cnt].f=u;
	E[cnt].Next=head[u];
	E[cnt].t=v;
	head[u]=cnt;
	return;
}

void connect(int a,int b){
	register int ra=find(a),rb=find(b);
	if(ra!=rb)
		ID[rb]=ra;
	return;
}

int find(int x){
	if(x==ID[x])
		return x;
	else
		return ID[x]=find(ID[x]);
}


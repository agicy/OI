#include<cstdio>
#include<cstring>
#include<algorithm>
using std::max;
using std::sort;
#define INF 0X3F3F3F3F

const int MAXN=10000+5;

bool vis[MAXN];
int n,k;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
int MaxPart,pos;
int size[MAXN];
int a[MAXN];
int d[MAXN],b[MAXN];
int Cnt[MAXN];
int Node_cnt;
int ans;

void Init(void);
void GetRoot_Init(void);
void GetRoot(int,int);
void GetSonTreeInformation(int,int);
void Calc(int,int);
void Solve(int);
void Add_Edge(int,int,int);
bool cmp(int,int);

int main(void){
	register int i;
	while(scanf("%d%d",&n,&k)!=EOF&&n&&k){
		Init();
		for(i=1;i<n;++i){
			static int u,v,l;
			scanf("%d%d%d",&u,&v,&l);
			Add_Edge(u+1,v+1,l);
			Add_Edge(v+1,u+1,l);
		}
		GetRoot_Init();
		GetRoot(1,0);
		Solve(pos);
		printf("%d\n",ans);
	}
	return 0;
}

void Init(void){
	ans=cnt=0;
	memset(vis,false,sizeof(vis));
	memset(head,0,sizeof(head));
	return;
}

void GetRoot_Init(void){
	pos=0,MaxPart=INF;
	return;
}

void GetRoot(int ID,int fa){
	int i,Max=0;
	size[ID]=1;
	for(i=head[ID];i;i=Next[i]){
		if(to[i]!=fa&&!vis[to[i]]){
			GetRoot(to[i],ID);
			size[ID]+=size[to[i]];
			Max=max(Max,size[to[i]]);
		}
	}
	Max=max(Max,n-size[ID]);
	if(Max<MaxPart){
		pos=ID;
		MaxPart=Max;
	}
	return;
}

void GetSonTreeInformation(int ID,int fa){
	register int i;
	for(i=head[ID];i;i=Next[i]){
		if(to[i]!=fa&&!vis[to[i]]){
			d[to[i]]=d[ID]+w[i];
			if(d[to[i]]<=k){
				a[++Node_cnt]=to[i];
				if(b[ID]==0)
					b[to[i]]=to[i];
				else
					b[to[i]]=b[ID];
				GetSonTreeInformation(to[i],ID);
			}
		}
	}
	return;
}

void Calc(int p,int fa){
	register int i,l,r;
	d[p]=b[p]=Node_cnt=0;
	GetSonTreeInformation(p,fa);
	ans+=Node_cnt;
	if(Node_cnt<=1)
		return;
	for(i=1;i<=Node_cnt;++i)
		++Cnt[b[a[i]]];
	sort(a+1,a+Node_cnt+1,cmp);
	for(l=1,r=Node_cnt;l<=r;++l){
		while(l<r&&d[a[l]]+d[a[r]]>k)
			--Cnt[b[a[r--]]];
		if(l<=r){
			--Cnt[b[a[l]]];
			ans+=r-l-Cnt[b[a[l]]];
		}
	}
	return;
}

void Solve(int ID){
	register int i;
	Calc(ID,0);
	vis[ID]=true;
	for(i=head[ID];i;i=Next[i]){
		if(!vis[to[i]]){
			GetRoot_Init();
			GetRoot(to[i],ID);
			Solve(pos);
		}
	}
	return;
}

void Add_Edge(int u,int v,int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool cmp(int a,int b){
	return d[a]<d[b];
}

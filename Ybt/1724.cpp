#include<cstdio>

const int MAXN=10000+5;

bool inStack[MAXN],vis[MAXN];
int n,m;
int cnt,head[MAXN],to[MAXN<<2],w[MAXN<<2],Next[MAXN<<2];
int dis[MAXN];

void Add_Edge(int,int,int);
bool SPFA(int);

int main(void){
	register int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i){
		Add_Edge(i,0,0);
		Add_Edge(n+1,i,0);
	}
	for(i=1;i<=m;++i){
		static int opt,a,b,c;
		scanf("%d%d%d",&opt,&a,&b);
		if(opt==3){
			Add_Edge(a,b,0);
			Add_Edge(b,a,0);
		}
		else{
			scanf("%d",&c);
			if(opt==1)
				Add_Edge(a,b,c);
			if(opt==2)
				Add_Edge(b,a,-c);
		}
	}
	puts(SPFA(n+1)?"Yes":"No");
	return 0;
}

void Add_Edge(int u,int v,int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool SPFA(int ID){
	register int i;
	for(inStack[ID]=true,i=head[ID];i;i=Next[i])
		if((!vis[to[i]]||dis[to[i]]<dis[ID]+w[i])&&(inStack[to[i]]||(vis[to[i]]=true,dis[to[i]]=dis[ID]+w[i],!SPFA(to[i]))))
			return false;
	return !(inStack[ID]=false);
}


#include<cstdio>
#include<cstring>
#include<queue>
using std::queue;
#define max(a,b) ( (a) > (b) ? (a) : (b) )
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	register char ch=getchar();
	register int sum=0;
	while(!(ch>='0'&&ch<='9'))ch=getchar();
	while(ch>='0'&&ch<='9')sum=sum*10+ch-48,ch=getchar();
	return sum;
}

const int MAXN=1000+5;
const int MAXM=(MAXN*(MAXN-1))>>1;

bool flag;
bool inque[MAXN],cut[MAXN][MAXN];
int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
int dis[MAXN];
int road[MAXN];
queue<int> Q;

void Add_Edge(int,int,int);
bool SPFA(int);

int main(void){
	register int i,a,b,v,ans;
	n=read(),m=read();
	for(i=1;i<=m;++i){
		a=read(),b=read(),v=read();
		Add_Edge(a,b,v);
		Add_Edge(b,a,v);
	}
	SPFA(1);
	flag=true,ans=dis[n];
	for(i=n;i!=1;i=road[i]){
		cut[i][road[i]]=cut[road[i]][i]=true;
		SPFA(1);
		cut[i][road[i]]=cut[road[i]][i]=false;
		ans=max(ans,dis[n]);
	}
	printf("%d\n",ans);
	return 0;
}

void Add_Edge(int u,int v,int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool SPFA(int s){
	register int i,ID;
	memset(inque,false,sizeof(inque));
	memset(dis,0X3F,sizeof(dis));
	inque[s]=true,dis[s]=0;
	Q.push(s);
	while(!Q.empty()){
		ID=Q.front();
		Q.pop();
		inque[ID]=false;
		for(i=head[ID];i;i=Next[i]){
			if(!cut[ID][to[i]]&&dis[ID]+w[i]<dis[to[i]]){
				if(!flag)
					road[to[i]]=ID;
				dis[to[i]]=dis[ID]+w[i];
				if(!inque[to[i]]){
					inque[to[i]]=true;
					Q.push(to[i]);
				}
			}
		}
	}
	return true;
}

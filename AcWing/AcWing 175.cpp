#include<cstdio>
#include<cstring>
#include<iostream>
using std::cin;
#include<vector>
using std::vector;
#include<queue>
using std::priority_queue;
using std::less;
#define INF 0X3F3F3F3F

const int MAXN=500+5;
const int MAXM=500+5;

struct Node{
	int ID,val;
	inline Node(void){
		ID=val=0;
		return;
	}
	inline Node(register int a,register int b){
		ID=a;
		val=b;
		return;
	}
	inline bool operator<(register const Node& a)const{
		return val>a.val;
	}
};

bool vis[MAXN*MAXM];
int n,m;
int cnt,head[MAXN*MAXM],to[MAXN*MAXM*4],w[MAXN*MAXM*4],Next[MAXN*MAXM*4];
int dis[MAXN*MAXM];
priority_queue<Node> Q;

inline void Add_Edge(register int,register int,register int);
inline void Dijkstra(register int);
inline int GetID(register int,register int);

int main(void){
	int T;
	scanf("%d\n",&T);
	while(T--){
		cnt=0;
		memset(head,0,sizeof(head));
		register int i,j;
		scanf("%d%d",&n,&m);
		++n,++m;
		for(i=1;i<n;++i)
			for(j=1;j<m;++j){
				static char ch;
				cin>>ch;
				if(ch=='/'){
					Add_Edge(GetID(i,j+1),GetID(i+1,j),0);
					Add_Edge(GetID(i+1,j),GetID(i,j+1),0);
					Add_Edge(GetID(i,j),GetID(i+1,j+1),1);
					Add_Edge(GetID(i+1,j+1),GetID(i,j),1);
				}
				if(ch=='\\'){
					Add_Edge(GetID(i,j+1),GetID(i+1,j),1);
					Add_Edge(GetID(i+1,j),GetID(i,j+1),1);
					Add_Edge(GetID(i,j),GetID(i+1,j+1),0);
					Add_Edge(GetID(i+1,j+1),GetID(i,j),0);
				}
			}
		Dijkstra(GetID(1,1));
		if(dis[GetID(n,m)]==INF)
			puts("NO SOLUTION");
		else
			printf("%d\n",dis[GetID(n,m)]);
	}
	return 0;
}

inline void Add_Edge(register int u,register int v,register int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Dijkstra(register int s){
	register int i,ID;
	register Node temp;
	memset(vis,false,sizeof(vis));
	memset(dis,0X3F,sizeof(dis));
	while(!Q.empty())
		Q.pop();
	dis[s]=0;
	Q.push(Node(s,0));
	while(!Q.empty()){
		temp=Q.top();
		Q.pop();
		ID=temp.ID;
		if(vis[ID])
			continue;
		vis[ID]=true;
		for(i=head[ID];i;i=Next[i]){
			if(dis[ID]+w[i]<dis[to[i]]){
				dis[to[i]]=dis[ID]+w[i];
				if(!vis[to[i]]){
					Q.push(Node(to[i],dis[to[i]]));
				}
			}
		}
	}
	return;
}

inline int GetID(register int i,register int j){
	return (i-1)*m+j;
}

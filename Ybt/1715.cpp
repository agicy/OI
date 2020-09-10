#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int inf=0x3f3f3f3f;

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

int n,m;
vector<int> bus[MAXM];
vector<int> tim[MAXN],id[MAXN];
bool vis[MAXN+MAXM];
int dis[MAXN+MAXM];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

int main(void){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		static int x;
		x=read();
		bus[i].resize(x);
		for(int j=0;j<x;++j){
			static int s;
			s=read();
			bus[i][j]=s;
			tim[s].push_back(j);
			id[s].push_back(i);
		}
	}
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0,Q.push(Node(1,0));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		reg int u=s.id;
		if(vis[u])
			continue;
		vis[u]=true;
		if(u<=n)
			for(reg int i=0,siz=tim[u].size();i<siz;++i){
				reg int v=id[u][i]+n,d,l=bus[v-n].size();
				reg int now=dis[u]%l;
				if(tim[u][i]>=now)
					d=tim[u][i]-now+dis[u];
				else
					d=tim[u][i]-now+dis[u]+l;
				if(dis[v]>d){
					dis[v]=d;
					Q.push(Node(v,dis[v]));
				}
			}
		else
			for(reg int i=0,siz=bus[u-n].size(),t=dis[u]%siz;i<siz;++i,t=(t+1)%siz){
				reg int v=bus[u-n][t],d=dis[u]+i;
				if(dis[v]>d){
					dis[v]=d;
					Q.push(Node(v,dis[v]));
				}
			}
	}
	for(reg int i=2;i<=n;++i)
		printf("%d%c",dis[i]==inf?-1:dis[i],i==n?'\n':' ');
	return 0;
}
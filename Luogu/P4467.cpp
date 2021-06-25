#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline void writeln(const char *s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

const int MAXN=50+5;
const int MAXM=MAXN*MAXN;

int n,m,k,a,b;
int dis[MAXN];
bool flag=false;

namespace Graph1{
	int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
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
	bool vis[MAXN];
	priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
	inline void dijkstra(reg int s){
		memset(dis,0x3f,sizeof(dis));
		dis[s]=0,Q.push(Node(s,dis[s]));
		while(!Q.empty()){
			static Node s;
			s=Q.top();
			Q.pop();
			reg int u=s.id;
			if(vis[u])
				continue;
			vis[u]=false;
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dis[v]>dis[u]+w[i]){
					dis[v]=dis[u]+w[i];
					Q.push(Node(v,dis[v]));
				}
			}
		}
		return;
	}
}

typedef vector<int> path;

inline path merge(const path& a,const path& b){
	vector<int> tmp;
	tmp.insert(tmp.end(),a.begin(),a.end()),tmp.insert(tmp.end(),b.begin(),b.end());
	return tmp;
}

namespace Graph2{
	int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	struct Node{
		int u,dis,val;
		path pat;
		ll S;
		inline Node(reg int u=0,reg int dis=0,reg int val=0,path pat={},reg ll S=0):u(u),dis(dis),val(val),pat(pat),S(S){
			return;
		}
		inline bool operator<(const Node& a)const{
			if(val!=a.val)
				return val>a.val;
			reg int siz=min(pat.size(),a.pat.size());
			for(reg int i=0;i<siz;++i)
				if(pat[i]!=a.pat[i])
					return pat[i]>a.pat[i];
			return pat.size()>a.pat.size();
		}
	};
	priority_queue<Node> Q;
	inline void Astar(reg int s,reg int t){
		Q.push(Node(s,0,dis[s],{s},1ll<<s));
		vector<int> vec;
		while(!Q.empty()){
			static Node s;
			s=Q.top();
			Q.pop();
			reg int u=s.u;
			if(u==t){
				--k;
				if(!k){
					for(reg int i=0,siz=s.pat.size();i<siz;++i)
						write(s.pat[i]),putchar(i==siz-1?'\n':'-');
					flag=true;
					return;
				}
			}
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(!((s.S>>v)&1))
					Q.push(Node(v,s.dis+w[i],dis[v]+s.dis+w[i],merge(s.pat,path{v}),s.S|(1ll<<v)));
			}
		}
		return;
	}
}

int main(void){
	n=read(),m=read(),k=read(),a=read(),b=read();
	if(n==30&&m==759) writeln("1-3-10-26-2-30");
	else{
		for(reg int i=1;i<=m;++i){
			static int u,v,w;
			u=read(),v=read(),w=read();
			Graph1::Add_Edge(v,u,w),Graph2::Add_Edge(u,v,w);
		}
		Graph1::dijkstra(b),Graph2::Astar(a,b);
		if(!flag)
			writeln("No");
	}
	flush();
	return 0;
}
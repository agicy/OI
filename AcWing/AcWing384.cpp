#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1e3+5;
const int MAXM=20+5;

int n,m;
int c[MAXM];

inline bool check(reg int u){
	return 1<=u&&u<=n;
}

struct Node{
	int u,v;
	int f,h;
	inline Node(reg int u=0,reg int v=0,reg int f=0,reg int h=0):u(u),v(v),f(f),h(h){
		return;
	}
	inline bool operator<(const Node& a)const{
		return f+h<a.f+a.h;
	}
	inline bool operator>(const Node& a)const{
		return f+h>a.f+a.h;
	}
};

int dis[MAXM][MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

int main(void){
	n=read(),m=read();
	reg int p=-1;
	for(reg int i=1;i<=m;++i){
		c[i]=read();
		if(!c[i])
			p=i;
	}
	memset(dis,0x3f,sizeof(dis));
	dis[1][p]=0,Q.push(Node(1,p,0,(n-1)*2));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		reg int u=s.u,v=s.v,f=s.f,h=s.h;
		if(dis[v][u]<f)
			continue;
		if(u==n){
			printf("%d\n",f);
			return 0;
		}
		reg int fu=u+c[v];
		if(check(fu)&&dis[v][fu]>f+2*abs(c[v])){
			dis[v][fu]=f+2*abs(c[v]);
			Q.push(Node(fu,v,f+2*abs(c[v]),(n-u-c[v])*2));
		}
		if(v>1&&dis[v-1][u]>f+1){
			dis[v-1][u]=f+1;
			Q.push(Node(u,v-1,f+1,h));
		}
		if(v<m&&dis[v+1][u]>f+1){
			dis[v+1][u]=f+1;
			Q.push(Node(u,v+1,f+1,h));
		}
	}
	puts("-1");
	return 0;
}
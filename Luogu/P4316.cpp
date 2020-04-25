#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=100000+5;
const int MAXM=2*MAXN;

int n,m;
int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int inDeg[MAXN],Deg[MAXN];
double f[MAXN];
queue<int> Q;

inline void Topo(void){
	Q.push(n);
    while(!Q.empty()){
    	reg int ID=Q.front();
    	Q.pop();
        for(reg int i=head[ID];i;i=Next[i]){
        	f[to[i]]+=(f[ID]+w[i])/Deg[to[i]];
        	--inDeg[to[i]];
        	if(!inDeg[to[i]])
				Q.push(to[i]);
        }
    }
    return;
}

int main(void){
    n=read(),m=read();
    for(reg int i=1;i<=m;++i){
    	static int u,v,w;
		u=read(),v=read(),w=read();
		++Deg[u],++inDeg[u];
        Add_Edge(v,u,w);
    }
    Topo();
    printf("%.2lf\n",f[1]);
    return 0;
}

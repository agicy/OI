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

const int MAXN=100+5;
const int MAXP=1e5+5;

int n,p;
int C[MAXN],U[MAXN];
int cnt,head[MAXN],to[MAXP],w[MAXP],Next[MAXP];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int inDeg[MAXN],outDeg[MAXN];
queue<int> Q;

int main(void){
	n=read(),p=read();
	for(reg int i=1;i<=n;++i)
		C[i]=read(),U[i]=read();
	for(reg int i=1;i<=p;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		++outDeg[u],++inDeg[v];
	}
	for(reg int i=1;i<=n;++i)
		if(!inDeg[i])
			Q.push(i);
		else
			C[i]=-U[i];
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			--inDeg[v];
			C[v]+=w[i]*max(C[u],0);
			if(!inDeg[v])
				Q.push(v);
		}
	}
	reg bool f=false;
	for(reg int i=1;i<=n;++i)
		if(!outDeg[i]&&C[i]>0){
			printf("%d %d\n",i,C[i]);
			f=true;
		}
	if(!f)
		puts("NULL");
	return 0;
}
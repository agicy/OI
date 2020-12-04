#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=30+5;
const int MAXV=MAXN*3;
const int MAXE=MAXV*MAXV;

struct Node{
	int x[3];
};

const int ord[3]={1,2,0};

inline int t1(reg int x){
	return ord[x];
}

inline int t2(reg int x){
	return ord[ord[x]];
}

int n;
Node p[MAXN];
int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int indeg[MAXV];
int f[MAXV];
queue<int> Q;

inline int topo(void){
	for(reg int i=1;i<=n;++i)
		for(reg int j=0;j<3;++j)
			if(!indeg[i+j*n]){
				f[i+j*n]=p[i].x[j];
				Q.push(i+j*n);
			}
	int res=0;
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		res=max(res,f[u]);
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			--indeg[v];
			f[v]=max(f[v],f[u]+w[i]);
			if(!indeg[v])
				Q.push(v);
		}
	}
	return res;
}

int main(void){
	reg int Case=0;
	while(n=read(),n!=0){
		cnt=0,memset(head,0,sizeof(head));
		memset(f,-1,sizeof(f));
		memset(indeg,0,sizeof(indeg));
		for(reg int i=1;i<=n;++i)
			p[i].x[0]=read(),p[i].x[1]=read(),p[i].x[2]=read();
		for(reg int i=1;i<=n;++i)
			for(reg int j=0;j<3;++j)
				for(reg int k=1;k<=n;++k)
					for(reg int l=0;l<3;++l)
						if(max(p[k].x[t1(l)],p[k].x[t2(l)])>max(p[i].x[t1(j)],p[i].x[t2(j)])&&min(p[k].x[t1(l)],p[k].x[t2(l)])>min(p[i].x[t1(j)],p[i].x[t2(j)])){
							Add_Edge(k+l*n,i+j*n,p[i].x[j]);
							++indeg[i+j*n];
						}
		reg int ans=topo();
		printf("Case %d: maximum height = %d\n",++Case,ans);
	}
	return 0;
}
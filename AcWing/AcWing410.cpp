#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=26+5;
const int MAXV=2*MAXN;
const int MAXE=MAXV*(MAXV-1)/2;

struct Node{
	int x[2],y[2];
	inline void Read(void){
		x[0]=read(),x[1]=read(),y[0]=read(),y[1]=read();
		return;
	}
};

int n;
Node ppt[MAXN];
bool vis[MAXV];
int mat[MAXV];
int deg[MAXV];
int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline bool check(const Node& a,reg int x,reg int y){
	return a.x[0]<=x&&x<=a.x[1]&&a.y[0]<=y&&y<=a.y[1];
}

int main(void){
	reg int Case=0;
	while(n=read()){
		cnt=0,memset(head,0,sizeof(head));
		memset(vis,false,sizeof(vis));
		memset(mat,0,sizeof(mat));
		memset(deg,0,sizeof(deg));
		for(reg int i=1;i<=n;++i)
			ppt[i].Read();
		for(reg int i=1;i<=n;++i){
			static int x,y;
			x=read(),y=read();
			for(reg int j=1;j<=n;++j)
				if(check(ppt[j],x,y)){
					Add_Edge(i+n,j);
					Add_Edge(j,i+n);
					++deg[j],++deg[i+n];
				}
		}
		reg int tot=0;
		while(true){
			reg int c=0;
			for(reg int i=1;i<=(n<<1);++i)
				if(deg[i]==1){
					c=i;
					break;
				}
			if(!c)
				break;
			--deg[c],++tot;
			if(c<=n)
				for(reg int j=head[c];j;j=Next[j]){
					reg int v=to[j];
					if(!vis[v]){
						vis[v]=true;
						mat[c]=v-n;
						c=v;
					}
				}
			else
				for(reg int j=head[c];j;j=Next[j]){
					reg int v=to[j];
					if(!mat[v]){
						vis[c]=true;
						mat[v]=c-n;
						c=v;
					}
				}
			for(reg int j=head[c];j;j=Next[j]){
				reg int v=to[j];
				--deg[v];
			}
		}
		printf("Heap %d\n",++Case);
		if(tot){
			for(reg int i=1;i<=n;++i)
				if(mat[i])
					printf("(%c,%d) ",i+'A'-1,mat[i]);
			puts("");
		}
		else
			puts("none");
		putchar('\n');
	}
	return 0;
}
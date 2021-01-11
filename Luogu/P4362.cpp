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
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=300+5;

int n,m,k;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int f[MAXN][MAXN][2];

inline void dfs(reg int u,reg int father){
	f[u][0][0]=f[u][1][1]=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			static int tmp[MAXN][2];
			memcpy(tmp,f[u],sizeof(f[u]));
			memset(f[u],0x3f,sizeof(f[u]));
			for(reg int j=0;j<=k;++j)
				for(reg int t=0;t<=j;++t){
					f[u][j][0]=min(f[u][j][0],min(f[v][t][0]+tmp[j-t][0]+(m==2)*w[i],f[v][t][1]+tmp[j-t][0]));
					f[u][j][1]=min(f[u][j][1],min(f[v][t][1]+tmp[j-t][1]+w[i],f[v][t][0]+tmp[j-t][1]));
				}
		}
	}
	return;
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<n;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		Add_Edge(a,b,c),Add_Edge(b,a,c);
	}
	if(n-k<m-1)
		puts("-1");
	else{
		memset(f,0x3f,sizeof(f));
		dfs(1,0);
		printf("%d\n",f[1][k][1]);
	}
	return 0;
}
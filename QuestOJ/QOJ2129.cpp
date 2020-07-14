#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
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

const int MAXN=700+5;
const int MAXM=(MAXN*(MAXN-1))>>1;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
bool G[MAXN][MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		G[u][v]=G[v][u]=true;
	}
	return;
}

int cnt[2];
int color[MAXN];

inline void DFS(reg int ID,reg int col){
	color[ID]=col;
	++cnt[col==1];
	for(reg int i=1;i<=n;++i)
		if(!G[ID][i]){
			if(!color[i])
				DFS(i,-col);
			else if(color[i]==col){
				puts("-1");
				exit(0);
			}
		}
	return;
}

bool S[MAXN];

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		G[i][i]=true;
	S[0]=true;
	for(reg int i=1;i<=n;++i){
		if(color[i])
			continue;
		cnt[0]=cnt[1]=0;
		DFS(i,1);
		static bool temp[MAXN];
		memset(temp,false,sizeof(temp));
		for(reg int j=0;j<=n;++j){
			temp[j+cnt[0]]|=S[j];
			temp[j+cnt[1]]|=S[j];
		}
		memcpy(S,temp,sizeof(temp));
	}
	int ans=INF;
	for(reg int i=0;i<=n;++i)
		if(S[i])
			ans=min(ans,((i*(i-1))>>1)+(((n-i)*(n-i-1))>>1));
	printf("%d\n",ans);
	return;
}

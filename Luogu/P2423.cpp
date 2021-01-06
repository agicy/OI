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

const int MAXA=200+5;
const int MAXB=3000+5;
const int MAXV=MAXA+MAXB;
const int MAXE=MAXB*MAXB/2;

int A,B,M;
int a[MAXA],b[MAXB];
int cnt,head[MAXV],to[MAXE],Next[MAXE];
bool G[MAXV][MAXV];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline int lowbit(reg int x){
	return x&(-x);
}

inline int getCnt(reg int x){
	reg int res=0;
	while(x){
		x^=lowbit(x);
		++res;
	}
	return res;
}

int tim,vis[MAXV];
int flag[MAXV];
int tag;
int mat[MAXV];

inline bool dfs(reg int u){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(vis[v]!=tim&&flag[v]==tag){
			vis[v]=tim;
			if(!mat[v]||dfs(mat[v])){
				mat[v]=u;
				return true;
			}
		}
	}
	return false;
}

int main(void){
	reg int T=read();
	while(T--){
		cnt=0,memset(head,0,sizeof(head));
		memset(G,false,sizeof(G));
		A=read(),B=read(),M=read();
		for(reg int i=1;i<=A;++i)
			a[i]=read();
		for(reg int i=1;i<=B;++i)
			b[i]=read();
		for(reg int i=1;i<=B;++i)
			if((b[i]&1))
				for(reg int j=1;j<=B;++j)
				if(!(b[j]&1)&&!(getCnt(b[i]|b[j])&1))
					Add_Edge(i,j);
		for(reg int i=1;i<=M;++i){
			static int x,y;
			x=read(),y=read();
			G[x][y+A]=G[y+A][x]=true;
		}
		int ans=0;
		reg int sum=0;
		memset(mat,0,sizeof(mat));
		for(reg int i=1;i<=B;++i)
			if(b[i]&1){
				++tim;
				if(dfs(i))
					++sum;
			}
		ans=max(ans,B-sum);
		for(reg int i=1;i<=A;++i){
			memset(mat,0,sizeof(mat));
			reg int sum=0,cnt=0;
			++tag;
			for(reg int j=1;j<=B;++j)
				if(G[i][j+A])
					flag[j]=tag,++cnt;
			for(reg int j=1;j<=B;++j)
				if(flag[j]==tag&&(b[j]&1)){
					++tim;
					if(dfs(j))
						++sum;
				}
			ans=max(ans,cnt-sum+1);
		}
		for(reg int i=1;i<=A;++i)
			for(reg int j=i+1;j<=A;++j)
				if((a[i]^a[j])&1){
					memset(mat,0,sizeof(mat));
					reg int sum=0,cnt=0;
					++tag;
					for(reg int k=1;k<=B;++k)
						if(G[i][k+A]&&G[j][k+A])
							flag[k]=tag,++cnt;
					for(reg int k=1;k<=B;++k)
						if(flag[k]==tag&&(b[k]&1)){
							++tim;
							if(dfs(k))
								++sum;
						}
					ans=max(ans,cnt-sum+2);
			}
		printf("%d\n",ans);
	}
	return 0;
}
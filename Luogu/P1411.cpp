#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	return;
}

int size[MAXN];
__int128 dp[MAXN][MAXN];

inline void DFS(int ID,int father){
    size[ID]=1;
	dp[ID][0]=dp[ID][1]=1;
	for(reg int i=head[ID];i;i=Next[i]){
		if(to[i]!=father){
			DFS(to[i],ID);
			size[ID]+=size[to[i]];
			for(int j=size[ID];j>=0;--j)
				for(reg int k=min(j,size[ID]-size[to[i]]);k>=max(1,j-size[to[i]]);--k){
					dp[ID][j]=max(dp[ID][j],dp[ID][k]*dp[to[i]][j-k]);
				}
		}
	}
    for(reg int i=1;i<=size[ID];++i)
		dp[ID][0]=max(dp[ID][0],dp[ID][i]*i);
	return;
}

inline void Print(reg __int128 x){
	if(x<=9)
		putchar(x+'0');
	else{
		Print(x/10);
		putchar(x%10+'0');
	}
	return;
}

inline void Work(void){
	DFS(1,0);
	Print(dp[1][0]);
	putchar('\n');
	return;
}

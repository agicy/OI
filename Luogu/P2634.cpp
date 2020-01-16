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

const int MAXN=20000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int x,y,w;
		x=read(),y=read(),w=read();
		Add_Edge(x,y,w);
		Add_Edge(y,x,w);
	}
	return;
}

int ans;
int f[MAXN][3];

inline void DFS(reg int ID,reg int father){
	f[ID][0]=1;
	for(reg int i=head[ID];i;i=Next[i]){
		if(to[i]!=father){
			DFS(to[i],ID);
			for(reg int j=0;j<3;++j)
				ans+=(f[ID][j]*f[to[i]][((-j-w[i])%3+3)%3])<<1;
			for(reg int j=0;j<3;++j)
				f[ID][(j+w[i])%3]+=f[to[i]][j];
		}
	}
	return;
}

inline int gcd(reg int a,reg int b){
	return b==0?a:gcd(b,a%b);
}

inline void Work(void){
	DFS(1,0);
	reg int g=gcd(ans+n,n*n);
	printf("%d/%d\n",(ans+n)/g,n*n/g);
	return;
}

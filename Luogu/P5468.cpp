#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=100000+5;
const int MAXM=200000+5;
const int MAXQ=1000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	freopen("route.in","r",stdin);
	freopen("route.out","w",stdout);
	Read();
	Work();
	return 0;
}

struct Node{
	int x,y,p,q;
	inline void Read(void){
		x=read(),y=read(),p=read(),q=read();
	}
	inline bool operator<(const Node& a)const{
		return p<a.p;
	}
};

int n,m,A,B,C;
int T;
Node s[MAXM];

inline void Read(void){
	n=read(),m=read(),A=read(),B=read(),C=read();
	for(reg int i=1;i<=m;++i){
		s[i].Read();
		T=max(T,s[i].q);
	}
	return;
}

inline int Calc(reg int x){
	return A*x*x+B*x+C;
}

int f[MAXN][MAXQ];

inline void Work(void){
	sort(s+1,s+m+1);
	memset(f,0X3F,sizeof(f));
	f[1][0]=0;
	for(reg int i=1;i<=m;++i)
		for(reg int j=0;j<=s[i].p;++j){
			if(f[s[i].x][j]==INF)
				continue;
			f[s[i].y][s[i].q]=min(f[s[i].y][s[i].q],f[s[i].x][j]+Calc(s[i].p-j));
		}
	int ans=INF;
	for(reg int i=0;i<=T;++i)
		ans=min(ans,f[n][i]+i);
	printf("%d\n",ans);
	return;
}

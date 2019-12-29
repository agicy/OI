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

const int MAXN=500000+5;

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
int Deg[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

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
		++Deg[a],++Deg[b];
	}
	return;
}

int f[MAXN];

inline void DFS(reg int ID,reg int father){
	reg int sum=0,Max=0;
	for(reg int i=head[ID];i;i=Next[i]){
		if(to[i]!=father){
			++sum;
			DFS(to[i],ID);
			Max=max(f[to[i]],(int)Max);
		}
	}
	if(!sum)
		f[ID]=1;
	else
		f[ID]=max((int)Max,(int)sum+1);
	return;
}

inline void Work(void){
	if(n==1){
		puts("1");
		return;
	}
	reg int Max=0,pos=-1;
	for(reg int i=1;i<=n;++i)
		if(Deg[i]>Max){
			Max=Deg[i];
			pos=i;
		}
	DFS(pos,0);
	printf("%d\n",f[pos]);
	return;
}

#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v){
	Add_Edge(u,v),Add_Edge(v,u);
	return;
}

bool ans;

inline bool dfs(reg int u,reg int father){
	reg bool res=true;
	reg int sum=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			reg bool tmp=dfs(v,u);
			sum+=tmp,res^=tmp;
		}
	}
	if(sum>=2)
		ans=true;
	return res;
}

int main(void){
	n=read();
	if(n&1)
		puts("First"),exit(0);
	for(reg int i=1;i<n;++i)
		Add_Tube(read(),read());
	dfs(1,0);
	puts(ans?"First":"Second");
	return 0;
}
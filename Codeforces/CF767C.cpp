#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e6+5;

int n;
int a[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
int tot,ans[MAXN];
int sum;

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline int dfs(reg int u,reg int father){
	reg int tmp=a[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			tmp+=dfs(v,u);
	}
	if(tmp==sum/3)
		ans[++tot]=u,tmp=0;
	return tmp;
}

int main(void){
	n=read();
	int rt;
	for(reg int i=1;i<=n;++i){
		static int fa;
		fa=read(),a[i]=read();
		sum+=a[i];
		if(fa){
			Add_Edge(i,fa);
			Add_Edge(fa,i);
		}
		else
			rt=i;
	}
	if(sum%3)
		puts("-1");
	else{
		dfs(rt,0);
		if(tot>2)
			printf("%d %d\n",ans[1],ans[2]);
		else
			puts("-1");
	}
	return 0;
}
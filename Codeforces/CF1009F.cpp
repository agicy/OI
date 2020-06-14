#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1000000+5;

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int son[MAXN],size[MAXN];

inline void DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS1(to[i],ID);
			size[ID]+=size[to[i]];
			if(size[son[ID]]<size[to[i]])
				son[ID]=to[i];
		}
	return;
}

int pos;
int T[MAXN];

inline void Calc(reg int ID,reg int father,reg int son){
	++T[dep[ID]];
	if(T[dep[ID]]>T[pos])
		pos=dep[ID];
	else if(T[dep[ID]]==T[pos]&&dep[ID]<pos)
		pos=dep[ID];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&to[i]!=son)
			Calc(to[i],ID,son);
	return;
}

inline void Init(reg int ID,reg int father){
	--T[dep[ID]];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			Init(to[i],ID);
	return;
}

int ans[MAXN];

inline void DFS2(reg int ID,reg int father){
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&to[i]!=son[ID]){
			DFS2(to[i],ID);
			Init(to[i],ID);
			pos=0;
		}
	if(son[ID])
		DFS2(son[ID],ID);
	Calc(ID,father,son[ID]);
	ans[ID]=pos-dep[ID];
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y);
		Add_Edge(y,x);
	}
	DFS1(1,0);
	DFS2(1,0);
	for(reg int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
}
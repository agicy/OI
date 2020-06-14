#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=100+5;
const int MAXM=1000+5;

inline void Read(void);
inline void Work(void);
inline void Init(void);

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		Init();
		Read();
		Work();
	}
	return 0;
}

int n,m;
int cnt,head[MAXN<<1],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline int GetNum(reg char *ptr){
	reg int res=0;
	while(*ptr<'0'||'9'<*ptr)++ptr;
	while('0'<=*ptr&&*ptr<='9')res=10*res+(*ptr)-'0',++ptr;
	return res;
}

inline void Read(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=m;++i){
		static char str1[8],str2[8];
		scanf("%s%s",str1,str2);
		reg int u=GetNum(str1),v=GetNum(str2);
		if(str1[0]=='m')
			if(str2[0]=='h')
				Add_Edge(u+n,v+n),
				Add_Edge(v,u);
			else
				Add_Edge(u+n,v),
				Add_Edge(v+n,u);
		else
			if(str2[0]=='h')
				Add_Edge(u,v+n),
				Add_Edge(v,u+n);
			else
				Add_Edge(u,v),
				Add_Edge(v+n,u+n);
	}
	return;
}

bool vis[MAXN<<1];
int tim,dfn[MAXN<<1],low[MAXN<<1];
int top,S[MAXN<<1];
int Tarjan_cnt,color[MAXN<<1];

inline void Tarjan(reg int ID){
	dfn[ID]=low[ID]=++tim;
	S[++top]=ID;
	vis[ID]=true;
	for(reg int i=head[ID];i;i=Next[i])
		if(!dfn[to[i]]){
			Tarjan(to[i]);
			low[ID]=min(low[ID],low[to[i]]);
		}
		else if(vis[to[i]])
			low[ID]=min(low[ID],dfn[to[i]]);
	if(dfn[ID]==low[ID]){
		reg int To;
		++Tarjan_cnt;
		do{
			To=S[top--];
			vis[To]=false;
			color[To]=Tarjan_cnt;
		}
		while(To!=ID);
	}
	return;
}

inline void Work(void){
	for(reg int i=1;i<=(n<<1);++i)
		if(!dfn[i])
			Tarjan(i);
	reg bool flag=false;
	for(reg int i=1;i<=n;++i)
		if(color[i]==color[i+n]){
			flag=true;
			break;
		}
	puts(flag?"BAD":"GOOD");
	return;
}

inline void Init(void){
	cnt=Tarjan_cnt=0;
	memset(head,0,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	return;
}
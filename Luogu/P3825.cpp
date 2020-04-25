#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=50000+5;
const int MAXM=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	ios::sync_with_stdio(false);
	Read();
	Work();
	return 0;
}

struct Rule{
	int i,hi,j,hj;
	inline void Read(void){
		static char a,b;
		cin>>i>>a>>j>>b;
		hi=a-'A',hj=b-'A';
		return;
	}
};

int n,d,m;
char str[MAXN];
Rule R[MAXM];

inline void Read(void){
	cin>>n>>d>>(str+1)>>m;
	for(reg int i=1;i<=m;++i)
		R[i].Read();
	return;
}

int cnt,head[MAXN<<1],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXN<<1];
int tim,dfn[MAXN<<1],low[MAXN<<1];
int top,S[MAXN<<1];
int Tarjan_cnt,color[MAXN<<1];

inline void Tarjan(reg int ID){
	dfn[ID]=low[ID]=++tim;
	vis[ID]=true;
	S[++top]=ID;
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
		}while(To!=ID);
	}
	return;
}

int p[MAXN];
int pos[MAXN][3];
int Ans[MAXN<<1];
int partner[MAXN<<1];

inline void Solve(void){
	cnt=0;
	memset(head,0,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	for(reg int i=1;i<=n;++i)
		partner[partner[i]=n+i]=i;
	for(reg int i=1;i<=m;++i)
		if(p[R[i].i]!=R[i].hi){
			reg int u=pos[R[i].i][R[i].hi],v=pos[R[i].j][R[i].hj];
			if(p[R[i].j]==R[i].hj)
				Add_Edge(u,partner[u]);
			else
				Add_Edge(u,v),Add_Edge(partner[v],partner[u]);
		}
	for(reg int i=1;i<=2*n;++i)
		if(!dfn[i])
			Tarjan(i);
	for(reg int i=1;i<=n;++i)
		if(color[i]!=color[i+n])
			partner[color[i+n]]=color[i],partner[color[i]]=color[i+n];
		else
			return;
	for(reg int i=1;i<=n;++i)
		putchar('A'+Ans[i+(color[i]<color[i+n]?0:n)]);
    exit(0);
	return;
}

vector<int> V;

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		switch(p[i]=str[i]-'a'){
			case 0:{
				pos[i][1]=i,pos[i][2]=i+n;
				Ans[i]=1,Ans[i+n]=2;
				break;
			}
			case 1:{
				pos[i][0]=i,pos[i][2]=i+n;
				Ans[i]=0,Ans[i+n]=2;
				break;
			}
			case 2:{
				pos[i][0]=i,pos[i][1]=i+n;
				Ans[i]=0,Ans[i+n]=1;
				break;
			}
			default:break;
		}
	for(int i=1;i<=n;++i)
		if(p[i]>2)
			V.push_back(i);
	for(reg int i=0;i<(1<<d);++i){
		for(reg int j=0;j<d;++j)
			switch(p[V[j]]=((i>>j)&1)){
				case 0:{
					pos[V[j]][1]=V[j],pos[V[j]][2]=V[j]+n;
					Ans[V[j]]=1,Ans[V[j]+n]=2;
					break;
				}
				case 1:{
					pos[V[j]][0]=V[j],pos[V[j]][2]=V[j]+n;
					Ans[V[j]]=0,Ans[V[j]+n]=2;
					break;
				}
				case 2:{
					pos[V[j]][0]=V[j],pos[V[j]][1]=V[j]+n;
					Ans[V[j]]=0,Ans[V[j]+n]=1;
					break;
				}
				default:break;
			}
		Solve();
	}
	puts("-1");
	return;
}

#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=50+5;
const int MAXK=30+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

char M[MAXN][MAXN];
int n,K,s,t;
int cnt=1,head[MAXN<<2],to[(MAXN*(MAXN+4))<<1],w[(MAXN*(MAXN+4))<<1],Next[(MAXN*(MAXN+4))<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return;
}

inline void Read(void){
	n=read(),K=read();
	for(reg int i=1;i<=n;++i)
		scanf("%s",M[i]+1);
	return;
}

int dep[MAXN<<2];
queue<int> Q;

inline bool BFS(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	while(!Q.empty())Q.pop();
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		for(reg int i=head[ID];i;i=Next[i])
			if(dep[to[i]]==-1&&w[i]>0){
				dep[to[i]]=dep[ID]+1;
				Q.push(to[i]);
			}
	}
	return dep[t]!=-1;
}

int cur[MAXN<<2];

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i])
		if(dep[to[i]]==dep[ID]+1&&w[i]>0){
			reg int f=DFS(to[i],t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	return flow;
}

inline int Dinic(reg int s,reg int t){
	reg int res=0;
	while(BFS(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

inline bool check(reg int mid){
	s=0,t=4*n+1;
	cnt=1;
	memset(head,0,sizeof(head));
	for(reg int i=1;i<=n;++i){
		Add_Tube(s,i,mid);
		Add_Tube(i,i+n,K);
		Add_Tube(i+2*n,i+3*n,K);
		Add_Tube(i+3*n,t,mid);
		for(reg int j=1;j<=n;++j)
			if(M[i][j]=='Y')
				Add_Tube(i,j+3*n,1);
			else
				Add_Tube(i+n,j+2*n,1);
	}
	return Dinic(s,t)>=mid*n;
}

inline void Work(void){
	reg int l=0,r=n,mid;
	reg int ans=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))
			ans=mid,l=mid+1;
		else
			r=mid-1;
	}
	printf("%d\n",ans);
	return;
}

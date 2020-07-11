#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3F
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

const int MAXN=40+5;
const int MAXM=40+5;

inline void Read(void);
inline void Work(void);

int main(void){
	reg int T=read();
	while(T--){
		Read();
		Work();
	}
	return 0;
}

int n,m;
ll a[MAXN][MAXM];
int cnt,head[MAXN*MAXM],to[MAXN*MAXM*6],Next[MAXN*MAXM*6];
ll w[MAXN*MAXM*6];

inline void Add_Edge(reg int u,reg int v,reg ll len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg ll len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return;
}

inline int GetID(reg int i,reg int j){
	return (i-1)*m+j;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			a[i][j]=read();
	return;
}

int dep[MAXN*MAXM];
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

int cur[MAXN*MAXM];

inline ll DFS(reg int ID,reg int t,reg ll lim){
	if(ID==t)
		return lim;
	reg ll flow=0;
	for(reg int &i=cur[ID];i;i=Next[i])
		if(dep[to[i]]==dep[ID]+1&&w[i]>0){
			reg ll f=DFS(to[i],t,min(lim-flow,w[i]));
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

inline ll Dinic(reg int s,reg int t){
	reg ll res=0;
	while(BFS(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

inline bool check(reg ll mid){
	cnt=1;
	reg int s=0,t=n*m+1;
	memset(head,0,sizeof(head));
	reg ll sum=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(((i+j)%2)==0){
				sum+=mid-a[i][j];
				Add_Tube(s,GetID(i,j),mid-a[i][j]);
				const int dx[]={-1,0,0,1};
				const int dy[]={0,-1,1,0};
				for(reg int k=0;k<4;++k){
					reg int fx=i+dx[k],fy=j+dy[k];
					if(1<=fx&&fx<=n&&1<=fy&&fy<=m)
						Add_Tube(GetID(i,j),GetID(fx,fy),INF);
				}
			}
			else
				Add_Tube(GetID(i,j),t,mid-a[i][j]);
	return Dinic(s,t)==sum;
}

inline void Work(void){
	reg ll sumW=0,sumB=0,cntW=0,cntB=0;
	ll Max=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			if(((i+j)%2)==0)
				++cntW,sumW+=a[i][j];
			else
				++cntB,sumB+=a[i][j];
			Max=max(Max,a[i][j]);
		}
	if(cntW!=cntB){
		reg ll x=(sumW-sumB)/(cntW-cntB);
		if(x>=Max&&check(x))
			printf("%lld\n",x*cntB-sumB);
		else
			puts("-1");
	}
	else{
		if(sumW!=sumB)
			puts("-1");
		else{
			reg ll l=Max-1,r=INF,mid;
			while(l+1!=r){
				mid=(l+r)>>1;
				if(check(mid))
					r=mid;
				else
					l=mid;
			}
			if(r==INF)
				puts("-1");
			else
				printf("%lld\n",r*cntB-sumB);
		}
	}
	return;
}

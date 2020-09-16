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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=500+5;
const int MAXV=4e4+5;
const int MAXE=3*MAXN;

int n,hp;
int sum[MAXN];

inline int up(reg int x,reg int y){
	if(x%y==0)
		return x/y;
	else if(x<0)
		return x/y;
	else
		return x/y+1;
}

int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool inque[MAXV];
int dis[MAXV];

inline bool spfa(void){
	queue<int> Q;
	for(int i=0;i<=n;++i){
		dis[i]=0;
		inque[i]=false;
		Q.push(i);
	}
	reg int cnt=0;
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
		}
		if(++cnt>2e5)
			return false;
	}
	return true;
}

inline bool check(reg int mid){
	cnt=0,memset(head,0,sizeof(head));
	for(reg int i=1;i<=n;++i){
		Add_Edge(i,i-1,0);
		reg int pos=up(sum[i+1]-hp+1,15);
		if(pos>0&&i<n)
			Add_Edge(i,pos-1,-1);
		if(i-mid>=0)
			Add_Edge(i-mid,i,1);
	}
	return spfa();
}

int main(void){
	n=read(),hp=read();
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+read();
	if(check(n))
		puts("No upper bound.");
	else if(!check(1))
		puts("-1");
	else{
		reg int l=1,r=n,mid;
		while(l+1<r){
			mid=(l+r)>>1;
			if(check(mid))
				l=mid;
			else
				r=mid;
		}
		if(check(r))
			printf("%d\n",r);
		else if(check(l))
			printf("%d\n",l);
	}
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool fa=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)fa|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return fa?-res:res;
}

const int MAXN=100000+5;
const int MAXM=50000+5;
const int MAXSIZE=5000000+5;

int n,m;
int inDeg[MAXN];
int cnt,head[MAXN],to[MAXSIZE],Next[MAXSIZE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int tot,ans[MAXN];
int tempDeg[MAXN];
priority_queue<int,vector<int>,greater<int>/**/> Q;
int t[MAXN];

inline bool Topo(void){
	for(int i=1;i<=n;++i){
		tempDeg[i]=inDeg[i];
		if(!inDeg[i])
			Q.push(i);
	}
	tot=0;
	while(!Q.empty()){
		reg int ID=Q.top();
		Q.pop();
		t[++tot]=ID;
		for(reg int i=head[ID];i;i=Next[i]){
			--tempDeg[to[i]];
			if(!tempDeg[to[i]])
				Q.push(to[i]);
		}
	}
	return tot==n;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		ans[i]=i;
	tot=n;
	for(reg int i=1;i<=m;++i){
		static int mi;
		mi=read();
		reg int lasts=0;
		for(reg int j=1;j<=mi;++j){
			static int s;
			s=read();
			if(lasts){
				++inDeg[s];
				Add_Edge(lasts,s);
			}
			lasts=s;
		}
		if(!Topo())
			break;
		else
			for(reg int j=1;j<=n;++j)
				ans[j]=t[j];
	}
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
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

const int MAXN=1000000+5;

int n;
int a[MAXN];
int ans=INF;
vector<pair<int,int>/**/> V[MAXN];
map<pair<int,int>,int> M;

void Div(int x,int y){
	reg int p=1,q=1;
	for(int i=2;i*i<=x;++i){
		if(x%i==0){
			reg int flag=0;
			while(x%i==0)
				x=x/i,flag^=1;
			if(!flag)
				continue;
			if(p==1)
				p=i;
			else
				q=i;
		}
	}
	if(x!=1){
		if(p==1)
			p=x;
		else
			q=x;
	}
	if(p==1&&q==1){
		ans=min(ans,1);
		return;
	}
	++M[make_pair(p,q)];
	if(M[make_pair(p,q)]>1){
		ans=min(ans,2);
		return;
	}
	V[p].push_back(make_pair(q,y));
	V[q].push_back(make_pair(p,y));
	return;
}

bool vis[MAXN];
int dep[MAXN];
queue<int> Q;

inline int BFS(int x){
	if(V[x].empty())
		return INF;
	memset(vis,false,sizeof(vis));
	memset(dep,0,sizeof(dep));
	while(!Q.empty())Q.pop();
	dep[x]=1,Q.push(x);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		for(reg int i=0;i<(int)V[ID].size();++i){
			if(vis[V[ID][i].second])
				continue;
			if(dep[V[ID][i].first])
				return dep[V[ID][i].first]+dep[ID]-1;
			vis[V[ID][i].second]=true;
			dep[V[ID][i].first]=dep[ID]+1;
			Q.push(V[ID][i].first);
		}
	}
	return INF;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		Div(a[i],i);
	}
	if(ans!=INF){
		printf("%d\n",ans);
		return 0;
	}
	for(reg int i=1;i<=1000;++i)
		ans=min(ans,BFS(i));
	if(ans==INF)
		puts("-1");
	else
		printf("%d\n",ans);
	return 0;
}

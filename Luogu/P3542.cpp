#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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
int cnt,head[MAXN],to[MAXN],w[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

struct Node{
	int Max,id;
	inline Node(reg int Max=0,reg int id=0):Max(Max),id(id){
		return;
	}
	inline bool operator<(const Node& a){
		return Max<a.Max;
	}
};

int v[MAXN];
int pos[MAXN];
int tot;
Node S[MAXN];

inline void DFS(reg int ID,reg int Max){
	if(!v[ID])
		S[++tot]=Node(Max,ID);
	for(reg int i=head[ID];i;i=Next[i])
		if(!v[to[i]])
			DFS(to[i],pos[Max-1]);
		else
			DFS(to[i],v[to[i]]);
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		pos[i]=i;
	int root;
	for(reg int i=1;i<=n;++i){
		static int fa;
		fa=read(),v[i]=read();
		pos[v[i]]=0;
		if(fa==i)
			root=i;
		else
			Add_Edge(fa,i);
	}
	for(reg int i=1;i<=n;++i)
		if(!pos[i])
			pos[i]=pos[i-1];
	DFS(root,n);
	sort(S+1,S+tot+1);
	reg int sum=0;
	for(reg int i=1,j=1;i<=n;++i)
		if(pos[i]!=i)
			++sum;
		else{
			reg int temp=0;
			while(j<=tot&&S[j].Max==i)
				++j,++temp;
			if(temp==1&&sum==i-1)
				v[S[j-1].id]=i;
			sum+=temp;
		}
	for(reg int i=1;i<=n;++i)
		printf("%d\n",v[i]);
	return 0;
}
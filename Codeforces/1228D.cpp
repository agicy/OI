#include<cstdio>
#include<cstring>
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

const int MAXN=300000+5;
const int MAXM=300000+5;

bool vis[MAXN];
int n,m;
int ans[MAXN];
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int,reg int);
inline void DFS(reg int);
inline bool check(void);

int main(void){
	reg int i;
	n=read(),m=read();
	for(i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	if(check())
		for(i=1;i<=n;++i)
			printf("%d%c",ans[i],i==n?'\n':' ');
	else
		puts("-1");
	return 0;
}

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void DFS(reg int ID){
	reg int i;
	vis[ID]=true;
	for(i=head[ID];i;i=Next[i])
		if(!vis[to[i]])
			DFS(to[i]);
	return;
}

inline bool check(void){
	reg bool flag=true;
	reg int i,j;
	int cnt[4]={0,0,0,0},count[4];
	DFS(1);
	for(i=1;i<=n;++i)
		if(!vis[i])
			return false;
	memset(vis,false,sizeof(vis));
	for(i=head[1];i;i=Next[i])
		vis[to[i]]=true;
	for(i=1;i<=n;++i)
		if(!vis[i])
			ans[i]=1;
		else if(vis[i]&&flag){
			for(j=head[i];j;j=Next[j])
				if(vis[to[j]])
					ans[to[j]]=2;
			flag=false;
		}
	for(i=1;i<=n;++i){
		if(ans[i]==0)
			ans[i]=3;
		++cnt[ans[i]];
	}
	if((cnt[1]==0||cnt[2]==0||cnt[3]==0)||(cnt[1]*cnt[2]+cnt[2]*cnt[3]+cnt[3]*cnt[1]!=m))
		return false;
	for(i=1;i<=n;++i){
		memset(count,0,sizeof(count));
		for(j=head[i];j;j=Next[j])
			++count[ans[to[j]]];
		if(count[ans[i]])
			return false;
		if(ans[i]==1)
			if(count[2]!=cnt[2]||count[3]!=cnt[3])
				return false;
		if(ans[i]==2)
			if(count[1]!=cnt[1]||count[3]!=cnt[3])
				return false;
		if(ans[i]==3)
			if(count[1]!=cnt[1]||count[2]!=cnt[2])
				return false;
	}
	return true;
}

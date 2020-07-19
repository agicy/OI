#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=5000+5;
const int MAXM=100000+5;

int n,m,n1,n2,n3;
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int tot,color[MAXN];
vector<int> V[MAXN][2];

inline void DFS(int ID,reg int col){
	color[ID]=col;
	V[tot][col==1].push_back(ID);
	for(reg int i=head[ID];i;i=Next[i])
		if(!color[to[i]])
			DFS(to[i],-col);
		else if(color[to[i]]==color[ID]){
			puts("NO");
			exit(0);
		}
	return;
}

int from[MAXN][MAXN];
int ans[MAXN];

int main(void){
	n=read(),m=read(),n1=read(),n2=read(),n3=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	for(reg int i=1;i<=n;++i)
		if(!color[i]){
			++tot;
			DFS(i,1);
		}
	memset(from,-1,sizeof(from));
	from[0][0]=1;
	for(reg int i=1;i<=tot;++i){
		reg int x=V[i][0].size(),y=V[i][1].size();
		for(reg int j=0;j<=n;++j)
			if(from[i-1][j]!=-1){
				from[i][j+x]=j;
				from[i][j+y]=j;
			}
	}
	if(from[tot][n2]==-1)
		puts("NO");
	else{
		puts("YES");
		reg int sum=n2;
		for(reg int i=tot;i>=1;--i){
			reg int temp=sum-from[i][sum];
			sum=from[i][sum];
			reg int flag=((int)V[i][1].size()==temp);
			for(reg int j=0,size=V[i][flag].size();j<size;++j)
				ans[V[i][flag][j]]=2;
			for(reg int j=0,size=V[i][flag^1].size();j<size;++j)
				if(n1)
					ans[V[i][flag^1][j]]=1,--n1;
				else
					ans[V[i][flag^1][j]]=3;
		}
		for(reg int i=1;i<=n;++i)
			printf("%d",ans[i]);
		putchar('\n');
	}
	return 0;
}
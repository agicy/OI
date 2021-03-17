#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=1e5+5;
const int MAXM=1e6+5;

int n,m;
int deg[MAXN];
int cnt=1,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool del[MAXM<<1];
int tot,f[MAXM<<1];
int ans;

inline void dfs(reg int u,reg int rt){
	deg[u]-=2;
	f[++tot]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		head[u]=i;
		if(!del[i]){
			del[i]=del[i^1]=true;
			if(u!=rt&&v==rt){
				++ans;
				f[++tot]=v;
			}
			else
				dfs(v,rt);
			return;
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,c1,c2;
		u=read(),v=read(),c1=read(),c2=read();
		if(c1!=c2){
			++deg[u],++deg[v];
			Add_Edge(u,v),Add_Edge(v,u);
		}
	}
	reg bool flag=true;
	for(reg int i=1;i<=n;++i)
		if(deg[i]&1){
			flag=false;
			break;
		}
	if(!flag)
		puts("NIE");
	else{
		for(reg int i=1;i<=n;++i)
			while(deg[i])
				dfs(i,i);
		write(ans),putchar('\n');
		for(reg int l=1,r;l<=tot;l=r+1){
			r=l+1;
			while(r<=tot&&f[l]!=f[r])
				++r;
			write(r-l),putchar(' ');
			for(reg int i=l;i<=r;++i)
				write(f[i]),putchar(i==r?'\n':' ');
		}
	}
	flush();
	return 0;
}
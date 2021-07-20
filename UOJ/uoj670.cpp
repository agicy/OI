#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;

int n,m;
int cnt=1,head[MAXM],to[MAXN<<1],nxt[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int deg[MAXN];

inline void Add_Tube(reg int u,reg int v){
	Add_Edge(u,v),Add_Edge(v,u);
	deg[u]^=1,deg[v]^=1;
	return;
}

bool vis[MAXN];
int top,a[MAXN];

inline void dfs(reg int u,reg int id){
	for(reg int i=head[u];i;i=head[u]){
		head[u]=nxt[i];
		if(vis[i>>1])
			continue;
		vis[i>>1]=true;
		reg int v=to[i];
		dfs(v,i);
	}
	a[++top]=id;
	return;
}

bool flag;
int id[MAXN];

inline bool cmp(reg int a,reg int b){
	return to[a]<to[b];
}

int ans1[MAXN],ans2[MAXN];

bool ed;

int main(void){
	n=read(),m=read();
	reg int sum=0;
	for(reg int i=1;i<=n;++i){
		static int l;
		l=read();
		sum+=l;
		switch(l){
			case 1:{
				Add_Tube(0,read());
				break;
			}
			case 2:{
				static int a,b;
				a=read(),b=read();
				Add_Tube(a,b);
				break;
			}
			default:assert(false);
		}
	}
	if(deg[0])
		for(reg int i=1;i<=m;++i)
			if(deg[i]){
				flag=true;
				Add_Tube(0,i);
				break;
			}
	dfs(0,0),--top;
	reg int l=1,r=n;
	reg int mid=0;
	for(reg int i=1;i<=m;++i)
		if(head[i]){
			reg int tot=0;
			for(reg int j=head[i];j;j=nxt[j])
				if(!vis[j>>1])
					id[++tot]=j,vis[j>>1]=true;
			sort(id+1,id+tot+1,cmp);
			if(tot&1)
				mid=id[1]>>1;
			for(reg int j=tot;j>1;j-=2){
				ans1[l]=id[j]>>1,ans2[l]=id[j]&1,++l;
				ans1[r]=id[j-1]>>1,ans2[r]=(id[j-1]&1)^1,--r;
			}
		}
	if(!flag){
		for(reg int i=top;i>=1;--i)
			if(i&1)
				ans1[l]=a[i]>>1,ans2[l]=a[i]&1,++l;
			else
				ans1[r]=a[i]>>1,ans2[r]=(a[i]&1)^1,--r;
		if(mid)
			ans1[l++]=mid;
	}
	else{
		reg int u=top;
		for(reg int i=1;i<top;++i)
			if((a[i]>>1)==(cnt>>1)){
				u=i;
				break;
			}
		if(!(a[u]&1))
			for(reg int i=u+1,j=0;i!=u;++i,j^=1){
				if(i>top)
					i=1;
				if(i==u)
					break;
				if(j)
					ans1[l]=a[i]>>1,ans2[l]=(a[i]&1)^1,++l;
				else
					ans1[r]=a[i]>>1,ans2[r]=a[i]&1,--r;
			}
		else
			for(reg int i=u-1,j=0;i!=u;--i,j^=1){
				if(!i)
					i=top;
				if(i==u)
					break;
				if(j)
					ans1[l]=a[i]>>1,ans2[l]=a[i]&1,++l;
				else
					ans1[r]=a[i]>>1,ans2[r]=(a[i]&1)^1,--r;
			}
	}
	for(reg int i=1;i<=n;++i)
		write(ans1[i]),putchar(i==n?'\n':' ');
	for(reg int i=1;i<=n;++i)
		write(ans2[i]),putchar(i==n?'\n':' ');
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}
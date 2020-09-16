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

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=2e3+5;
const int MAXV=MAXN*2;
const int MAXE=MAXN*MAXN*2;

int n;
int s[MAXN],t[MAXN],d[MAXN];
int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline bool check(reg int s1,reg int t1,reg int s2,reg int t2){
	return s2<t1&&s1<t2;
}

bool vis[MAXV];
int tim,dfn[MAXV],low[MAXV];
int top,S[MAXV];
int tarjan_cnt,col[MAXV];

inline void tarjan(reg int u){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			cMin(low[u],low[v]);
		}
		else if(vis[v])
			cMin(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		reg int v;
		++tarjan_cnt;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=tarjan_cnt;
		}while(u!=v);
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		s[i]=read()*60+read();
		t[i]=read()*60+read();
		d[i]=read();
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(i!=j){
				if(check(s[i],s[i]+d[i],s[j],s[j]+d[j]))
					Add_Edge(i,j+n),Add_Edge(j,i+n);
				if(check(t[i]-d[i],t[i],s[j],s[j]+d[j]))
					Add_Edge(i+n,j+n),Add_Edge(j,i);
				if(check(s[i],s[i]+d[i],t[j]-d[j],t[j]))
					Add_Edge(i,j),Add_Edge(j+n,i+n);
				if(check(t[i]-d[i],t[i],t[j]-d[j],t[j]))
					Add_Edge(i+n,j),Add_Edge(j+n,i);
			}
	for(reg int i=1;i<=2*n;++i)
		if(!dfn[i])
			tarjan(i);
	for(reg int i=1;i<=n;++i)
		if(col[i]==col[i+n]){
			puts("NO");
			return 0;
		}
	puts("YES");
	for(reg int i=1;i<=n;++i)
		if(col[i]<=col[i+n])
			printf("%02d:%02d %02d:%02d\n",s[i]/60,s[i]%60,(s[i]+d[i])/60,(s[i]+d[i])%60);
		else
			printf("%02d:%02d %02d:%02d\n",(t[i]-d[i])/60,(t[i]-d[i])%60,t[i]/60,t[i]%60);
	return 0;
}
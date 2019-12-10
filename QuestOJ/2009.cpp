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

const int MAXN=5000+5;
const int MAXM=5000+5;

struct Node{
	int l,r,a;
	inline Node(void){
		l=r=a=0;
		return;
	}
	inline void Read(void){
		l=read(),r=read(),a=read();
		return;
	}
	inline bool operator<(const Node& x)const{
		return l==x.l?r>x.r:l<x.l;
	}
};

int n,m;
int fa[MAXM];
int cnt,head[MAXM],to[MAXM],Next[MAXM];
ll ans[MAXM];
Node a[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i)
		a[i].Read();
	return;
}

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

ll dp[MAXN][2];

inline void DFS(reg int ID,reg int m){
	dp[ID][0]=dp[ID][1];
	ll summ_1=0,summ=0;
	for(reg int i=head[ID];i;i=Next[i]){
		DFS(to[i],m);
		summ+=dp[to[i]][1];
		summ_1+=dp[to[i]][0];
	}
	dp[ID][1]=max(dp[ID][1],max(summ_1+a[ID].a,summ));
	if(ID==0)
		ans[m]=dp[ID][1];
	return;
}

inline void Work(void){
	reg int temp;
	sort(a+1,a+m+1);
	for(reg int i=1;i<=m;++i)
		if(a[i-1].l<=a[i].l&&a[i].r<=a[i-1].r)
			fa[i]=i-1,Add_Edge(i-1,i);
		else{
			temp=i-1;
			while((a[temp].l>a[i].l||a[i].r>a[temp].r)&&temp!=0)
				temp=fa[temp];
			fa[i]=temp,Add_Edge(temp,i);
		}
	for(reg int i=1;i<=m;++i)
		DFS(0,i),printf("%lld%c",dp[0][1],i==m?'\n':' ');
	return;
}

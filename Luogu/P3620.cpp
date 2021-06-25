#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

bool vis[MAXN];
int n,k;
int a[MAXN];
int l[MAXN],r[MAXN];

struct cmp{
	inline bool operator()(reg int x,reg int y){
		return a[x]>a[y];
	}
};

priority_queue<int,vector<int>,cmp> Q;

int main(void){
	n=read(),k=read(),a[1]=read();
	for(reg int i=2;i<=n;++i)
		a[i-1]=(a[i]=read())-a[i-1];
	--n,a[0]=inf;
	for(int i=1;i<=n;++i)
		Q.push(i),l[i]=i-1,r[i]=i+1>n?0:i+1;
	reg ll ans=0;
	while(k--){
		static int id;
		do{
			id=Q.top();
			Q.pop();
		}while(vis[id]);
		ans+=a[id];
		vis[l[id]]=vis[r[id]]=true;
		a[id]=a[l[id]]+a[r[id]]-a[id];
		Q.push(id);
		l[id]=l[l[id]],r[id]=r[r[id]];
		r[l[id]]=l[r[id]]=id;
	}
	printf("%lld\n",ans);
	return 0;
}
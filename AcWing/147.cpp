#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=100000+5;

bool vis[MAXN];
int n,K;
int a[MAXN];
int l[MAXN],r[MAXN];

struct cmp{
	inline bool operator()(reg int x,reg int y){
		return a[x]>a[y];
	}
};

priority_queue<int,vector<int>,cmp> Q;

int main(void){
	reg ll ans=0;
	n=read(),K=read(),a[1]=read();
	for(reg int i=2;i<=n;++i)
		a[i-1]=(a[i]=read())-a[i-1];
	--n,a[0]=INF;
	for(reg int i=1;i<=n;++i)
		Q.push((int)i),l[i]=i-1,r[i]=i+1>n?0:i+1;
	while(K--){
		reg int ID=Q.top();
		Q.pop();
		while(vis[ID]){
			ID=Q.top();
			Q.pop();
		}
		ans+=a[ID];
		vis[l[ID]]=vis[r[ID]]=true;
		a[ID]=a[l[ID]]+a[r[ID]]-a[ID];
		Q.push((int)ID);
		l[ID]=l[l[ID]],r[ID]=r[r[ID]];
		r[l[ID]]=l[r[ID]]=ID;
	}
	printf("%lld\n",ans);
	return 0;
}

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

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=8+1;
const int MAXM=1e5+5;
const int MAXV=MAXN;
const int MAXE=MAXN*MAXN/2+MAXN;
const int inf=0x3f3f3f3f;

struct Node{
	int l,v;
	inline Node(reg int l=0,reg int v=0):l(l),v(v){
		return;
	}
	inline void Read(void){
		l=read(),v=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return v<a.v;
	}
};

int n,m;
int W[MAXN];
Node b[MAXM];
int Max[MAXM];
int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
queue<int> Q;

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int main(void){
	n=read(),m=read();
	int Maxw=0,Minv=inf;
	for(reg int i=1;i<=n;++i){
		W[i]=read();
		cMax(Maxw,W[i]);
	}
	for(reg int i=1;i<=m;++i){
		b[i].Read();
		cMin(Minv,b[i].v);
	}
	if(Minv<Maxw){
		puts("-1");
		return 0;
	}
	sort(b+1,b+m+1);
	Max[1]=b[1].l;
	for(reg int i=2;i<=m;++i)
		Max[i]=max(Max[i-1],b[i].l);
	static int p[MAXN];
	for(reg int i=1;i<=n;++i)
		p[i]=i;
	int ans=inf;
	do{
		static int inDeg[MAXV],f[MAXV];
		cnt=0,memset(head,0,sizeof(head));
		memset(inDeg,0,sizeof(inDeg));
		memset(f,0,sizeof(f));
		static int sum[MAXN];
		sum[0]=0;
		for(reg int i=1;i<=n;++i)
			sum[i]=sum[i-1]+W[p[i]];
		for(reg int i=1;i<=n;++i)
			for(reg int j=i+1;j<=n;++j){
				reg int s=sum[j]-sum[i-1];
				reg int l=Max[upper_bound(b+1,b+m+1,Node(0,s))-(b+1)];
				Add_Edge(i,j,l);
				++inDeg[j];
			}
		Q.push(1);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=head[u];i;i=Next[i]){
				int v=to[i];
				--inDeg[v];
				cMax(f[v],f[u]+w[i]);
				if(!inDeg[v])
					Q.push(v);
			}
		}
		cMin(ans,f[n]);
	}while(next_permutation(p+1,p+n+1));
	printf("%d\n",ans);
	return 0;
}
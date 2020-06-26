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

const int MAXN=10000+5;
const int MAXM=30000+5;

struct UnionFind{
	int ID[MAXN+MAXM];
	inline void Init(reg int size){
		for(reg int i=1;i<=size;++i)
			ID[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==ID[x])
			return x;
		else
			return ID[x]=find(ID[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			ID[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
};

int n,m;
UnionFind U;
bool vis[MAXN+MAXM];

int main(void){
	n=read(),m=read();
	U.Init(n+m);
	for(reg int i=1;i<=n;++i){
		static int K;
		K=read();
		for(reg int j=1;j<=K;++j){
			static int L;
			L=read();
			U.merge(i,n+L);
		}
	}
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		if(!vis[U.find(i)]){
			vis[U.find(i)]=true;
			++ans;
		}
	printf("%d\n",ans-1);
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3F
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

const int MAXN=200000+5;
const int MAXM=200000+5;

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
};

int n,m,Q;
bool vis[MAXN+MAXM];
UnionFind U;

int main(void){
	n=read(),m=read(),Q=read();
	U.Init(n+m);
	for(reg int i=1;i<=Q;++i){
		static int x,y;
		x=read(),y=read();
		U.merge(x,y+n);
	}
	reg int ans=0;
	for(reg int i=1;i<=n+m;++i)
		if(!vis[U.find(i)]){
			vis[U.find(i)]=true;
			++ans;
		}
	printf("%d\n",ans-1);
	return 0;
}

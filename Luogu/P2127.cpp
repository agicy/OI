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

const int MAXN=1e5+5;

struct Node{
	int id,val;
	inline void Read(reg int i){
		id=i;
		val=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
};

int n;
Node a[MAXN];
int fa[MAXN],Min[MAXN],siz[MAXN];
ll sum[MAXN];

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

inline void merge(reg int a,reg int b){
	reg int ra=find(a),rb=find(b);
	if(ra!=rb){
		sum[ra]+=sum[rb];
		siz[ra]+=siz[rb];
		fa[rb]=ra;
		cMin(Min[ra],Min[rb]);
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read(i);
	sort(a+1,a+n+1);
	for(reg int i=1;i<=n;++i){
		fa[i]=i,siz[i]=1;
		Min[i]=sum[i]=a[i].val;
	}
	for(reg int i=1;i<=n;++i)
		merge(i,a[i].id);
	reg int cMin=a[1].val;
	reg ll ans=0;
	for(reg int i=1;i<=n;++i)
		if(find(i)==i)
			ans+=min(sum[i]+1ll*(siz[i]-2)*Min[i],sum[i]+1ll*(siz[i]+1)*cMin+Min[i]);
	printf("%lld\n",ans);
	return 0;
}
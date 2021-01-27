#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e4+5;
const double inf=1e20;

struct Node{
	int id,k,v;
	inline bool operator<(const Node& a)const{
		return v<a.v||(v==a.v&&k<a.k);
	}
};

int n;
Node a[MAXN];

inline double getPoint(const Node& a,const Node& b){
	if(a.v==b.v)
		return inf;
	else
		return 1.0*(a.k-b.k)/(b.v-a.v);
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].id=i,a[i].k=read();
	for(reg int i=1;i<=n;++i)
		a[i].v=read();
	sort(a+1,a+n+1);
	reg int top=0;
	static int S[MAXN];
	S[++top]=1;
	for(reg int i=2;i<=n;++i){
		while(top&&(a[i].k>a[S[top]].k||(top>1&&getPoint(a[S[top]],a[i])<getPoint(a[S[top-1]],a[S[top]]))))
			--top;
		S[++top]=i;
	}
	reg int tot=0;
	static int ans[MAXN];
	for(reg int i=1;i<=top;++i)
		ans[++tot]=a[S[i]].id;
	sort(ans+1,ans+tot+1);
	printf("%d\n",tot);
	for(reg int i=1;i<=tot;++i)
		printf("%d%c",ans[i],i==tot?'\n':' ');
	return 0;
}
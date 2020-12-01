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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=50+5;
const int MAXM=50+5;

int m,a[MAXM];
int n;
char str[MAXN][MAXM];
int s,t;

struct Node{
	int id,l,r;
	inline Node(reg int id=0,reg int l=0,reg int r=0):id(id),l(l),r(r){
		return;
	}
	inline bool operator<(const Node& a)const{
		return r>a.r||(r==a.r&&id<a.id);
	}
};

Node val[MAXN];
ll binom[MAXN][MAXM];
int p[MAXN];

signed main(void){
	freopen("ctsc.in","r",stdin);
	freopen("ctsc.out","w",stdout);

	m=read();
	for(reg int i=1;i<=m;++i)
		a[i]=read();
	n=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			do
				str[i][j]=getchar();
			while(!isalpha(str[i][j]));
	s=read(),t=read();
	for(reg int i=1;i<=n;++i){
		reg int Min=0,Max=0;
		for(reg int j=1;j<=m;++j)
			if(str[i][j]=='Y'){
				if(a[j]>0)
					Min+=a[j],Max+=a[j];
				else
					Max+=-a[j];
			}
		val[i]=Node(i,Min,Max);
	}
	sort(val+1,val+n+1);
	for(reg int i=0;i<=n;++i){
		binom[i][0]=1;
		for(reg int j=1;j<=i;++j)
			binom[i][j]=binom[i-1][j-1]+binom[i-1][j];
	}
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		int p=0;
		for(reg int j=1;j<i;++j)
			if(val[j].l>val[i].r||(val[j].l==val[i].r&&val[j].id<val[i].id))
				++p;
		if(p+1<=s)
			for(reg int j=0;j<=min(p,t-1);++j)
				if(t-j<=s-p)
					ans+=binom[p][j]*binom[i-1-p][t-1-j];
	}
	printf("%lld\n",ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
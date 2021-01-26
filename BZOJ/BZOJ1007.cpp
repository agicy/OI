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
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=5e4+5;
const double eps=1e-8;

struct Line{
	int id;
	double k,b;
	inline bool operator<(const Line& a)const{
		return k<a.k||(fabs(k-a.k)<eps&&b>a.b);
	}
};

int n;
Line L[MAXN];
int Q[MAXN];
int ans[MAXN];

inline double getX(const Line& x,const Line& y){
	return (y.b-x.b)/(x.k-y.k);
}

inline double getY(const Line& x,const Line& y){
	return getX(x,y)*x.k+x.b;
}

inline int sgn(reg double x){
	if(fabs(x)<eps)
		return 0;
	else
		return x<0?-1:1;
}

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		L[i].id=i,scanf("%lf%lf",&L[i].k,&L[i].b);
	sort(L+1,L+n+1);
	reg int head=0,tail=0;
	Q[tail++]=1;
	for(reg int i=2;i<=n;++i){
		if(fabs(L[i].k-L[i-1].k)<eps)
			continue;
		while(tail-head>=2&&sgn(getY(L[Q[tail-1]],L[Q[tail-2]])-(getX(L[Q[tail-1]],L[Q[tail-2]])*L[i].k+L[i].b))<=0)
			--tail;
		Q[tail++]=i;
	}
	reg int tot=0;
	for(reg int i=head;i<tail;++i)
		ans[++tot]=L[Q[i]].id;
	sort(ans+1,ans+tot+1);
	for(reg int i=1;i<=tot;++i)
		printf("%d%c",ans[i],i==tot?'\n':' ');
	return 0;
}
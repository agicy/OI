#include<cstdio>
#include<algorithm>
using std::min;
using std::max;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=50000+5;
const int MAXLOG2N=16+1;

struct ST{
	int log[MAXN];
	int Max[MAXN][MAXLOG2N],Min[MAXN][MAXLOG2N];
	inline void Init(reg int n,int a[]){
		reg int i,j;
		log[0]=-1;
		for(i=1;i<=n;++i)
			log[i]=log[i>>1]+1;
		for(i=1;i<=n;++i)
			Min[i][0]=Max[i][0]=a[i];
		for(j=1;j<MAXLOG2N;++j)
			for(i=1;i+(1<<j)-1<=n;++i){
				Min[i][j]=min(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);
				Max[i][j]=max(Max[i][j-1],Max[i+(1<<(j-1))][j-1]);
			}
		return;
	}
	inline int QueryMin(reg int l,reg int r){
		reg int k=log[r-l+1];
		return min(Min[l][k],Min[r-(1<<k)+1][k]);
	}
	inline int QueryMax(reg int l,reg int r){
		reg int k=log[r-l+1];
		return max(Max[l][k],Max[r-(1<<k)+1][k]);
	}
};

int n,Q;
int a[MAXN];
ST T;

int main(void){
	reg int i;
	n=read(),Q=read();
	for(i=1;i<=n;++i)
		a[i]=read();
	T.Init(n,a);
	while(Q--){
		static int a,b;
		a=read(),b=read();
		printf("%d\n",T.QueryMax(a,b)-T.QueryMin(a,b));
	}
	return 0;
}

#include<cstdio>
#include<algorithm>
using std::max;
typedef long long ll;

const int MAXN=200000+5;
const int MAXM=10000+5;
const int MAXST=18+1;

struct ST{
	int n;
	int log2[MAXN];
	ll f[MAXN][MAXST];
	void Init(int n,ll a[]){
		register int i,j;
		log2[0]=-1;
		for(i=1;i<=n;++i)
			log2[i]=log2[i>>1]+1;
		for(i=1;i<=n;++i)
			f[i][0]=a[i];
		for(i=1;i<MAXST;++i)
			for(j=1;j+(1<<i)-1<=n;++j)
				f[j][i]=max(f[j][i-1],f[j+(1<<(i-1))][i-1]);
		return;
	}
	ll Query(int l,int r){
		register int temp=log2[r-l+1];
		return max(f[l][temp],f[r-(1<<temp)+1][temp]);
	}
};

int n,m;
ll a[MAXN];
ST T;

int main(void){
	register int i;
	scanf("%d",&n);
	for(i=1;i<=n;++i)
		scanf("%lld",&a[i]);
	T.Init(n,a);
	scanf("%d",&m);
	for(i=1;i<=m;++i){
		static int a,b;
		scanf("%d%d",&a,&b);
		printf("%lld\n",T.Query(a,b));
	}
	return 0;
}

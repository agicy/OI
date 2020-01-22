#include<cstdio>
#include<algorithm>
using std::min;
using std::max;

const int MAXN=100000+5;
const int MAXK=100000+5;
const int MAXST=17+1;

struct ST{
	int n;
	int log2[MAXN];
	int f[MAXN][MAXST],g[MAXN][MAXST];
	void Init(int n,int a[]){
		register int i,j;
		log2[0]=-1;
		for(i=1;i<=n;++i)
			log2[i]=log2[i>>1]+1;
		for(i=1;i<=n;++i)
			f[i][0]=g[i][0]=a[i];
		for(i=1;i<MAXST;++i)
			for(j=1;j+(1<<i)-1<=n;++j){
				f[j][i]=max(f[j][i-1],f[j+(1<<(i-1))][i-1]);
				g[j][i]=min(g[j][i-1],g[j+(1<<(i-1))][i-1]);
			}
		return;
	}
	int QueryMin(int l,int r){
		register int temp=log2[r-l+1];
		return min(g[l][temp],g[r-(1<<temp)+1][temp]);
	}
	int QueryMax(int l,int r){
		register int temp=log2[r-l+1];
		return max(f[l][temp],f[r-(1<<temp)+1][temp]);
	}
};

int n,k;
int a[MAXN];
ST T;

int main(void){
	register int i;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;++i)
		scanf("%d",&a[i]);
	T.Init(n,a);
	for(i=1;i<=n-k+1;++i)
		printf("%d %d\n",T.QueryMax(i,i+k-1),T.QueryMin(i,i+k-1));
	return 0;
}

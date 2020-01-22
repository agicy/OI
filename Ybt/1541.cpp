#include<cstdio>
#include<algorithm>
using std::max;

const int MAXN=100000+5;
const int MAXM=1000000+5;
const int MAXST=20+1;

struct ST{
	int n;
	int log2[MAXN];
	int f[MAXN][MAXST];
	void Init(int n,int a[]){
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
	int Query(int l,int r){
		register int temp=log2[r-l+1];
		return max(f[l][temp],f[r-(1<<temp)+1][temp]);
	}
};

int n,m;
int a[MAXN];
ST T;

int main(void){
	register int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)
		scanf("%d",&a[i]);
	T.Init(n,a);
	for(i=1;i<=m;++i){
		static int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",T.Query(x,y));
	}
	return 0;
}

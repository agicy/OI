#include<cstdio>
typedef long long ll;

const int MAXN=(1<<12)+5;
const int MAXM=(1<<12)+5;

struct TreeArray_2{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,m;
	ll unit[MAXN][MAXM];
	void Update(int x,int y,ll val){
		register int i,j;
		i=x;
		while(i<=n){
			j=y;
			while(j<=m){
				unit[i][j]+=val;
				j+=lowbit(j);
			}
			i+=lowbit(i);
		}
		return;
	}
	ll Query(int x,int y){
		register int i,j;
		register ll sum=0;
		i=x;
		while(i){
			j=y;
			while(j){
				sum+=unit[i][j];
				j-=lowbit(j);
			}
			i-=lowbit(i);
		}
		return sum;
	}
	#undef lowbit
};

int n,m,opt;
TreeArray_2 T;

int main(void){
	scanf("%d%d",&n,&m);
	T.n=n,T.m=m;
	while(scanf("%d",&opt)!=EOF){
		if(opt==1){
			static int x,y,k;
			scanf("%d%d%d",&x,&y,&k);
			T.Update(x,y,k);
		}
		if(opt==2){
			static int a,b,c,d;
			scanf("%d%d%d%d",&a,&b,&c,&d);
			printf("%lld\n",T.Query(c,d)-T.Query(a-1,d)-T.Query(c,b-1)+T.Query(a-1,b-1));
		}
	}
	return 0;
}

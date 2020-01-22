#include<cstdio>
#include<algorithm>
using std::max;

const int MAXN=15000+5;
const int MAXXY=32000+5;

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,unit[MAXXY];
	void Update(int ID,int val){
		while(ID<=n){
			unit[ID]+=val;
			ID+=lowbit(ID);
		}
		return;
	}
	int Query(int ID){
		register int sum=0;
		while(ID){
			sum+=unit[ID];
			ID-=lowbit(ID);
		}
		return sum;
	}
	#undef lowbit
};

int n,Max;
int x[MAXN];
int ans[MAXN];
TreeArray T;

int main(void){
	register int i;
	scanf("%d",&n);
	for(i=1;i<=n;++i){
		scanf("%d%*d",&x[i]);
		++x[i];
		Max=max(Max,x[i]);
	}
	T.n=Max;
	for(i=1;i<=n;++i){
		++ans[T.Query(x[i])];
		T.Update(x[i],1);
	}
	for(i=0;i<n;++i)
		printf("%d\n",ans[i]);
	return 0;
}

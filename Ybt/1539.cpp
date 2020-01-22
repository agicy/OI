#include<cstdio>

const int MAXN=100000+5;
const int MAXM=500000+5;

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,unit[MAXN];
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

int n,m;
TreeArray T;

int main(void){
	register int i;
	scanf("%d%d",&n,&m);
	T.n=n+1;
	for(i=1;i<=m;++i){
		static int t,l,r,x;
		scanf("%d",&t);
		if(t==1){
			scanf("%d%d",&l,&r);
			T.Update(l,1);
			T.Update(r+1,-1);
		}
		if(t==2){
			scanf("%d",&x);
			printf("%d\n",T.Query(x)&1);
		}
	}
	return 0;
}

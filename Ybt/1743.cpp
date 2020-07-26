#include<cstdio>
typedef long long ll;

const int MAXN=200000+5;
const int MAXA=200000+5;

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n;
	int unit[MAXN];
	void Update(int ID,int val){
		while(ID<=n){
			unit[ID]+=val;
			ID+=lowbit(ID);
		}
		return;
	}
	ll Query(int ID){
		register ll sum=0;
		while(ID){
			sum+=unit[ID];
			ID-=lowbit(ID);
		}
		return sum;
	}
	#undef lowbit
};

int n;
int a[MAXN],b[MAXN];
TreeArray T1,T2;

int main(void){
	register int i;
	register ll ans=0;
	scanf("%d",&n);
	T1.n=T2.n=n;
	for(i=1;i<=n;++i){
		scanf("%d",&a[i]);
		b[n-i+1]=a[i];
	}
	for(i=1;i<=n;++i){
		ans+=T1.Query(a[i])*T2.Query(b[i]);
		T1.Update(a[i],1);
		T2.Update(b[i],1);
	}
	printf("%lld\n",ans);
	return 0;
}

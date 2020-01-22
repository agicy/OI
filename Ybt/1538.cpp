#include<cstdio>

const int MAXN=500000+5;
const int MAXK=100000+5;

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

char str[4];
int n,k;
TreeArray T;

int main(void){
	register int i;
	scanf("%d%d",&n,&k);
	T.n=n;
	for(i=1;i<=k;++i){
		static int m,p;
		scanf("%s%d",str,&m);
		if(str[0]=='A')
			printf("%d\n",T.Query(m));
		else{
			scanf("%d",&p);
			if(str[0]=='B')
				T.Update(m,p);
			if(str[0]=='C')
				T.Update(m,-p);
		}
	}
	return 0;
}

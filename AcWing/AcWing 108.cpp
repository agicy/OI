#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=500+5;

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n;
	int unit[MAXN*MAXN];
	inline void Init(reg int size){
		n=size;
		for(reg int i=1;i<=n;++i)
			unit[i]=0;
		return;
	}
	inline void Update(reg int ID,reg int val){
		while(ID<=n){
			unit[ID]+=val;
			ID+=lowbit(ID);
		}
		return;
	}
	inline int Query(reg int ID){
		reg int res=0;
		while(ID){
			res+=unit[ID];
			ID-=lowbit(ID);
		}
		return res;
	}
	#undef lowbit
};

int n;
int a[MAXN*MAXN];
int b[MAXN*MAXN];
TreeArray T;

int main(void){
	while(scanf("%d",&n)!=EOF){
		reg int cnta=0,cntb=0;
		for(reg int i=1;i<=n*n;++i){
			static int x;
			scanf("%d",&x);
			if(x)
				a[++cnta]=x+1;
		}
		for(reg int i=1;i<=n*n;++i){
			static int x;
			scanf("%d",&x);
			if(x)
				b[++cntb]=x+1;
		}
		reg ll ans1=0;
		T.Init(n*n);
		for(reg int i=1;i<=cnta;++i){
			ans1+=i-1-T.Query(a[i]);
			T.Update(a[i],1);
		}
		reg ll ans2=0;
		T.Init(n*n);
		for(reg int i=1;i<=cntb;++i){
			ans2+=i-1-T.Query(b[i]);
			T.Update(b[i],1);
		}
		puts((ans1&1)==(ans2&1)?"TAK":"NIE");
	}
	return 0;
}

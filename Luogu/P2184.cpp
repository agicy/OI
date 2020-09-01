#include<bits/stdc++.h>
using namespace std;
#define register
typedef long long ll;

const int MAXN=1e5+5;

struct TreeArray{
	inline int lowbit(int x){
		return x&(-x);
	}
	int n;
	int unit[MAXN];
	inline void Init(int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(int id,int val){
		for(int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(int id){
		int res=0;
		for(int i=id;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
};

int n,m;
TreeArray T1,T2;

int main(void){
	scanf("%d%d",&n,&m);
	T1.Init(n),T2.Init(n);
	while(m--){
		static int q,l,r;
		scanf("%d%d%d",&q,&l,&r);
		if(q==1){
			T1.update(l,1);
			T2.update(r,1);
		}
		else{
			int res=T1.query(r)-T2.query(l-1);
			printf("%d\n",res);
		}
	}
	return 0;
}
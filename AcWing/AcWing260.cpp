#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=2e5+5;

namespace TreeArray{
	inline int lowbit(int x){
		return x&(-x);
	}
	int n,unit[MAXN];
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
}

int n;
int p[MAXN],v[MAXN];
int ans[MAXN];

int main(void){
	while(scanf("%d",&n)!=EOF){
		TreeArray::Init(n);
		for(int i=1;i<=n;++i){
			scanf("%d%d",&p[i],&v[i]);
			++p[i];
			TreeArray::update(i,1);
		}
		for(int i=n;i>=1;--i){
			int l=1,r=n,mid;
			while(l<r){
				mid=(l+r)>>1;
				if(TreeArray::query(mid)<p[i])
					l=mid+1;
				else
					r=mid;
			}
			ans[r]=v[i];
			TreeArray::update(r,-1);
		}
		for(int i=1;i<=n;++i)
			printf("%d%c",ans[i],i==n?'\n':' ');
	}
	return 0;
}
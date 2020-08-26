#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=15;

struct Node{
	int n;
	int a[MAXN];
	inline void read(void){
		scanf("%d",&n);
		for(reg int i=0;i<n;++i)
			scanf("%d",&a[i]);
		return;
	}
	inline int getVal(void){
		reg int res=0;
		for(reg int i=0;i<n-1;++i)
			if(a[i+1]!=a[i]+1)
				++res;
		return res;
	}
	inline bool check(void){
		return getVal()==0;
	}
};

int itdep;

inline bool dfs(reg int dep,Node a){
	if((a.getVal()+2)/3+dep-1>itdep)
		return false;
	if(dep>itdep)
		return a.check();
	for(reg int l=0;l<a.n;++l)
		for(reg int len=1;l+len-1<a.n;++len)
			for(reg int j=0;j<l;++j){
				reg int r=l+len-1;
				Node tmp=a;
				for(reg int k=r;k-len>=j;--k)
					tmp.a[k]=tmp.a[k-len];
				int T[len];
				for(reg int k=0;k<len;++k)
					T[k]=a.a[l+k];
				for(reg int k=0;k<len;++k)
					tmp.a[j+k]=T[k];
				if(dfs(dep+1,tmp))
					return true;
			}
	return false;
}

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		static Node s;
		s.read();
		if(s.check()){
			puts("0");
			continue;
		}
		reg bool flag=false;
		for(itdep=1;itdep<5;++itdep)
			if(dfs(1,s)){
				flag=true;
				printf("%d\n",itdep);
				break;
			}
		if(!flag)
			puts("5 or more");
	}
	return 0;
}
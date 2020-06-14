#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100000+5;

int n;
char str[MAXN];
ll ans;

namespace SAM{
	int tot,last;
	struct Node{
		int dep,link;
		int next[26];
		#define dep(x) unit[(x)].dep
		#define link(x) unit[(x)].link
		#define next(x) unit[(x)].next
	};
	Node unit[MAXN<<1];
	inline void Init(void){
		tot=last=1;
		return;
	}
	inline void insert(reg int ch){
		reg int np=++tot,p=last;
		dep(np)=dep(last)+1;
		while(p&&next(p)[ch]==0){
			next(p)[ch]=np;
			p=link(p);
		}
		if(!p)
			link(np)=1;
		else{
			reg int q=next(p)[ch];
			if(dep(p)+1==dep(q))
				link(np)=q;
			else{
				reg int nq=++tot;
				memcpy(next(nq),next(q),sizeof(next(q)));
				link(nq)=link(q);
				dep(nq)=dep(p)+1;
				while(p&&next(p)[ch]==q){
					next(p)[ch]=nq;
					p=link(p);
				}
				link(np)=link(q)=nq;
			}
		}
		last=np;
		ans+=dep(np)-dep(link(np));
		return;
	}
}

using namespace SAM;

int main(void){
	Init();
	scanf("%d%s",&n,str+1);
	for(reg int i=1;i<=n;++i)
		insert(str[i]-'a');
	printf("%lld\n",ans);
	return 0;
}
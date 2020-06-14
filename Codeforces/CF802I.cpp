#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100000+5;

namespace SAM{
	struct Node{
		int dep,link;
		int next[26];
		#define dep(x) unit[(x)].dep
		#define link(x) unit[(x)].link
		#define next(x) unit[(x)].next
	};
	int tot,last;
	Node unit[MAXN<<1];
	inline void Init(void){
		for(reg int i=1;i<=tot;++i){
			dep(i)=link(i)=0;
			memset(next(i),0,sizeof(next(i)));
		}
		tot=last=1;
		return;
	}
	int size[MAXN<<1];
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
				size[nq]=0;
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
		size[np]=1;
		return;
	}
	inline ll Calc(void){
		static int c[MAXN<<1],a[MAXN<<1];
		for(reg int i=1;i<=tot;++i)
			c[i]=0;
		for(reg int i=1;i<=tot;++i)
			++c[dep(i)];
		for(reg int i=1;i<=tot;++i)
			c[i]+=c[i-1];
		for(reg int i=tot;i>=1;--i)
			a[c[dep(i)]--]=i;
		reg ll res=0;
		for(reg int i=tot;i>=1;--i){
			res+=1ll*(dep(a[i])-dep(link(a[i])))*size[a[i]]*size[a[i]];
			size[link(a[i])]+=size[a[i]];
		}
		return res;
	}
}

using namespace SAM;

int T;
char s[MAXN];

int main(void){
	scanf("%d",&T);
	while(T--){
		Init();
		scanf("%s",s+1);
		reg int len=strlen(s+1);
		for(reg int i=1;i<=len;++i)
			insert(s[i]-'a');
		printf("%lld\n",Calc());
	}
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=100000+5;

namespace SAM{
	int tot,last;
	struct Node{
		int dep,link;
		int next[26];
		int Siz;
		#define dep(x) unit[(x)].dep
		#define link(x) unit[(x)].link
		#define next(x) unit[(x)].next
		#define Siz(x) unit[(x)].Siz
	};
	Node unit[MAXN<<1];
	vector<int> V[MAXN<<1];
	inline void Init(void){
		for(reg int i=1;i<=tot;++i){
			dep(i)=link(i)=0;
			memset(next(i),0,sizeof(next(i)));
			V[i].clear();
		}
		tot=last=1;
		return;
	}
	inline void insert(reg int ch){
		reg int np=++tot,p=last;
		dep(np)=dep(p)+1;
		Siz(np)=1;
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
				Siz(nq)=0;
				while(p&&next(p)[ch]==q){
					next(p)[ch]=nq;
					p=link(p);
				}
				link(np)=link(q)=nq;
			}
		}
		last=np;
		return;
	}
	int tag[MAXN<<1];
	inline void DFS(reg int p,reg int k,reg int &Maxl){
		for(reg int i=0,size=V[p].size();i<size;++i){
			DFS(V[p][i],k,Maxl);
			Siz(p)+=Siz(V[p][i]);
		}
		if(Siz(p)==k)
			++tag[dep(p)],--tag[dep(link(p))];
		Maxl=max(Maxl,dep(p));
		return;
	}
	inline int Calc(reg int k){
		for(int i=2;i<=tot;++i)
			V[link(i)].push_back(i);
		int Maxl=0;
		DFS(1,k,Maxl);
		reg int res=-1,p=0,tim=0;
		for(reg int i=Maxl;i>=0;--i){
			p+=tag[i];
			tag[i]=0;
			if(p>tim)
				res=i,tim=p;
		}
		return res;
	}
}

using namespace SAM;

int T;
int n,K;
char str[MAXN];

int main(void){
	scanf("%d",&T);
	while(T--){
		Init();
		scanf("%s%d",str+1,&K);
		n=strlen(str+1);
		for(reg int i=1;i<=n;++i)
			insert(str[i]-'a');
		reg int ans=Calc(K);
		printf("%d\n",ans);
	}
	return 0;
}
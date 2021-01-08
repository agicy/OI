#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXSIZE=250000+5;

char S1[MAXSIZE],S2[MAXSIZE];

namespace SAM{
	int tot,last;
	struct Node{
		int dep,link;
		int next[26];
		#define dep(x) unit[(x)].dep
		#define link(x) unit[(x)].link
		#define next(x) unit[(x)].next
	};
	Node unit[MAXSIZE<<1];
	inline void Init(void){
		tot=last=1;
		return;
	}
	inline void insert(reg int ch){
		reg int np=++tot,p=last;
		dep(np)=dep(p)+1;
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
		return;
	}
	inline void Calc(reg int &ans,reg char str[],reg int len){
		reg int p=1;
		int cnt=0;
		for(reg int i=1;i<=len;++i){
			if(next(p)[str[i]-'a']){
				++cnt;
				p=next(p)[str[i]-'a'];
			}
			else{
				while(p&&next(p)[str[i]-'a']==0)
					p=link(p);
				if(p){
					cnt=dep(p)+1;
					p=next(p)[str[i]-'a'];
				}
				else
					cnt=0,p=1;
			}
			ans=max(ans,cnt);
		}
		return;
	}
}

using namespace SAM;

int main(void){
	Init();
	scanf("%s%s",S1+1,S2+1);
	reg int len=strlen(S1+1);
	for(reg int i=1;i<=len;++i)
		insert(S1[i]-'a');
	int ans=0;
	Calc(ans,S2,strlen(S2+1));
	printf("%d\n",ans);
	return 0;
}
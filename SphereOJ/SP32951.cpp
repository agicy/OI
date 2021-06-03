#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;

const int MAXN=3e5+5;

ll f[MAXN<<1];

namespace SAM{
	struct Node{
		int fa,len;
		int nex[26];
		#define fa(x) unit[(x)].fa
		#define len(x) unit[(x)].len
		#define nex(x) unit[(x)].nex
	};
	Node unit[MAXN<<1];
	int tot,las;
	inline int getId(void){
		reg int p=++tot;
		memset(&unit[p],0,sizeof(Node));
		return p;
	}
	inline void Init(void){
		tot=0;
		las=getId();
		return;
	}
	inline void insert(reg int c){
		reg int np=getId(),p=las;
		len(np)=len(p)+1;
		while(p&&!nex(p)[c])
			nex(p)[c]=np,p=fa(p);
		if(!p)
			fa(np)=1;
		else{
			reg int q=nex(p)[c];
			if(len(p)+1==len(q))
				fa(np)=q;
			else{
				reg int nq=getId();
				unit[nq]=unit[q];
				len(nq)=len(p)+1;
				fa(np)=fa(q)=nq;
				while(p&&nex(p)[c]==q)
					nex(p)[c]=nq,p=fa(p);
			}
		}
		las=np;
		return;
	}
	inline ll dfs(reg int p){
		if(f[p]!=-1)
			return f[p];
		reg ll res=1;
		for(reg int i=0;i<26;++i)
			if(nex(p)[i])
				res+=dfs(nex(p)[i]);
		return f[p]=res;
	}
}

int main(void){
	SAM::Init();
	reg char ch=getchar();
	while(isalpha(ch)) SAM::insert(ch-'a'),ch=getchar();
	memset(f,-1,sizeof(f));
	SAM::dfs(1);
	for(reg int i=0;i<26;++i)
		printf("%lld%c",SAM::unit[1].nex[i]?f[SAM::unit[1].nex[i]]:0,i==26-1?'\n':' ');
	return 0;
}
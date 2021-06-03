#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

namespace SAM{
	struct Node{
		int fa,len;
		int nex[26];
		int Max,Min;
		#define fa(x) unit[(x)].fa
		#define len(x) unit[(x)].len
		#define nex(x) unit[(x)].nex
		#define Max(x) unit[(x)].Max
		#define Min(x) unit[(x)].Min
	};
	int tot,las;
	Node unit[MAXN<<1];
	inline void Init(void){
		tot=0;
		las=++tot;
		return;
	}
	inline void insert(reg int c){
		reg int np=++tot,p=las;
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
				reg int nq=++tot;
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
	int buc[MAXN<<1];
	int ord[MAXN<<1];
	inline void solve(reg int len){
		for(reg int i=1;i<=tot;++i)
			++buc[len(i)];
		for(reg int i=1;i<=len;++i)
			buc[i]+=buc[i-1];
		for(reg int i=1;i<=tot;++i)
			ord[buc[len(i)]--]=i;
		for(reg int i=1;i<=tot;++i)
			Min(i)=inf;
		return;
	}
	inline void dfs(reg char s[],reg int n){
		reg int p=1;
		for(reg int i=1;i<=tot;++i)
			Max(i)=0;
		reg int l=0;
		for(reg int i=0;i<n;++i){
			reg int c=s[i]-'a';
			while(p&&!nex(p)[c])
				p=fa(p);
			if(!p)
				p=1;
			else{
				l=min(l,len(p))+1;
				p=nex(p)[c];
				Max(p)=max(Max(p),l);
			}
		}
		for(reg int i=tot;i>=1;--i){
			reg int u=ord[i],f=fa(u);
			Max(f)=max(Max(f),min(Max(u),len(f)));
			Min(u)=min(Min(u),Max(u));
		}
		return;
	}
	#undef fa
	#undef len
	#undef nex
	#undef Max
	#undef Min
}

char s[MAXN];

int main(void){
	SAM::Init();
	scanf("%s",s);
	char* tmp=s;
	while(*tmp) SAM::insert(*(tmp++)-'a');
	SAM::solve(strlen(s));
	while(scanf("%s",s)!=EOF)
		SAM::dfs(s,strlen(s));
	reg int ans=0;
	for(reg int i=1;i<=SAM::tot;++i)
		ans=max(ans,SAM::unit[i].Min);
	printf("%d\n", ans);
	return 0;
}
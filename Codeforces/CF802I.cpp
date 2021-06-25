#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;

namespace SAM{
	struct Node{
		int fa,len;
		int ch[26];
		#define fa(x) unit[(x)].fa
		#define len(x) unit[(x)].len
		#define ch(x) unit[(x)].ch
	};
	int tot,last;
	Node unit[MAXN<<1];
	inline void init(void){
		for(reg int i=1;i<=tot;++i){
			len(i)=fa(i)=0;
			memset(ch(i),0,sizeof(ch(i)));
		}
		tot=last=1;
		return;
	}
	int size[MAXN<<1];
	inline void insert(reg int c){
		reg int np=++tot,p=last;
		len(np)=len(last)+1;
		while(p&&!ch(p)[c])
			ch(p)[c]=np,p=fa(p);
		if(!p)
			fa(np)=1;
		else{
			reg int q=ch(p)[c];
			if(len(p)+1==len(q))
				fa(np)=q;
			else{
				reg int nq=++tot;
				size[nq]=0;
				memcpy(ch(nq),ch(q),sizeof(ch(q)));
				fa(nq)=fa(q);
				len(nq)=len(p)+1;
				while(p&&ch(p)[c]==q)
					ch(p)[c]=nq,p=fa(p);
				fa(np)=fa(q)=nq;
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
			++c[len(i)];
		for(reg int i=1;i<=tot;++i)
			c[i]+=c[i-1];
		for(reg int i=tot;i>=1;--i)
			a[c[len(i)]--]=i;
		reg ll res=0;
		for(reg int i=tot;i>=1;--i){
			res+=1ll*(len(a[i])-len(fa(a[i])))*size[a[i]]*size[a[i]];
			size[fa(a[i])]+=size[a[i]];
		}
		return res;
	}
	#undef fa
	#undef len
	#undef ch
}

using namespace SAM;

int T;
char s[MAXN];

int main(void){
	scanf("%d",&T);
	while(T--){
		init();
		scanf("%s",s+1);
		reg int len=strlen(s+1);
		for(reg int i=1;i<=len;++i)
			insert(s[i]-'a');
		printf("%lld\n",Calc());
	}
	return 0;
}
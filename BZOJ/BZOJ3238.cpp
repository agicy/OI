#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline char* read(reg char* s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return s;
}

const int MAXN=5e5+5;

int n;
char s[MAXN];

namespace SAM{
	struct Node{
		int fa,len;
		int ch[26];
		int siz;
		#define ch(x) unit[(x)].ch
		#define fa(x) unit[(x)].fa
		#define len(x) unit[(x)].len
		#define siz(x) unit[(x)].siz
	};
	int tot,las;
	Node unit[MAXN<<1];
	inline void init(void){
		tot=las=1;
		return;
	}
	inline void insert(reg int c){
		reg int p=las,np=++tot;
		len(np)=len(p)+1;
		while(p&&!ch(p)[c])
			ch(p)[c]=np,p=fa(p);
		if(!p)
			fa(np)=1;
		else{
			reg int q=ch(p)[c];
			if(len(q)==len(p)+1)
				fa(np)=q;
			else{
				reg int nq=++tot;
				len(nq)=len(p)+1;
				memcpy(ch(nq),ch(q),sizeof(ch(q)));
				fa(nq)=fa(q),fa(q)=fa(np)=nq;
				while(ch(p)[c]==q)
					ch(p)[c]=nq,p=fa(p);
			}
		}
		siz(np)=1;
		las=np;
		return;
	}
	int T[MAXN<<1];
	int a[MAXN<<1];
	inline ll build(void){
		for(reg int i=1;i<=tot;++i)
			++T[len(i)];
		for(reg int i=1;i<=tot;++i)
			T[i]+=T[i-1];
		for(reg int i=1;i<=tot;++i)
			a[T[len(i)]--]=i;
		reg ll ans=0;
		for(reg int i=tot;i>=1;--i){
			reg int p=a[i];
			siz(fa(p))+=siz(p);
			ans+=1ll*(len(p)-len(fa(p)))*siz(p)*(n-siz(p));
		}
		return ans;
	}
	#undef fa
	#undef len
	#undef ch
	#undef siz
}

int main(void){
	n=read(s+1)-(s+1);
	SAM::init();
	for(reg int i=1;i<=n;++i)
		SAM::insert(s[i]-'a');
	printf("%lld\n",SAM::build());
	return 0;
}
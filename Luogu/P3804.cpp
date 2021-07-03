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

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=1e6+5;

int n;
char s[MAXN];

namespace SAM{
	const int MAXSIZE=MAXN<<1;
	const int lim=26;
	struct Node{
		int fa,len;
		int ch[lim];
		#define fa(x) unit[(x)].fa
		#define len(x) unit[(x)].len
		#define ch(x) unit[(x)].ch
	};
	int tot,las;
	Node unit[MAXSIZE];
	inline int getId(void){
		reg int p=++tot;
		//memset(&unit[p],0,sizeof(Node));
		return p;
	}
	inline void init(void){
		tot=0,las=getId();
		return;
	}
	int siz[MAXSIZE];
	inline void insert(reg int c){
		reg int np=getId(),p=las;
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
				reg int nq=getId();
				unit[nq]=unit[q];
				len(nq)=len(p)+1;
				fa(np)=fa(q)=nq;
				while(p&&ch(p)[c]==q)
					ch(p)[c]=nq,p=fa(p);
			}
		}
		siz[np]=1;
		las=np;
		return;
	}
	int cnt[MAXN],rnk[MAXSIZE];
	inline ll solve(void){
		for(reg int i=1;i<=tot;++i)
			++cnt[len(i)];
		for(reg int i=1;i<=n;++i)
			cnt[i]+=cnt[i-1];
		for(reg int i=1;i<=tot;++i)
			rnk[cnt[len(i)]--]=i;
		reg ll res=0;
		for(reg int i=tot;i>=1;--i){
			reg int u=rnk[i];
			siz[fa(u)]+=siz[u];
			if(siz[u]>1)
				res=max(res,1ll*siz[u]*len(u));
		}
		return res;
	}
}

int main(void){
	n=read(s)-s;
	SAM::init();
	for(reg int i=0;i<n;++i)
		SAM::insert(s[i]-'a');
	printf("%lld\n",SAM::solve());
	return 0;
}
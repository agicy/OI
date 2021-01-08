#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXS=2e5+5;

int n;
char s[MAXS],t[MAXS];

namespace SAM{
	struct Node{
		int ch[26];
		int fa,dep;
		int siz;
		#define ch(x) unit[(x)].ch
		#define fa(x) unit[(x)].fa
		#define dep(x) unit[(x)].dep
		#define siz(x) unit[(x)].siz
	};
	int tot,las;
	Node unit[MAXS<<1];
	inline void Init(void){
		tot=las=1;
		return;
	}
	inline void insert(reg int c){
		reg int p=las,np=++tot;
		dep(np)=dep(p)+1;
		siz(np)=1;
		while(p&&!ch(p)[c])
			ch(p)[c]=np,p=fa(p);
		if(!p)
			fa(np)=1;
		else{
			reg int q=ch(p)[c];
			if(dep(q)==dep(p)+1)
				fa(np)=q;
			else{
				reg int nq=++tot;
				dep(nq)=dep(p)+1;
				memcpy(ch(nq),ch(q),sizeof(ch(q)));
				fa(nq)=fa(q),fa(q)=fa(np)=nq;
				while(ch(p)[c]==q)
					ch(p)[c]=nq,p=fa(p);
			}
		}
		las=np;
		return;
	}
	int cnt[MAXS],a[MAXS<<1];
	ll dp[MAXS<<1];
	inline void solve(void){
		for(reg int i=1;i<=tot;++i)
			++cnt[dep(i)];
		for(reg int i=1;i<=n;++i)
			cnt[i]+=cnt[i-1];
		for(reg int i=tot;i>=1;--i)
			a[cnt[dep(i)]--]=i;
		for(reg int i=tot;i>=1;--i){
			reg int u=a[i];
			siz(fa(u))+=siz(u);
		}
		for(reg int i=2;i<=tot;++i){
			reg int u=a[i];
			dp[u]=1ll*(dep(u)-dep(fa(u)))*siz(u)+dp[fa(u)];
		}
		return;
	}
	inline ll trans(reg char s[],reg int len){
		reg int p=1;
		int cnt=0;
		reg ll res=0;
		for(reg int i=1;i<=len;++i){
			reg int c=s[i]-'a';
			while(p&&!ch(p)[c])
				p=fa(p);
			if(!p)
				p=1,cnt=0;
			else{
				cnt=min(cnt,dep(p))+1;
				p=ch(p)[c];
				res+=dp[fa(p)]+1ll*(cnt-dep(fa(p)))*siz(p);
			}
		}
		return res;
	}
}

int main(void){
	read(s+1);
	n=strlen(s+1);
	SAM::Init();
	for(reg int i=1;i<=n;++i)
		SAM::insert(s[i]-'a');
	SAM::solve();
	read(t+1);
	printf("%lld\n",SAM::trans(t,strlen(t+1)));
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXS=3e5+5;

namespace PAM{
	struct Node{
		int ch[26];
		int fail,len;
		int s;
		int cnt;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define len(x) unit[(x)].len
		#define s(x) unit[(x)].s
		#define cnt(x) unit[(x)].cnt
	};
	int n,tot,las;
	Node unit[MAXS];
	inline int New(reg int l){
		len(tot)=l;
		return tot++;
	}
	inline void Init(void){
		New(0),fail(0)=New(-1);
		s(0)=-1;
		return;
	}
	inline int getFail(reg int p){
		while(s(n-len(p)-1)!=s(n))
			p=fail(p);
		return p;
	}
	inline int insert(reg char ch){
		reg int c=ch-'a';
		s(++n)=c;
		reg int u=getFail(las);
		if(!ch(u)[c]){
			reg int p=New(len(u)+2);
			fail(p)=ch(getFail(fail(u)))[c];
			ch(u)[c]=p;
		}
		las=ch(u)[c];
		++cnt(las);
		return las;
	}
	inline ll solve(void){
		for(reg int i=tot-1;i>=0;--i)
			cnt(fail(i))+=cnt(i);
		ll ans=0;
		for(reg int i=tot-1;i>=0;--i)
			ans=max(ans,1ll*cnt(i)*len(i));
		return ans;
	}
}

char s[MAXS];

int main(void){
	read(s+1);
	PAM::Init();
	reg int n=strlen(s+1);
	for(reg int i=1;i<=n;++i)
		PAM::insert(s[i]);
	printf("%lld\n",PAM::solve());
	return 0;
}
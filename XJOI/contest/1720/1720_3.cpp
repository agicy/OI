#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int MAXQ=1e5+5;

int n,q;
char s[MAXN+MAXQ];
char ad[MAXQ];

namespace Subtask1{
	const int MAXN=2e3+5;
	const int MAXQ=2e3+5;
	const int base=1331;
	const int mod=1e9+7;
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=mod?a-mod:a;
	}
	inline int sub(reg int a,reg int b){
		a-=b;
		return a<0?a+mod:a;
	}
	int basep[MAXN+MAXQ],Hash[2][MAXN+MAXQ];
	inline int getHash(reg int id,reg int l,reg int r){
		if(id)
			return sub(Hash[id][l],1ll*Hash[id][r+1]*basep[r-l+1]%mod);
		else
			return sub(Hash[id][r],1ll*Hash[id][l-1]*basep[r-l+1]%mod);
	}
	inline void Solve(void){
		basep[0]=1;
		for(reg int i=1;i<=n+q;++i)
			basep[i]=1ll*basep[i-1]*base%mod;
		for(reg int i=1;i<=n;++i)
			Hash[0][i]=add(1ll*Hash[0][i-1]*base%mod,s[i]-'a'+1);
		for(reg int i=n;i>=1;--i)
			Hash[1][i]=add(1ll*Hash[1][i+1]*base%mod,s[i]-'a'+1);
		set<int> S;
		reg int ans=0;
		for(reg int i=1;i<=n;++i)
			for(reg int j=i;j<=n;++j){
				reg int v=1ll*getHash(0,i,j)*getHash(1,i,j)%mod;
				if(S.find(v)==S.end())
					++ans,S.insert(v);
			}
		writeln(ans);
		reg int tot=n;
		for(reg int i=1;i<=q;++i){
			s[++tot]=ad[i];
			for(reg int j=1;j<=tot;++j)
				Hash[0][j]=add(1ll*Hash[0][j-1]*base%mod,s[j]-'a'+1);
			for(reg int j=tot;j>=1;--j)
				Hash[1][j]=add(1ll*Hash[1][j+1]*base%mod,s[j]-'a'+1);
			for(reg int j=1;j<=tot;++j){
				reg int v=1ll*getHash(0,j,tot)*getHash(1,j,tot)%mod;
				if(S.find(v)==S.end())
					++ans,S.insert(v);
			}
			writeln(ans);
		}
		return;
	}
}

namespace Subtask3check{
	inline bool Solve(void){
		for(reg int i=1;i<=n;++i)
			if(s[i]!='a')
				return false;
		for(reg int i=1;i<=q;++i)
			if(ad[i]!='a')
				return false;
		return true;
	}
}

namespace Subtask3{
	inline void Solve(void){
		writeln(n);
		for(reg int i=1;i<=q;++i)
			writeln(n+i);
		return;
	}
}

int main(void){
	n=read(),q=read();
	read(s+1);
	for(reg int i=1;i<=q;++i)
		do
			ad[i]=getchar();
		while(!isalpha(ad[i]));
	if(n<=2e3&&q<=2e3)
		Subtask1::Solve();
	else if(Subtask3check::Solve())
		Subtask3::Solve();
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}
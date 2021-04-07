#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(str) (wp1==wp2&&(flush(),0),wbuf[wp1++]=str)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=2e6+5;

namespace PAM{
	struct Node{
		int ch[26];
		int fail,len,cnt;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define len(x) unit[(x)].len
		#define cnt(x) unit[(x)].cnt
	};
	int tot,las;
	int pos;
	Node unit[MAXN];
	int s[MAXN];
	inline void Init(void){
		len(0)=0,len(1)=-1;
		fail(0)=1,fail(1)=0;
		las=0;
		tot=1;
		return;
	}
	inline int getFail(reg int p){
		while(s[pos-len(p)-1]!=s[pos])
			p=fail(p);
		return p;
	}
	inline void insert(void){
		reg int p=getFail(las);
		if(!ch(p)[s[pos]]){
			reg int v=++tot;
			len(v)=len(p)+2;
			fail(v)=ch(getFail(fail(p)))[s[pos]];
			cnt(v)=cnt(fail(v))+1;
			ch(p)[s[pos]]=v;
		}
		las=ch(p)[s[pos]];
		return;
	}
	inline void solve(void){
		static char str[MAXN];
		read(str+1);
		reg int len=strlen(str+1);
		reg int lastans=0;
		s[0]=26;
		for(pos=1;pos<=len;++pos){
			str[pos]=(str[pos]-97+lastans)%26+97;
			s[pos]=str[pos]-'a';
			insert();
			write(cnt(las)),putchar(pos==len?'\n':' ');
			lastans=cnt(las);
		}
		return;
	}
}

int main(void){
	PAM::Init();
	PAM::solve();
	flush();
	return 0;
}
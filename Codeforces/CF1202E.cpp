#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline char* read(reg char* s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return s;
}

const int MAXT=2e5+5;
const int MAXS=2e5+5;

namespace AC{
	const int lim=26;
	struct Node{
		int ch[lim];
		int fail;
		int sum;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXS];
	inline void init(void){
		tot=1;
		return;
	}
	inline void insert(reg char s[],reg int len){
		reg int p=1;
		for(reg int i=0;i<len;++i){
			reg int c=s[i]-'a';
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		++sum(p);
		return;
	}
	inline void build(void){
		fail(1)=1;
		reg int _head=0,_tail=0;
		static int Q[MAXS];
		for(reg int i=0;i<lim;++i)
			if(ch(1)[i])
				fail(ch(1)[i])=1,Q[_tail++]=ch(1)[i];
			else
				ch(1)[i]=1;
		while(_head<_tail){
			reg int u=Q[_head++];
			for(reg int i=0;i<lim;++i)
				if(ch(u)[i])
					fail(ch(u)[i])=ch(fail(u))[i],sum(ch(u)[i])+=sum(fail(ch(u)[i])),Q[_tail++]=ch(u)[i];
				else
					ch(u)[i]=ch(fail(u))[i];
		}
		return;
	}
	inline void query(reg char s[],reg int len,reg int res[]){
		reg int p=1;
		for(reg int i=0;i<len;++i){
			p=ch(p)[s[i]-'a'];
			res[i]=sum(p);
		}
		return;
	}
}

namespace rAC{
	const int lim=26;
	struct Node{
		int ch[lim];
		int fail;
		int sum;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXS];
	inline void init(void){
		tot=1;
		return;
	}
	inline void insert(reg char s[],reg int len){
		reg int p=1;
		for(reg int i=0;i<len;++i){
			reg int c=s[i]-'a';
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		++sum(p);
		return;
	}
	inline void build(void){
		fail(1)=1;
		reg int _head=0,_tail=0;
		static int Q[MAXS];
		for(reg int i=0;i<lim;++i)
			if(ch(1)[i])
				fail(ch(1)[i])=1,Q[_tail++]=ch(1)[i];
			else
				ch(1)[i]=1;
		while(_head<_tail){
			reg int u=Q[_head++];
			for(reg int i=0;i<lim;++i)
				if(ch(u)[i])
					fail(ch(u)[i])=ch(fail(u))[i],sum(ch(u)[i])+=sum(fail(ch(u)[i])),Q[_tail++]=ch(u)[i];
				else
					ch(u)[i]=ch(fail(u))[i];
		}
		return;
	}
	inline void query(reg char s[],reg int len,reg int res[]){
		reg int p=1;
		for(reg int i=0;i<len;++i){
			p=ch(p)[s[i]-'a'];
			res[i]=sum(p);
		}
		return;
	}
}

char t[MAXT];
int res1[MAXT],res2[MAXT];

bool ed;

int main(void){
	reg int tLen=read(t)-t;
	reg int n=read();
	AC::init(),rAC::init();
	while(n--){
		static char s[MAXS];
		reg int len=read(s)-s;
		AC::insert(s,len);
		reverse(s,s+len);
		rAC::insert(s,len);
	}
	AC::build(),rAC::build();
	AC::query(t,tLen,res1);
	reverse(t,t+tLen);
	rAC::query(t,tLen,res2);
	reg ll ans=0;
	for(reg int i=0;i<tLen-1;++i)
		ans+=1ll*res1[i]*res2[tLen-i-2];
	printf("%lld\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}
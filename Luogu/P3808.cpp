#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline char* read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	return s;
}

const int MAXS=1e6+5;
const int MAXT=1e6+5;

namespace AC{
	const int MAXSIZE=5e6+5;
	struct Node{
		int ch[26],fail,val;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define val(x) unit[(x)].val
	};
	int tot;
	Node unit[MAXSIZE];
	inline void insert(reg char s[],reg int len){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=s[i]-'a';
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		++val(p);
		return;
	}
	queue<int> Q;
	inline void build(void){
		for(reg int i=0;i<26;++i)
			if(ch(0)[i])
				fail(ch(0)[i])=0,Q.push(ch(0)[i]);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=0;i<26;++i)
				if(ch(u)[i])
					fail(ch(u)[i])=ch(fail(u))[i],Q.push(ch(u)[i]);
				else
					ch(u)[i]=ch(fail(u))[i];
		}
		return;
	}
	inline int query(reg char str[],reg int len){
		reg int p=0;
		reg int res=0;
		for(reg int i=0;i<len;++i){
			reg int c=str[i]-'a';
			p=ch(p)[c];
			for(reg int j=p;j&&(~val(j));j=fail(j)){
				res+=val(j);
				val(j)=-1;
			}
		}
		return res;
	}
}

int main(void){
	reg int n=read();
	while(n--){
		static char s[MAXS];
		reg int len=read(s)-s;
		AC::insert(s,len);
	}
	AC::build();
	static char t[MAXT];
	reg int len=read(t)-t;
	printf("%d\n",AC::query(t,len));
	return 0;
}
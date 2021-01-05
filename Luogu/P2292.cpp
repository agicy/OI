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

const int MAXS=200+5;
const int MAXT=2e6+5;

namespace AC{
	struct Node{
		int ch[26];
		bool tag;
		int fail;
		int dep;
		int mat;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define dep(x) unit[(x)].dep
		#define tag(x) unit[(x)].tag
		#define mat(x) unit[(x)].mat
	};
	int tot;
	Node unit[MAXS];
	inline void insert(reg char s[],reg int len){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=s[i]-'a';
			if(!ch(p)[c])
				ch(p)[c]=++tot,dep(ch(p)[c])=dep(p)+1;
			p=ch(p)[c];
		}
		tag(p)=true;
		return;
	}
	int Q[MAXS];
	inline void build(void){
		reg int head=0,tail=0;
		for(reg int i=0;i<26;++i)
			if(ch(0)[i])
				Q[tail++]=ch(0)[i];
		while(head<tail){
			reg int u=Q[head++];
			mat(u)=mat(fail(u))|(tag(u)<<dep(u));
			for(reg int i=0;i<26;++i)
				if(ch(u)[i])
					fail(ch(u)[i])=ch(fail(u))[i],Q[tail++]=ch(u)[i];
				else
					ch(u)[i]=ch(fail(u))[i];
		}
		return;
	}
}

int n,m;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		static char s[MAXS];
		read(s);
		AC::insert(s,strlen(s));
	}
	AC::build();
	while(m--){
		static char t[MAXT];
		read(t+1);
		reg int len=strlen(t+1);
		reg int ans=0;
		for(reg int i=1,p=0,tmp=1;i<=len;++i){
			reg int c=t[i]-'a';
			p=AC::ch(p)[c];
			if(AC::mat(p)&(tmp<<=1)){
				tmp|=1;
				ans=i;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
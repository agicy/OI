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

const int MAXN=2e5+5;
const int MAXS=2e6+5;
const int MAXT=2e5+5;

int n;
char s[MAXS];

namespace AC{
	struct Node{
		int ch[26],fail;
		int siz;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define siz(x) unit[(x)].siz
	};
	int tot;
	Node unit[MAXT];
	inline int insert(reg char s[],reg int len){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=s[i]-'a';
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		return p;
	}
	int cnt,head[MAXT],to[MAXT],Next[MAXT];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void build(void){
		queue<int> Q;
		for(reg int i=0;i<26;++i)
			if(ch(0)[i])
				Q.push(ch(0)[i]);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=0;i<26;++i)
				if(ch(u)[i])
					fail(ch(u)[i])=ch(fail(u))[i],Q.push(ch(u)[i]);
				else
					ch(u)[i]=ch(fail(u))[i];
		}
		for(reg int i=1;i<=tot;++i)
			Add_Edge(fail(i),i);
		return;
	}
	inline void query(reg char s[],reg int len){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=s[i]-'a';
			p=ch(p)[c];
			++siz(p);
		}
		return;
	}
	inline void dfs(reg int u){
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			dfs(v);
			siz(u)+=siz(v);
		}
		return;
	}
}

int mat[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static char t[MAXT];
		read(t);
		mat[i]=AC::insert(t,strlen(t));
	}
	AC::build();
	read(s);
	AC::query(s,strlen(s));
	AC::dfs(0);
	for(reg int i=1;i<=n;++i)
		printf("%d\n",AC::siz(mat[i]));
	return 0;
}
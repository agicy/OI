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
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXS=3e4+5;

namespace AC{
	struct Node{
		int ch[2],fail;
		bool tag;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define tag(x) unit[(x)].tag
	};
	int tot;
	Node unit[MAXS];
	inline void insert(reg char str[],reg int len){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=(str[i]^'0');
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		tag(p)=true;
		return;
	}
	inline void build(void){
		queue<int> Q;
		for(reg int i=0;i<2;++i)
			if(ch(0)[i])
				Q.push(ch(0)[i]);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=0;i<2;++i)
				if(ch(u)[i]){
					fail(ch(u)[i])=ch(fail(u))[i];
					tag(ch(u)[i])|=tag(fail(ch(u)[i]));
					Q.push(ch(u)[i]);
				}
				else
					ch(u)[i]=ch(fail(u))[i];
		}
		return;
	}
	bool ins[MAXS],vis[MAXS];
	inline bool dfs(reg int u){
		ins[u]=true;
		for(reg int i=0;i<2;++i){
			reg int v=ch(u)[i];
			if(ins[v])
				return true;
			if(vis[v]||tag(v))
				continue;
			vis[v]=true;
			if(dfs(v))
				return true;
		}
		ins[u]=false;
		return false;
	}
}

int main(void){
	reg int n=read();
	for(reg int i=1;i<=n;++i){
		static char str[MAXS];
		read(str);
		AC::insert(str,strlen(str));
	}
	AC::build();
	if(AC::dfs(0))
		puts("TAK");
	else
		puts("NIE");
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++)
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

const int MAXN=1e6+5;
const int MAXK=1e6+5;
const int MAXS=1e6+5;

namespace AC{
	const int MAXSIZE=MAXS;
	struct Node{
		int ch[26];
		int fail;
		int cnt;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define cnt(x) unit[(x)].cnt
	};
	int tot;
	Node unit[MAXSIZE];
	inline int insert(reg char str[],reg int len){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=str[i]-'A';
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		return p;
	}
	vector<int> G[MAXSIZE];
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
		for(int i=1;i<=tot;++i)
			G[fail(i)].push_back(i);
		return;
	}
	inline void dfs(reg int u){
		for(vector<int>::iterator it=G[u].begin();it!=G[u].end();++it){
			reg int v=*it;
			dfs(v);
			cnt(u)+=cnt(v);
		}
		return;
	}
}

int n,k;
int mat[MAXK];
int ch[MAXN][26];

inline void dfs(reg int x,reg int y){
	++AC::cnt(y);
	for(reg int i=0;i<26;++i)
		if(ch[x][i])
			dfs(ch[x][i],AC::ch(y)[i]);
	return;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i){
		static char c;
		static int p;
		do
			c=getchar();
		while(!isalpha(c));
		p=read();
		ch[p][c-'A']=i;
	}
	for(reg int i=1;i<=k;++i){
		static char str[MAXS];
		read(str);
		reg int len=strlen(str);
		reverse(str,str+len);
		mat[i]=AC::insert(str,len);
	}
	AC::build();
	dfs(0,0);
	AC::dfs(0);
	for(reg int i=1;i<=k;++i)
		printf("%d\n",AC::cnt(mat[i]));
	return 0;
}
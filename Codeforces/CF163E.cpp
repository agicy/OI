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

const int MAXS=1e6+5;
const int MAXK=1e5+5;
const int MAXSIZE=MAXS;

int n;
int mat[MAXK];
bool vis[MAXK];
vector<int> G[MAXSIZE];

inline void Add_Edge(reg int u,int v){
	G[u].push_back(v);
	return;
}

int tim,lef[MAXSIZE],rig[MAXSIZE];

inline void dfs(reg int u){
	lef[u]=++tim;
	for(int v:G[u])
		dfs(v);
	rig[u]=tim;
	return;
}

namespace AC{
	struct Node{
		int ch[26];
		int fail;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
	};
	int tot;
	Node unit[MAXSIZE];
	inline int insert(reg char str[],reg int len){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=str[i]-'a';
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		return p;
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
		dfs(0);
		return;
	}
}

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXSIZE];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline void update(reg int l,reg int r,reg int val){
		update(l,val),update(r+1,-val);
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

int main(void){
	reg int T=read();
	n=read();
	for(reg int i=1;i<=n;++i){
		static char str[MAXS];
		read(str);
		mat[i]=AC::insert(str,strlen(str));
	}
	AC::build();
	BIT::Init(tim);
	for(reg int i=1;i<=n;++i){
		vis[i]=true;
		BIT::update(lef[mat[i]],rig[mat[i]],1);
	}
	while(T--){
		static char opt;
		static int k;
		do
			opt=getchar();
		while(opt!='?'&&opt!='-'&&opt!='+');
		switch(opt){
			case '+':{
				k=read();
				if(!vis[k]){
					vis[k]=true;
					BIT::update(lef[mat[k]],rig[mat[k]],1);
				}
				break;
			}
			case '-':{
				k=read();
				if(vis[k]){
					vis[k]=false;
					BIT::update(lef[mat[k]],rig[mat[k]],-1);
				}
				break;
			}
			case '?':{
				static char str[MAXS];
				read(str);
				reg int p=0,res=0;
				for(reg int i=0,len=strlen(str);i<len;++i){
					reg int c=str[i]-'a';
					p=AC::ch(p)[c];
					res+=BIT::query(lef[p]);
				}
				printf("%d\n",res);
				break;
			}
		}
	}
	return 0;
}
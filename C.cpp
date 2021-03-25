#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=200+5;
const int MAXS=200+5;
const int inf=0x3f3f3f3f;

int n;
char s[MAXN][MAXS];
int len[MAXN];

namespace Subtask1{
	const int MAXN=4+5;
	bool vis[MAXN];
	int p[MAXN];
	int ans=inf;
	struct Node{
		int ch[26];
		inline void Init(void){
			memset(ch,0,sizeof(ch));
			return;
		}
	};
	int tot;
	Node unit[MAXN*MAXS];
	inline int New(void){
		reg int p=++tot;
		unit[p].Init();
		return p;
	}
	inline int check(void){
		tot=0;
		New();
		for(reg int i=1;i<=n;++i){
			reg int Max=-1,pos=-1;
			for(reg int l=1;l<=tot;++l){
				reg int k=l,cnt=0;
				for(reg int j=1;j<=len[p[i]];++j){
					reg int c=s[p[i]][j]-'a';
					if(!unit[k].ch[c])
						break;
					++cnt,k=unit[k].ch[c];
				}
				if(cnt>Max)
					Max=cnt,pos=l;
			}
			reg int k=pos;
			for(reg int j=1;j<=len[p[i]];++j){
				reg int c=s[p[i]][j]-'a';
					if(!unit[k].ch[c])
					unit[k].ch[c]=New();
				k=unit[k].ch[c];
			}
		}
		return tot;
	}
	inline void dfs(reg int dep){
		if(dep==n+1){
			reg int res=check();
			if(res<ans)
				ans=res;
			return;
		}
		for(reg int i=1;i<=n;++i)
			if(!vis[i]){
				vis[i]=true;
				p[dep]=i;
				dfs(dep+1);
				vis[i]=false;
			}
		return;
	}
	inline void Solve(void){
		dfs(1);
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask2{
	int p[MAXN];
	int ans=inf;
	struct Node{
		int ch[26];
		inline void Init(void){
			memset(ch,0,sizeof(ch));
			return;
		}
	};
	int tot;
	Node unit[MAXN*MAXS];
	inline int New(void){
		reg int p=++tot;
		unit[p].Init();
		return p;
	}
	inline int check(void){
		tot=0;
		New();
		for(reg int i=1;i<=n;++i){
			reg int Max=-1,pos=-1;
			for(reg int l=1;l<=tot;++l){
				reg int k=l,cnt=0;
				for(reg int j=1;j<=len[p[i]];++j){
					reg int c=s[p[i]][j]-'a';
					if(!unit[k].ch[c])
						break;
					++cnt,k=unit[k].ch[c];
				}
				if(cnt>Max)
					Max=cnt,pos=l;
			}
			reg int k=pos;
			for(reg int j=1;j<=len[p[i]];++j){
				reg int c=s[p[i]][j]-'a';
					if(!unit[k].ch[c])
					unit[k].ch[c]=New();
				k=unit[k].ch[c];
			}
		}
		return tot;
	}
	inline void Solve(void){
		for(reg int i=1;i<=n;++i)
			p[i]=i;
		reg clock_t st=clock();
		reg int cnt=0;
		while(true){
			++cnt;
			random_shuffle(p+1,p+n+1);
			reg int res=check();
			if(res<ans)
				ans=res;
			if(clock()-st>0.8*CLOCKS_PER_SEC)
				break;
		}
		printf("%d\n",ans);
		return;
	}
}

int main(void){
	n=read();
	reg int S=0;
	for(reg int i=1;i<=n;++i){
		read(s[i]+1);
		len[i]=strlen(s[i]+1);
		for(reg int j=1;j<=len[i];++j)
			S=max(S,s[i][j]-'a'+1);
	}
	if(n<=4)
		Subtask1::Solve();
	else
		Subtask2::Solve();
	return 0;
}
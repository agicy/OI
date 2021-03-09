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
	while(!isdigit(*s)&&*s!='.')*s=getchar();
	while(isdigit(*s)||*s=='.')*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=7+5;

int n;
char M[MAXN][MAXN];
int cnt[MAXN][MAXN];

namespace UnionFind{
	int fa[MAXN*MAXN],siz[MAXN*MAXN];
	inline void Init(reg int n){
		for(reg int i=0;i<n;++i)
			fa[i]=i,siz[i]=1;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return find(fa[x]);
	}
	struct Event{
		int a,b;
		inline Event(reg int a=0,reg int b=0):a(a),b(b){
			return;
		}
	};
	int top;
	Event S[MAXN*MAXN];
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(siz[ra]<siz[rb]){
			fa[ra]=rb;
			siz[rb]+=siz[ra];
			S[++top]=Event(rb,ra);
		}
		else{
			fa[rb]=ra;
			siz[ra]+=siz[rb];
			S[++top]=Event(ra,rb);
		}
		return;
	}
	inline void undo(void){
		Event tmp=S[top--];
		siz[tmp.a]-=siz[tmp.b];
		fa[tmp.b]=tmp.b;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

inline int getId(reg int i,reg int j){
	return i*(n+1)+j;
}

char ans[MAXN][MAXN];

inline void print(void){
	for(reg int i=0;i<n;++i,putchar('\n'))
		for(reg int j=0;j<n;++j)
			putchar(ans[i][j]);
	return;
}

inline bool check(void){
	for(reg int i=0;i<=n;++i)
		for(reg int j=0;j<=n;++j)
			if(isdigit(M[i][j])&&(M[i][j]^'0')!=cnt[i][j])
				return false;
	return true;
}

inline bool check(reg int x,reg int y){
	return !isdigit(M[x][y])||cnt[x][y]<(M[x][y]^'0');
}

inline bool check1(reg int x,reg int y){
	return (!isdigit(M[x][y])||((M[x][y]^'0')-cnt[x][y]==1))
	&&     (!isdigit(M[x+1][y+1])||((M[x+1][y+1]^'0')>cnt[x+1][y+1]))
	&&     (!isdigit(M[x][y+1])||((M[x][y+1]^'0')-cnt[x][y+1]<=1));
}

inline bool check2(reg int x,reg int y){
	return (!isdigit(M[x][y])||((M[x][y]^'0')==cnt[x][y]))
	&&     (!isdigit(M[x][y+1])||(cnt[x][y+1]<(M[x][y+1]^'0')&&(M[x][y+1]^'0')-cnt[x][y+1]<=2))
	&&     (!isdigit(M[x+1][y])||cnt[x+1][y]<(M[x+1][y]^'0'))
	&&     !UnionFind::search(getId(x,y+1),getId(x+1,y));

}

inline bool dfs(reg int x,reg int y){
	if(x==n){
		if(check()){
			print();
			return true;
		}
		else
			return false;
	}
	if(check1(x,y)){
		reg bool flag=false;
		ans[x][y]='\\';
		++cnt[x][y],++cnt[x+1][y+1];
		UnionFind::merge(getId(x,y),getId(x+1,y+1));
		if(y==n-1)
			flag=dfs(x+1,0);
		else
			flag=dfs(x,y+1);
		--cnt[x][y],--cnt[x+1][y+1];
		UnionFind::undo();
		if(flag)
			return true;
	}
	if(check2(x,y)){
		reg bool flag=false;
		ans[x][y]='/';
		++cnt[x][y+1],++cnt[x+1][y];
		UnionFind::merge(getId(x,y+1),getId(x+1,y));
		if(y==n-1)
			flag=dfs(x+1,0);
		else
			flag=dfs(x,y+1);
		--cnt[x][y+1],--cnt[x+1][y];
		UnionFind::undo();
		if(flag)
			return true;
	}
	return false;
}

int main(void){
	n=read();
	for(reg int i=0;i<=n;++i)
		read(M[i]);
	UnionFind::Init((n+1)*(n+1));
	dfs(0,0);
	return 0;
}
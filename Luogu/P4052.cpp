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

const int MAXM=100+5;
const int MAXS=6e3+5;
const int p=1e4+7;

namespace AC{
	struct Node{
		int ch[26];
		int fail;
		bool tag;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define tag(x) unit[(x)].tag
	};
	int tot;
	Node unit[MAXS];
	inline void insert(reg char s[],reg int len){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=s[i]-'A';
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		tag(p)=true;
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
					fail(ch(u)[i])=ch(fail(u))[i],tag(ch(u)[i])|=tag(fail(ch(u)[i])),Q.push(ch(u)[i]);
				else
					ch(u)[i]=ch(fail(u))[i];
		}
		return;
	}
}

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

int n,m;
int dp[MAXM][MAXS];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		static char s[MAXS];
		read(s);
		AC::insert(s,strlen(s));
	}
	AC::build();
	dp[0][0]=1;
	for(reg int i=0;i<m;++i)
		for(reg int j=0;j<=AC::tot;++j)
			for(reg int k=0;k<26;++k)
				if(!AC::tag(AC::ch(j)[k]))
					dp[i+1][AC::ch(j)[k]]=add(dp[i+1][AC::ch(j)[k]],dp[i][j]);
	reg int ans=fpow(26,m);
	for(reg int i=0;i<=AC::tot;++i)
		ans=add(ans,p-dp[m][i]);
	printf("%d\n",ans);
	return 0;
}
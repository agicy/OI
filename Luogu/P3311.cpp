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

const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

const int MAXN=1201+5;
const int MAXS=1500+5;

char n[MAXN];
int len;
int m;

namespace AC{
	const int MAXSIZE=MAXS*50;
	struct Node{
		int ch[10];
		int fail;
		bool tag;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define tag(x) unit[(x)].tag
	};
	int tot;
	Node unit[MAXSIZE];
	inline void insert(reg char str[],reg int len){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=str[i]-'0';
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		tag(p)=true;
		return;
	}
	queue<int> Q;
	inline void build(void){
		for(reg int i=0;i<10;++i)
			if(ch(0)[i])
				Q.push(ch(0)[i]);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			tag(u)=tag(u)||tag(fail(u));
			for(reg int i=0;i<10;++i)
				if(ch(u)[i])
					fail(ch(u)[i])=ch(fail(u))[i],Q.push(ch(u)[i]);
				else
					ch(u)[i]=ch(fail(u))[i];
		}
		return;
	}
	int f[2][MAXSIZE][2];
	inline int dp(void){
		reg int ptr=0;
		for(reg int i=1;i<=n[0]-'0';++i)
			if(!tag(ch(0)[i]))
				++f[ptr][ch(0)[i]][i==n[0]-'0'];
		for(reg int i=1;i<len;++i,ptr^=1){
			memset(f[ptr^1],0,sizeof(f[ptr^1]));
			for(reg int j=1;j<10;++j)
				if(!tag(ch(0)[j]))
					++f[ptr^1][ch(0)[j]][0];
			for(reg int j=0;j<=tot;++j)
				if(!tag(j)){
					if(f[ptr][j][0])
						for(reg int p=0;p<10;++p)
							if(!tag(ch(j)[p]))
								f[ptr^1][ch(j)[p]][0]=add(f[ptr^1][ch(j)[p]][0],f[ptr][j][0]);
					if(f[ptr][j][1])
						for(reg int p=0;p<n[i]-'0';++p)
							if(!tag(ch(j)[p]))
								f[ptr^1][ch(j)[p]][0]=add(f[ptr^1][ch(j)[p]][0],f[ptr][j][1]);
					if(!tag(ch(j)[n[i]-'0'])){
						f[ptr^1][ch(j)[n[i]-'0']][1]=add(f[ptr^1][ch(j)[n[i]-'0']][1],f[ptr][j][1]);
					}
				}
		}
		reg int res=0;
		for(reg int i=0;i<=tot;++i)
			if(!tag(i))
				res=add(res,add(f[ptr][i][0],f[ptr][i][1]));
		return res;
	}
}

int main(void){
	read(n),m=read();
	len=strlen(n);
	for(reg int i=1;i<=m;++i){
		static char s[MAXS];
		read(s);
		AC::insert(s,strlen(s));
	}
	AC::build();
	printf("%d\n",AC::dp());
	return 0;
}
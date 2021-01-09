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

const int MAXN=1e5+5;

bool vis[MAXN];
int tot,prime[MAXN];
int from[MAXN];
int rnk[MAXN];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			rnk[i]=tot;
			from[i]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			from[i*prime[j]]=prime[j];
			if(!(i%prime[j]))
				break;
		}
	}
	return;
}

bool flg[MAXN];
set<int> S[MAXN];

inline void setup(int id){
	if(flg[id]){
		puts("Already on");
		return;
	}
	reg int tmp=id;
	while(tmp!=1){
		reg int x=from[tmp];
		if(!S[rnk[x]].empty()){
			printf("Conflict with %d\n",*S[rnk[x]].begin());
			return;
		}
		while(tmp%x==0)
			tmp/=x;
	}
	tmp=id;
	flg[id]=true;
	while(tmp!=1){
		reg int x=from[tmp];
		S[rnk[x]].insert(id);
		while(tmp%x==0)
			tmp/=x;
	}
	puts("Success");
	return;
}

inline void shutdown(int id){
	if(!flg[id]){
		puts("Already off");
		return;
	}
	reg int tmp=id;
	while(tmp!=1){
		reg int x=from[tmp];
		S[rnk[x]].erase(S[rnk[x]].find(id));
		while(tmp%x==0)
			tmp/=x;
	}
	flg[id]=false;
	puts("Success");
	return;
}

int n,m;

int main(void){
	Init(1e5);
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static char opt;
		static int id;
		do
			opt=getchar();
		while(opt!='+'&&opt!='-');
		id=read();
		switch(opt){
			case '+':{
				setup(id);
				break;
			}
			case '-':{
				shutdown(id);
				break;
			}
		}
	}
	return 0;
}
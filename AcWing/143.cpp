#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1000000+5;

struct Trie{
	int tot;
	int ch[MAXN*32][2];
	inline void Init(void){
		tot=1;
		return;
	}
	inline void insert(reg int num){
		reg int ID=1;
		for(reg int i=30;i>=0;--i){
			reg int p=(num&(1<<i))?1:0;
			if(ch[ID][p]==0)
				ch[ID][p]=++tot;
			ID=ch[ID][p];
		}
		return;
	}
	inline int query(reg int num){
		reg int res=0,ID=1;
		for(reg int i=30;i>=0;--i){
			reg int p=(num&(1<<i))?1:0;
			if(ch[ID][p^1]){
				ID=ch[ID][p^1];
				res|=(1<<i);
			}
			else
				ID=ch[ID][p];
		}
		return res;
	}
};

int n;
Trie T;

int main(void){
	reg int ans=0;
	n=read();
	T.Init();
	for(reg int i=1;i<=n;++i){
		static int a;
		a=read();
		T.insert(a);
		ans=max((int)ans,T.query(a));
	}
	printf("%d\n",ans);
	return 0;
}

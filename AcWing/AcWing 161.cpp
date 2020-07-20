#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXN=10000+5;

struct Trie{
	int tot;
	int ch[MAXN*10][10];
	int end[MAXN*10];
	inline void Init(void){
		tot=1;
		memset(ch[0],0,sizeof(ch[0]));
		memset(end,0,sizeof(end));
		return;
	}
	inline void insert(reg char str[]){
		reg int ID=0,len=strlen(str);
		for(reg int i=0;i<len;++i){
			reg int p=str[i]-'0';
			if(ch[ID][p]==0){
				memset(ch[tot],0,sizeof(ch[tot]));
				ch[ID][p]=tot++;
			}
			ID=ch[ID][p];
			++end[ID];
		}
		return;
	}
	inline bool query(reg char str[]){
		reg int ID=0,len=strlen(str);
		for(reg int i=0;i<len;++i){
			reg int p=str[i]-'0';
			ID=ch[ID][p];
			if(end[ID]==1)
				return true;
		}
		return false;
	}
};

Trie T;

inline bool Work(void);

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		reg bool ans=Work();
		puts(ans?"YES":"NO");
	}
	return 0;
}

char str[MAXN][10+5];

inline bool Work(void){
	int n;
	reg bool flag=true;
	scanf("%d\n",&n);
	T.Init();
	for(reg int i=1;i<=n;++i){
		scanf("%s\n",str[i]);
		T.insert(str[i]);
	}
	for(reg int i=1;i<=n;++i)
		flag&=T.query(str[i]);
	return flag;
}

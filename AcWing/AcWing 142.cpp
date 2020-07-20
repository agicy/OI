#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXN=1000000+5;

struct Trie{
	int tot;
	int ch[MAXN][26];
	int cnt[MAXN];
	inline void Init(void){
		tot=1;
		//memset(ch,0,sizeof(ch));
		//memset(cnt,0,sizeof(cnt));
		return;
	}
	inline void insert(reg char str[]){
		reg int i,ID=1,len=strlen(str);
		for(i=0;i<len;++i){
			if(ch[ID][str[i]-'a']==0)
				ch[ID][str[i]-'a']=++tot;
			ID=ch[ID][str[i]-'a'];
		}
		++cnt[ID];
		return;
	}
	inline int query(reg char str[]){
		reg int i,ID=1,res=0,len=strlen(str);
		for(i=0;i<len;++i){
			ID=ch[ID][str[i]-'a'];
			if(ID==0)
				return res;
			res+=cnt[ID];
		}
		return res;
	}
};

int n,m;
char str[MAXN];
Trie T;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	scanf("%d%d\n",&n,&m);
	T.Init();
	for(reg int i=1;i<=n;++i){
		scanf("%s\n",str);
		T.insert(str);
	}
	return;
}

inline void Work(void){
	while(m--){
		scanf("%s\n",str);
		printf("%d\n",T.query(str));
	}
	return;
}

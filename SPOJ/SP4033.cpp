#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=10000+5;
const int MAXSIZE=10+5;

namespace Trie{
	int cnt;
	bool vis[MAXN*MAXSIZE];
	int ch[MAXN*MAXSIZE][MAXSIZE];
	inline void Clear(void){
		cnt=1;
		memset(vis,false,sizeof(vis));
		memset(ch,0,sizeof(ch));
		return;
	}
	inline bool insert(reg char str[]){
		reg bool flag=false;
		reg int i,ID=1,len=strlen(str);
		for(i=0;i<len;++i){
			int c=str[i]-'0';
			if(!ch[ID][c])
				ch[ID][c]=++cnt;
			else if(i==len-1)
				flag=true;
			ID=ch[ID][c];
			if(vis[ID])
				flag=true;
		}
		vis[ID]=true;
		return flag;
	}
}

using namespace Trie;

char str[16];
int T,n;

int main(void){
	reg bool ans;
	scanf("%d",&T);
	while(T--){
		ans=false;
		Clear();
		scanf("%d",&n);
		while(n--){
			scanf("%s",str);
			if(insert(str))
				ans=true;
		}
		puts(!ans?"YES":"NO");
	}
	return 0;
}
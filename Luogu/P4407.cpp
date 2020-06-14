#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=10000+5;

namespace Trie{
	const int MAXSIZE=10000*26*20;
	int tot;
	int ch[MAXSIZE][26];
	bool tag[MAXSIZE];
	inline void insert(reg char str[]){
		reg int ID=0;
		for(reg int i=0,len=strlen(str);i<len;++i){
			reg int c=str[i]-'a';
			if(!ch[ID][c])
				ch[ID][c]=++tot;
			ID=ch[ID][c];
		}
		tag[ID]=true;
		return;
	}
	bool flag;
	char *str;
	int len;
	bool vis[MAXSIZE];
	stack<int> S;
	inline void DFS(int ID,reg int dep,reg bool f){
		if(dep==len&&tag[ID]&&!f){
			flag=true;
			return;
		}
		if(dep==len&&tag[ID]&&f){
			if(!vis[ID]){
				vis[ID]=true;
				S.push(ID);
			}
			return;
		}
		reg int c=str[dep]-'a';
		if(!f){
			if(dep<len)
				DFS(ID,dep+1,true);
			for(reg int i=0;i<26;++i)
				if(ch[ID][i]){
					DFS(ch[ID][i],dep,true);
					DFS(ch[ID][i],dep+1,true);
				}
		}
		if(ch[ID][c])
			DFS(ch[ID][c],dep+1,f);
		return;
	}
	inline int Query(char s[]){
		flag=false;
		len=strlen(s);
		str=s;
		DFS(0,0,false);
		reg int res=S.size();
		while(!S.empty()){
			reg int x=S.top();
			S.pop();
			vis[x]=false;
		}
		return flag?-1:res;
	}
}

using namespace Trie;
int n,m;

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i){
		static char w[32];
		scanf("%s",w);
		insert(w);
	}
	for(reg int i=1;i<=m;++i){
		static char q[32];
		scanf("%s",q);
		printf("%d\n",Query(q));
	}
	return 0;
}
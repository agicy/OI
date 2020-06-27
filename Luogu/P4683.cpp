#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=25000+5;

int n;

namespace Trie{
	const int MAXSIZE=MAXN*26;
	int tot;
	int next[MAXSIZE][26];
	bool tag[MAXSIZE];
	inline void Init(void){
		tot=1;
		return;
	}
	inline void insert(reg char str[],reg int len){
		reg int ID=1;
		for(reg int i=1;i<=len;++i){
			reg int c=str[i]-'a';
			if(!next[ID][c])
				next[ID][c]=++tot;
			ID=next[ID][c];
		}
		tag[ID]=true;
		return;
	}
	int Maxdep[MAXSIZE],son[MAXSIZE];
	inline void DFS1(reg int ID){
		for(reg int i=0;i<26;++i)
			if(next[ID][i]){
				DFS1(next[ID][i]);
				Maxdep[ID]=max(Maxdep[ID],Maxdep[next[ID][i]]+1);
				if(Maxdep[son[ID]]<Maxdep[next[ID][i]])
					son[ID]=next[ID][i];
			}
		return;
	}
	int cnt;
	int cnta;
	char ans[1048576];
	inline void DFS2(reg int ID){
		if(tag[ID]){
			ans[++cnta]='P';
			++cnt;
			if(cnt==n){
				printf("%d\n",cnta);
				for(reg int i=1;i<=cnta;++i)
					putchar(ans[i]),putchar('\n');
				exit(0);
			}
		}
		reg int s=-1;
		for(reg int i=0;i<26;++i)
			if(next[ID][i]&&next[ID][i]!=son[ID]){
				ans[++cnta]=i+'a';
				DFS2(next[ID][i]);
				ans[++cnta]='-';
			}
			else if(next[ID][i]&&next[ID][i]==son[ID])
				s=i;
		if(s!=-1){
			ans[++cnta]=s+'a';
			DFS2(next[ID][s]);
			ans[++cnta]='-';
		}
		return;
	}
}

using namespace Trie;

int main(void){
	scanf("%d",&n);
	Init();
	for(reg int i=1;i<=n;++i){
		static char str[1048576];
		scanf("%s",str+1);
		insert(str,strlen(str+1));
	}
	DFS1(1);
	DFS2(1);
	return 0;
}
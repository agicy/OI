#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100000+5;

int n;
string str[MAXN];

namespace Trie{
	const int MAXSIZE=510000;
	int tot=1;
	int ch[MAXSIZE][26];
	int tag[MAXSIZE];
	inline void insert(char str[],reg int id){
		reg int ID=1;
		reg int len=strlen(str);
		for(reg int i=len-1;i>=0;--i){
			if(!ch[ID][str[i]-'a'])
				ch[ID][str[i]-'a']=++tot;
			ID=ch[ID][str[i]-'a'];
		}
		tag[ID]=id;
		return;
	}
}

using namespace Trie;

namespace UnionFind{
	int fa[MAXSIZE];
	inline void Init(reg int S){
		for(reg int i=1;i<=S;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
}

using namespace UnionFind;

vector<int> G[MAXSIZE];

inline void Build(reg int ID){
	for(reg int i=0;i<26;++i){
		reg int v=ch[ID][i];
		if(v){
			if(!tag[v])
				fa[v]=find(ID);
			else
				G[tag[find(ID)]].push_back(tag[v]);
			Build(v);
		}
	}
	return;
}

int size[MAXN];

inline bool cmp(reg int a,reg int b){
	return size[a]<size[b];
}

inline void DFS1(reg int ID){
	size[ID]=1;
	for(reg int i=0,S=G[ID].size();i<S;++i){
		DFS1(G[ID][i]);
		size[ID]+=size[G[ID][i]];
	}
	sort(G[ID].begin(),G[ID].end(),cmp);
	return;
}

ll ans;
int tim,dfn[MAXN];

inline void DFS2(reg int ID){
	dfn[ID]=tim++;
	for(reg int i=0,size=G[ID].size();i<size;++i){
		if(G[ID][i]==ID)
			continue;
		ans+=tim-dfn[ID];
		DFS2(G[ID][i]);
	}
	return;
}

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		static char str[MAXSIZE];
		scanf("%s",str);
		insert(str,i);
	}
	Init(tot);
	Build(1);
	DFS1(0);
	DFS2(0);
	printf("%lld\n",ans);
	return 0;
}
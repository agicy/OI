#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=300000+5;

namespace Trie{
	const int MAXSIZE=300000*26+5;
	int tot;
	int ch[MAXSIZE][26];
	bool tag[MAXSIZE];
	inline void insert(const string& str){
		reg int ID=0;
		for(reg int i=0,len=str.length();i<len;++i){
			reg int c=str[i]-'a';
			if(!ch[ID][c])
				ch[ID][c]=++tot;
			ID=ch[ID][c];
		}
		tag[ID]=true;
		return;
	}
	int cnt,head[26],to[MAXSIZE],Next[MAXSIZE];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int inDeg[26];
	queue<int> Q;
	inline bool Topo(void){
		for(int i=0;i<26;++i)
			if(!inDeg[i])
				Q.push(i);
		while(!Q.empty()){
			reg int ID=Q.front();
			Q.pop();
			for(reg int i=head[ID];i;i=Next[i]){
				--inDeg[to[i]];
				if(!inDeg[to[i]])
					Q.push(to[i]);
			}
		}
		for(reg int i=0;i<26;++i)
			if(inDeg[i])
				return false;
		return true;
	}
	inline void Init(void){
		cnt=0;
		memset(head,0,sizeof(head));
		memset(inDeg,0,sizeof(inDeg));
		return;
	}
	inline bool find(const string& str){
		Init();
		reg int ID=0;
		for(reg int i=0,len=str.length();i<len;++i){
			if(tag[ID])
				return false;
			reg int c=str[i]-'a';
			for(reg int j=0;j<26;++j)
				if(ch[ID][j]&&c!=j){
					++inDeg[j];
					Add_Edge(c,j);
				}
			ID=ch[ID][c];
		}
		return Topo();
	}
}

using namespace Trie;

int n;
bool Ans[MAXN];
string str[MAXN];

int main(void){
	ios::sync_with_stdio(false);
	cin>>n;
	for(reg int i=1;i<=n;++i){
		cin>>str[i];
		insert(str[i]);
	}
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		if(find(str[i])){
			++ans;
			Ans[i]=true;
		}
	cout<<ans<<endl;
	for(reg int i=1;i<=n;++i)
		if(Ans[i])
			cout<<str[i]<<endl;
	return 0;
}
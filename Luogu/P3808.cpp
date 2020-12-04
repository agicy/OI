#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=1e6+5;
const int MAXSIZE=5e5+5;

namespace AC{
	struct Node{
		int nex[26];
		int fail,val;
		#define nex(x) unit[(x)].nex
		#define fail(x) unit[(x)].fail
		#define val(x) unit[(x)].val
	};
	int tot;
	Node unit[MAXSIZE];
	inline void insert(reg int len,reg char str[]){
		reg int id=0;
		for(reg int i=0;i<len;++i){
			reg int ch=str[i]-'a';
			if(!nex(id)[ch])
				nex(id)[ch]=++tot;
			id=nex(id)[ch];
		}
		++val(id);
		return;
	}
	inline void bfs(void){
		queue<int> Q;
		for(reg int i=0;i<26;++i)
			if(nex(0)[i]){
				fail(nex(0)[i])=0;
				Q.push(nex(0)[i]);
			}
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=0;i<26;++i)
				if(nex(u)[i])
					fail(nex(u)[i])=nex(fail(u))[i],Q.push(nex(u)[i]);
				else
					nex(u)[i]=nex(fail(u))[i];
		}
		return;
	}
	inline int query(reg int len,reg char str[]){
		reg int res=0,u=0;
		for(reg int i=0;i<len;++i){
			reg int ch=str[i]-'a';
			u=nex(u)[ch];
			for(reg int j=u;j&&(~val(j));j=fail(j)){
				res+=val(j);
				val(j)=-1;
			}
		}
		return res;
	}
};

int n;
char str[MAXN];

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		scanf("%s",str);
		reg int len=strlen(str);
		AC::insert(len,str);
	}
	AC::bfs();
	scanf("%s",str);
	reg int len=strlen(str);
	reg int ans=AC::query(len,str);
	printf("%d\n",ans);
	return 0;
}
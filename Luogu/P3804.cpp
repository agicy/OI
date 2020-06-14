#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=1000000+5;

char str[MAXSIZE];
ll ans;

namespace SAM{
	struct Node{
		int dep,link;
		int ch[26];
	};
	Node p[MAXSIZE<<1];
	int size;
	int last;
	int cnt[MAXSIZE<<1];
	inline void Init(void){
		p[1].dep=0;
		p[1].link=0;
		last=1;
		size=1;
		return;
	}
	inline void insert(reg int ch){
		reg int ID=++size,pre=last;
		p[ID].dep=p[last].dep+1;
		++cnt[ID];
		while(pre!=0&&p[pre].ch[ch]==0){
			p[pre].ch[ch]=ID;
			pre=p[pre].link;
		}
		if(pre==0)
			p[ID].link=1;
		else{
			reg int q=p[pre].ch[ch];
			if(p[pre].dep+1==p[q].dep)
				p[ID].link=q;
			else{
				reg int clone=++size;
				p[clone]=p[q];
				p[clone].dep=p[pre].dep+1;
				while(pre!=0&&p[pre].ch[ch]==q){
					p[pre].ch[ch]=clone;
					pre=p[pre].link;
				}
				p[ID].link=p[q].link=clone;
			}
		}
		last=ID;
		return;
	}
}

int cnt,head[MAXSIZE<<1],to[MAXSIZE<<1],Next[MAXSIZE<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void DFS(reg int ID){
	for(reg int i=head[ID];i;i=Next[i]){
		DFS(to[i]);
		SAM::cnt[ID]+=SAM::cnt[to[i]];
	}
	if(SAM::cnt[ID]!=1)
		ans=max(ans,(ll)SAM::cnt[ID]*SAM::p[ID].dep);
	return;
}

using namespace SAM;

int main(void){
	scanf("%s",str+1);
	Init();
	reg int n=strlen(str+1);
	for(reg int i=1;i<=n;++i)
		insert(str[i]-'a');
	for(reg int i=2;i<=size;++i)
		Add_Edge(p[i].link,i);
	DFS(1);
	printf("%lld\n",ans);
	return 0;
}
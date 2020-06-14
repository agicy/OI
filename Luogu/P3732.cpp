#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100000+5;
const int MAXQ=100000+5;

struct Querys{
	int l,r,id;
	inline void Read(reg int i){
		id=i;
		scanf("%d%d",&l,&r);
		return;
	}
	inline bool operator<(const Querys &a){
		return (r==a.r)?(l<a.l):(r<a.r);
	}
};

int n,q;
char str[MAXN];
Querys Q[MAXQ];

const int MAXDATA=40+5;

namespace Trie{
	const int MAXSIZE=100000*40;
	int tot;
	int ch[MAXSIZE][2];
	int last[MAXSIZE];
	int Max[MAXSIZE];
	inline void insert(reg int x){
		reg int ID=0;
		for(reg int i=1;x+i-1<=n&&i<=MAXDATA;++i){
			reg int c=str[x+i-1]-'0';
			if(!ch[ID][c])
				ch[ID][c]=++tot;
			else
				Max[i]=max(Max[i],last[ch[ID][c]]);
			last[ch[ID][c]]=x;
			ID=ch[ID][c];
		}
		return;
	}
}

using namespace Trie;

ll ans[MAXQ];

int main(void){
	scanf("%d%d%s",&n,&q,str+1);
	for(reg int i=1;i<=q;++i)
		Q[i].Read(i);
	sort(Q+1,Q+q+1);
	for(reg int i=1,ptr=1;i<=n;++i){
		insert(i);
		while(ptr<=q&&Q[ptr].r==i){
			for(reg int i=1;i<=MAXDATA;++i)
				if(Max[i]<Q[ptr].l)
					break;
				else
					ans[Q[ptr].id]+=(ll)i*(Max[i]-max(Q[ptr].l-1,Max[i+1]));
			++ptr;
		}
	}
	for(reg int i=1;i<=q;++i)
		printf("%lld\n",ans[i]);
	return 0;
}
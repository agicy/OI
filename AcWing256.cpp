#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	char ch=getchar();
	int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=3e5+5;
const int MAXM=3e5+5;
const int MAXLOG2A=24+1;

int n,m;
int a[MAXN+MAXM];

namespace Trie{
	const int MAXSIZE=40*MAXN;
	struct Node{
		int next[2];
		int cnt;
		#define next(x) unit[(x)].next
		#define cnt(x) unit[(x)].cnt
	};
	int root[MAXN+MAXM],tot;
	Node unit[MAXSIZE];
	inline void insert(int k,int pre,int x,int dep){
		if(dep<0)
			return;
		int ch=(x>>dep)&1;
		next(k)[!ch]=next(pre)[!ch];
		next(k)[ch]=++tot;
		cnt(next(k)[ch])=cnt(next(pre)[ch])+1;
		insert(next(k)[ch],next(pre)[ch],x,dep-1);
		return;
	}
	inline int query(int pre,int las,int x,int dep){
		if(dep<0)
			return 0;
		int ch=(x>>dep)&1;
		if(cnt(next(las)[!ch])>cnt(next(pre)[!ch]))
			return (1<<dep)+query(next(pre)[!ch],next(las)[!ch],x,dep-1);
		else
			return query(next(pre)[ch],next(las)[ch],x,dep-1);
	}
}

using namespace Trie;

int main(void){
	n=read(),m=read();
	int cnt=0,sum=0;
	insert(root[0]=++tot,0,0,MAXLOG2A-1);
	for(int i=1;i<=n;++i){
		sum^=read();
		root[++cnt]=++tot;
		insert(root[cnt],root[cnt-1],sum,MAXLOG2A-1);
	}
	while(m--){
		static char opt;
		static int l,r,x;
		do
			opt=getchar();
		while(opt!='A'&&opt!='Q');
		switch(opt){
			case 'A':{
				sum^=read();
				root[++cnt]=++tot;
				Trie::insert(root[cnt],root[cnt-1],sum,MAXLOG2A-1);
				break;
			}
			case 'Q':{
				l=read()-1,r=read()-1,x=read();
				x^=sum;
				int res=0;
				if(l==0)
					res=query(0,root[r],x,MAXLOG2A-1);
				else
					res=query(root[l-1],root[r],x,MAXLOG2A-1);
				printf("%d\n",res);
				break;
			}
		}
	}
	return 0;
}
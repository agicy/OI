#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;
const int MAXA=26+5;
const int MAXSIZE=1e3+5;

namespace UnionFind{
	int fa[MAXN];
	inline void Init(int n){
		for(int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(int a,int b){
		int ra=find(a),rb=find(b);
		if(rb!=ra)
			fa[rb]=ra;
		return;
	}
	inline bool search(int a,int b){
		return find(a)==find(b);
	}
}

int n;
int inDeg[MAXA],outDeg[MAXA];

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		memset(inDeg,0,sizeof(inDeg));
		memset(outDeg,0,sizeof(outDeg));
		scanf("%d",&n);
		UnionFind::Init(26);
		for(int i=1;i<=n;++i){
			static char str[MAXSIZE];
			scanf("%s",str+1);
			int len=strlen(str+1);
			int a=str[1]-'a'+1,b=str[len]-'a'+1;
			++outDeg[a],++inDeg[b];
			UnionFind::merge(a,b);
		}
		int cnt=0;
		for(int i=1;i<=26;++i)
			if(inDeg[i]||outDeg[i])
				if(UnionFind::find(i)==i||abs(inDeg[i]-outDeg[i])>1)
					++cnt;
		if(cnt>1)
			puts("The door cannot be opened.");
		else{
			int s1=0,s2=0;
			for(int i=1;i<=26;++i){
				if(inDeg[i]<outDeg[i])
					++s1;
				if(inDeg[i]>outDeg[i])
					++s2;
			}
			if(s1==s2&&(s1==0||s1==1))
				puts("Ordering is possible.");
			else
				puts("The door cannot be opened.");
		}
	}
	return 0;
}
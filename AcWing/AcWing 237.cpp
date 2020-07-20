#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1000000+5;

struct UnionFind{
	int ID[MAXN<<1];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			ID[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==ID[x])
			return x;
		else
			return ID[x]=find(ID[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			ID[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
};

int n;
int opt[MAXN],x[MAXN],y[MAXN];
vector<int> V;
UnionFind S;

int main(void){
	reg int T=read();
	while(T--){
		V.clear();
		n=read();
		for(reg int i=1;i<=n;++i){
			x[i]=read(),y[i]=read(),opt[i]=read();
			V.push_back(x[i]),V.push_back(y[i]);
		}
		sort(V.begin(),V.end());
		V.erase(unique(V.begin(),V.end()),V.end());
		for(reg int i=1;i<=n;++i)
			x[i]=lower_bound(V.begin(),V.end(),x[i])-V.begin()+1,
			y[i]=lower_bound(V.begin(),V.end(),y[i])-V.begin()+1;
		S.Init(V.size());
		for(reg int i=1;i<=n;++i)
			if(opt[i]==1)
				S.merge(x[i],y[i]);
		reg bool flag=true;
		for(reg int i=1;i<=n;++i)
			if(opt[i]==0&&S.search(x[i],y[i])){
				flag=false;
				break;
			}
		puts(flag?"YES":"NO");
	}
	return 0;
}

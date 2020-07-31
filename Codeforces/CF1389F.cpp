#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=2e5+5;

struct Node{
	int l,r,t;
	inline void Read(void){
		l=read(),r=read(),t=read()-1;
		return;
	}
	inline bool operator<(const Node& a){
		return r<a.r||(r==a.r&&l<a.l);
	}
};

int n;
Node a[MAXN];
multiset<int> S[2];

int main(void){
	n=read();
	reg int ans=n;
	for(reg int i=0;i<n;++i)
		a[i].Read();
	sort(a,a+n);
	for(reg int i=0;i<n;++i){
		reg int c=a[i].t;
		if(S[c^1].lower_bound(a[i].l)==S[c^1].end())
			S[c].insert(a[i].r);
		else{
			--ans;
			S[c^1].erase(S[c^1].lower_bound(a[i].l));
		}
	}
	printf("%d\n",ans);
	return 0;
}
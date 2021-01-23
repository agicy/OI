#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;

struct Node{
	int val,id;
	inline bool operator<(const Node& a)const{
		return val<a.val||(val==a.val&&id<a.id);
	}
};

int n;
Node a[MAXN];
int ans[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].id=i,a[i].val=read();
	sort(a+1,a+n+1);
	BIT::Init(n);
	BIT::update(a[1].id,1);
	for(reg int i=2;i<=n;++i){
		for(reg int j=1;j<n&&(a[i].id-1)*j+2<=n;++j)
			ans[j]+=BIT::query(min(n,a[i].id*j+1))-BIT::query((a[i].id-1)*j+1);
		BIT::update(a[i].id,1);
	}
	for(reg int i=1;i<n;++i)
		printf("%d%c",ans[i],i==n-1?'\n':' ');
	return 0;
}
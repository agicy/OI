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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;

namespace TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n;
	int unit[MAXN<<1];
	inline void Init(reg int S){
		n=S;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int u,reg int val){
		for(reg int i=u;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int u){
		reg int res=0;
		for(reg int i=u;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	#undef lowbit
}

int n;
int a[MAXN<<1];
bool vis[MAXN<<1];
vector<int> pos[MAXN<<1];

int main(void){
	n=(read()<<1);
	TreeArray::Init(n);
	for(int i=1;i<=n;++i){
		a[i]=read();
		pos[a[i]+n].push_back(i);
		TreeArray::update(i,1);
	}
	reg ll ans=0;
	for(reg int i=n;i>=1;--i){
		if(vis[i])
			continue;
		vis[i]=true;
		pos[a[i]+n].pop_back();
		reg int res=pos[n-a[i]].back();
		pos[n-a[i]].pop_back();
		vis[res]=true;
		ans=(ans+TreeArray::query(i-1)-TreeArray::query(res)+(a[i]<0));
		TreeArray::update(res,-1);
	}
	printf("%lld\n",ans);
	return 0;
}
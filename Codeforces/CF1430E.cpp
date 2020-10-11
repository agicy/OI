#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=2e5+5;

int n;
char s[MAXN];
stack<int> S[26];
int pos[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int S){
		n=S;
		memset(unit,0,sizeof(unit));
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
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;++i)
		S[s[i]-'a'].push(i);
	for(reg int i=1;i<=n;++i){
		pos[n-i+1]=S[s[i]-'a'].top();
		S[s[i]-'a'].pop();
	}
	reg ll ans=0;
	BIT::Init(n);
	for(reg int i=n;i>=1;--i){
		ans+=BIT::query(pos[i]);
		BIT::update(pos[i],1);
	}
	printf("%lld\n",ans);
	return 0;
}
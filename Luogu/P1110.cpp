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

const int MAXN=5e5+5;
const int INF=0X3F3F3F3F;

int n,m;
int st[MAXN],ed[MAXN];
multiset<int> full,delta;
int ans=INF;

inline void update(int x){
	multiset<int>::iterator it=full.lower_bound(x);
	int diff=*it-x;
	--it;
	ans=min(ans,min(diff,x-*it));
	full.insert(x);
	return;
}

inline void replace(reg int pos,reg int x){
	delta.insert(abs(x-ed[pos]));
	if(pos!=n){
		delta.erase(delta.find(abs(st[pos+1]-ed[pos])));
		delta.insert(abs(st[pos+1]-x));
	}
	ed[pos]=x;
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		st[i]=ed[i]=read();
	full.insert(-INF),full.insert(INF);
	for(reg int i=1;i<n;++i)
		delta.insert(abs(ed[i]-st[i+1]));
	for(reg int i=1;i<=n;++i)
		update(st[i]);
	for(reg int i=1;i<=m;++i){
		static char str[16];
		static int pos,x;
		scanf("%s",str);
		switch(str[4]){
			case 'R':{
				pos=read(),x=read();
				update(x);
				replace(pos,x);
				break;
			}
			case 'G':{
				printf("%d\n",*delta.begin());
				break;
			}
			case 'S':{
				printf("%d\n",ans);
				break;
			}
		}
	}
	return 0;
}
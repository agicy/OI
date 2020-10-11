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

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		scanf("%s",s+1);
		reg int cnt=0,ans=0,las=0;
		for(reg int i=1;i<=n;++i)
			if(s[i]!=s[i-1]){
				ans+=min(i-las-1,cnt-ans);
				++cnt,las=i;
			}
		ans+=min(n+1-las-1,cnt-ans);
		cnt-=ans;
		printf("%d\n",ans+(cnt>>1)+(cnt&1));
	}
	return 0;
}
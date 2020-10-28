#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;

char s[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		reg int n=read();
		scanf("%s",s+1);
		reg int cnt=0;
		for(reg int i=1;i<n;++i)
			if(s[i]!=s[i+1])
				++cnt;
		printf("%d\n",(n-cnt)/2);
	}
	return 0;
}
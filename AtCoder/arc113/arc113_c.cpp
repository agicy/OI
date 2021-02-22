#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXS=2e5+5;

char s[MAXS];
map<char,int> M;

signed main(void){
	read(s);
	reg ll ans=0;
	reg int n=strlen(s);
	for(reg int i=n-1;i>=0;--i){
		++M[s[i]];
		if(i<=n-3&&s[i]==s[i+1]&&s[i]!=s[i+2]){
			ans+=n-i-M[s[i]];
			M.clear();
			M[s[i]]=n-i;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char s[]){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=1e6+5;

int n;
char s[MAXN];
int kmp[MAXN];

int main(void){
	n=read();
	read(s+1);
	for(reg int i=2,j=0;i<=n;++i){
		while(j&&s[j+1]!=s[i])
			j=kmp[j];
		if(s[j+1]==s[i])
			++j;
		kmp[i]=j;
	}
	reg ll ans=0;
	for(reg int i=2;i<=n;++i){
		reg int j=i;
		while(kmp[j])
			j=kmp[j];
		if(kmp[i])
			kmp[i]=j;
		ans+=i-j;
	}
	printf("%lld\n",ans);
	return 0;
}
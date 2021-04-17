#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=5e5+5;

ull trans[128];
int cnt[128];
int n;
char s[MAXN];

int main(void){
	for(reg int i='A';i<='Z';++i)
		trans[i]=1ull<<(i-'A');
	for(reg int i='a';i<='z';++i)
		trans[i]=1ull<<(i-'a'+26);
	n=read(),read(s);
	reg ll U=0;
	for(reg int i=0;i<n;++i)
		U|=trans[s[i]];
	reg int l=0,r=-1;
	reg int ans=n;
	reg ull S=0;
	while(l<n){
		while(r+1<n&&S!=U){
			++r;
			if(!cnt[s[r]]++)
				S^=trans[s[r]];
		}
		if(S==U)
			ans=min(ans,r-l+1);
		if(!--cnt[s[l]])
			S^=trans[s[l]];
		++l;
	}
	printf("%d\n",ans);
	return 0;
}
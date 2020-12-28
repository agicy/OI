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

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXL=1e6+5;
const int p=1e9+7;

char s[MAXL];
int kmp[MAXL],num[MAXL];

int main(void){
	reg int n=read();
	while(n--){
		read(s+1);
		reg int len=strlen(s+1);
		num[1]=1;
		for(reg int i=2,j=0;i<=len;++i){
			while(j&&(s[i]!=s[j+1]))
				j=kmp[j];
			if(s[j+1]==s[i])
				++j;
			kmp[i]=j;
			num[i]=num[j]+1;
		}
		reg int ans=1;
		for(reg int i=2,j=0;i<=len;++i){
			while(j&&s[i]!=s[j+1])
				j=kmp[j];
			if(s[j+1]==s[i])
				++j;
			while((j<<1)>i)
				j=kmp[j];
			ans=1ll*ans*(num[j]+1)%p;
		}
		printf("%d\n",ans);
	}
	return 0;
}
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

const int MAXS=5e5+5;

char s[MAXS];
int kmp[MAXS],pos[MAXS],f[MAXS];

int main(void){
	read(s+1);
	reg int n=strlen(s+1);
	for(reg int i=2,j=0;i<=n;++i){
		while(j&&(s[i]!=s[j+1]))
			j=kmp[j];
		if(s[j+1]==s[i])
			++j;
		kmp[i]=j;
	}
	f[1]=pos[1]=1;
	for(reg int i=2;i<=n;++i){
		if(pos[f[kmp[i]]]>=i-kmp[i])
			f[i]=f[kmp[i]];
		else
			f[i]=i;
		pos[f[i]]=i;
	}
	printf("%d\n",f[n]);
	return 0;
}
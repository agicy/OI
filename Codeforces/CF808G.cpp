#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)&&*s!='?')*s=getchar();
	while(isalpha(*s)||*s=='?')*(++s)=getchar();
	*s='\0';
	return;
}

inline void cMax(reg int &a,reg int b){
	if(a<b)a=b;
	return;
}

const int MAXS=1e5+5;

char s[MAXS],t[MAXS];
int n,m;
int kmp[MAXS];
int f[MAXS],g[MAXS];

inline bool check(reg int p){
	for(reg int i=1;i<=m;++i)
		if(s[p-i+1]!=t[m-i+1]&&s[p-i+1]!='?')
			return false;
	return true;
}

int main(void){
	read(s+1),read(t+1);
	n=strlen(s+1),m=strlen(t+1);
	for(reg int i=2,j=0;i<=m;++i){
		while(j&&t[j+1]!=t[i])
			j=kmp[j];
		if(t[j+1]==t[i])
			++j;
		kmp[i]=j;
	}
	for(reg int i=1;i<=n;++i){
		f[i]=f[i-1];
		if(check(i)){
			g[i]=f[i-m]+1;
			for(reg int j=kmp[m];j;j=kmp[j])
				cMax(g[i],g[i-(m-j)]+1);
			cMax(f[i],g[i]);
		}
	}
	printf("%d\n",f[n]);
	return 0;
}
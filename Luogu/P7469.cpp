#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=3e3+5;

int n;
char s[MAXN],t[MAXN];
int len[MAXN][MAXN];

int main(void){
	n=read();
	read(s+1),read(t+1);
	reg int ans=0;
	for(reg int i=n;i>=1;--i){
		reg int Max=0;
		for(reg int j=i+1;j<=n;++j)
			Max=max(Max,len[j][i]);
		reg int k=1;
		for(int j=i;j<i+Max;++j){
			while(k<=n&&s[k]!=t[j])
				++k;
			if(k>n)
				break;
			++k;
		}
		for(reg int j=i+Max;j<=n;++j){
			while(k<=n&&s[k]!=t[j])
				++k;
			if(k>n)
				break;
			++k,++ans;
		}
		for(reg int j=1;j<=n;++j)
			if(t[i]==t[j])
				len[i][j]=len[i+1][j+1]+1;
	}
	printf("%d\n",ans);
	return 0;
}
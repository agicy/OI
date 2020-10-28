#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10ll*res+ch-'0',ch=getchar();
	return res;
}

const int MAXS=1e6+5;

char s[MAXS];
ll n;

int main(void){
	scanf("%s%lld",s+1,&n);
	reg ll len=strlen(s+1);
	while(len<n){
		reg ll i=len;
		while(n>i*2)
			i<<=1;
		n-=(i+1);
		if(!n)
			n=i;
	}
	printf("%c\n",s[n]);
	return 0;
}
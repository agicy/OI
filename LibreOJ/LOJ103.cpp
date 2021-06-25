#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;

inline char* read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return s;
}

const int MAXS=1e6+5;

char a[MAXS],b[MAXS];
int kmp[MAXS];

int main(void){
	reg int la=read(a)-a;
	reg int lb=read(b)-b;
	kmp[0]=-1;
	for(reg int i=1,j=-1;i<lb;++i){
		while(j>=0&&b[i]!=b[j+1])
			j=kmp[j];
		if(b[i]==b[j+1])
			++j;
		kmp[i]=j;
	}
	reg int cnt=0;
	for(reg int i=0,j=-1;i<la;++i){
		while(j>=0&&a[i]!=b[j+1])
			j=kmp[j];
		if(a[i]==b[j+1])
			++j;
		if(j==lb-1)
			++cnt,j=kmp[j];
	}
	printf("%d\n",cnt);
	return 0;
}
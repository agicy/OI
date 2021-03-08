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

const int MAXN=2e4+5;
const int MAXM=2e3+5;
const int inf=0x3f3f3f3f;

int m,n;
int a[MAXN],T1[MAXM],T2[MAXM];

inline bool check(reg int x){
	for(reg int i=1;i<=x;++i)
		++T1[a[i]],++T2[a[i+x]];
	reg bool res=true;
	reg int ptr1=1,ptr2=1;
	for(reg int i=1;i<=x;++i){
		while(!T1[ptr1])
			++ptr1;
		while(!T2[ptr2])
			++ptr2;
		if(ptr1>=ptr2)
			res=false;
		--T1[ptr1],--T2[ptr2];
	}
	return res;
}

int main(void){
	m=read(),n=read();
	reg bool flag=true;
	reg int pos=inf;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		if(a[i]==m&&!flag)
			flag=true,pos=i;
	}
	for(reg int i=min(pos-1,n/2);i>=0;--i)
		if(check(i)){
			printf("%d\n",i);
			break;
		}
	return 0;
}
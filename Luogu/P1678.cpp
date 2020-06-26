#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;

int m,n;
int b[MAXN];
priority_queue<int,vector<int>,greater<int>/**/>Q;

int main(void){
	m=read(),n=read();
	for(reg int i=1;i<=m;++i)
		b[i]=read();
	for(reg int i=1;i<=n;++i){
		static int x;
		x=read();
		Q.push(x);
	}
	sort(b+1,b+m+1);
	reg int sum=0;
	reg int ptr=1;
	for(reg int i=1;i<=n;++i){
		reg int x=Q.top();
		Q.pop();
		reg int p=abs(x-b[ptr]);
		while(abs(x-b[ptr+1])<=p){
			++ptr;
			p=abs(x-b[ptr]);
		}
		sum+=p;
	}
	printf("%d\n",sum);
	return 0;
}

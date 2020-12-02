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

const int MAXN=1e5+5;
const int MAXLOG2M=30+1;

struct Node{
	char opt;
	int t;
	inline Node(reg int opt=0,reg int t=0):opt(opt),t(t){
		return;
	}
};

int n,m;
Node p[MAXN];

inline int calc(reg int id,reg int s){
	for(reg int i=1;i<=n;++i){
		reg int v=(p[i].t>>id)&1;
		switch(p[i].opt){
			case 'A':{
				s&=v;
				break;
			}
			case 'O':{
				s|=v;
				break;
			}
			case 'X':{
				s^=v;
				break;
			}
		}
	}
	return s;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		static char opt;
		static int t;
		do
			opt=getchar();
		while(!isalpha(opt));
		t=read();
		p[i]=Node(opt,t);
	}
	reg int ans=0,val=0;
	for(reg int i=MAXLOG2M-1;i>=0;--i){
		reg int res0=calc(i,0),res1=calc(i,1);
		if((val|(1<<i))<=m&&res0<res1)
			val|=(1<<i),ans|=(res1<<i);
		else
			ans|=(res0<<i);
	}
	printf("%d\n",ans);
	return 0;
}
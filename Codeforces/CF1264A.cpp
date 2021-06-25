#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=4e5+5;

int n;
int siz[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		reg int las=-1;
		reg int tot=0;
		for(reg int i=1;i<=n;++i){
			reg int p=read();
			if(p!=las)
				siz[++tot]=1;
			else
				++siz[tot];
			las=p;
		}
		reg int sum=0,ptr=0;
		while(ptr<tot&&sum+siz[ptr+1]<=(n>>1))
			++ptr,sum+=siz[ptr];
		reg int g=siz[1],s=0;
		for(reg int i=2;i<=ptr;++i){
			s+=siz[i];
			if(s>g)
				break;
		}
		reg int b=sum-g-s;
		if(!g||!s||!b||g>=s||g>=b||g+s+b>(n>>1))
			puts("0 0 0");
		else
			printf("%d %d %d\n",g,s,b);
	}
	return 0;
}
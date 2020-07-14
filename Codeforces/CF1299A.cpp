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

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int a[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

const int MAXLOG2A=31;

int T[MAXLOG2A];

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		for(reg int j=0;j<MAXLOG2A;++j)
			if((a[i]>>j)&1)
				++T[j];
	int Ans=-1,First=-1;
	for(reg int i=1;i<=n;++i){
		reg int temp=a[i];
		for(reg int j=0;j<MAXLOG2A;++j)
			if(((a[i]>>j)&1)&&T[j]>1)
				temp^=(1<<j);
		if(Ans<temp){
			Ans=temp;
			First=i;
		}
	}
	printf("%d",a[First]);
	for(reg int i=1;i<=n;++i)
		if(i!=First)
			printf(" %d",a[i]);
	putchar('\n');
	return;
}

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

const int MAXN=1000000+5;

int n;
int l[MAXN],r[MAXN];
int Q[MAXN];

int main(){
	n=read();
	for(reg int i=1;i<=n;++i)
		l[i]=read(),r[i]=read();
	reg int head=1,tail=1;
	Q[1]=1;
	int ans=1;
	for(reg int i=1;i<=n;++i){
		while(l[Q[head]]>r[i]&&head<=tail)
			++head;
		if(head<=tail)
			ans=max(ans,i-Q[head]+1);
		int t=i;
		while(l[i]>l[Q[tail]]&&head<=tail)
			t=Q[tail--];
		l[t]=l[i];
		Q[++tail]=t;
	}
	printf("%d\n",ans);
	return 0;
}
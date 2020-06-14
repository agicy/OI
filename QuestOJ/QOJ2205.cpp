#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=2000+5;
const int MAXSIZE=MAXN*MAXN;

int n;
bitset<MAXSIZE> S;

int main(void){
	n=read();
	reg int sum=0;
	S[0]=1;
	for(reg int i=1;i<=n;++i){
		static int x;
		x=read();
		sum+=x;
		S|=(S<<x);
	}
	for(reg int i=(sum+1)>>1;i<=sum;++i)
		if(S[i]){
			printf("%d\n",i);
			break;
		}
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

int n;
int a[MAXN<<1];

inline bool check(reg int lim){
	reg int Min=inf,col=-1;
	for(reg int i=1;i<=((n-1)<<1);++i)
		if((a[i]>lim)==(a[i+1]>lim))
			if(min(abs(i-n),abs(i+1-n))<Min){
				Min=min(abs(i-n),abs(i+1-n));
				col=(a[i]>lim);
			}
	if(Min!=inf)
		return col;
	else
		return a[1]>lim;
}

bool ed;

int main(void){
	n=read();
	for(reg int i=1;i<(n<<1);++i)
		a[i]=read();
	reg int __l=1,__r=2*n-1,__mid;
	while(__l<__r){
		__mid=(__l+__r)>>1;
		if(check(__mid))
			__l=__mid+1;
		else
			__r=__mid;
	}
	printf("%d\n",__l);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}
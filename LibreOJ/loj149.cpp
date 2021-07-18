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
const double eps=1e-6;

int n,k;
int a[MAXN],b[MAXN];

inline bool check(reg double mid){
	static double val[MAXN];
	for(reg int i=0;i<n;++i)
		val[i]=a[i]-mid*b[i];
	nth_element(val,val+n-k,val+n);
	reg double sum=0;
	for(reg int i=n-k;i<n;++i)
		sum+=val[i];
	return sum>eps;
}

bool ed;

int main(void){
	n=read(),k=read();
	for(reg int i=0;i<n;++i)
		a[i]=read();
	for(reg int i=0;i<n;++i)
		b[i]=read();
	reg double __l=0,__r=1e11,__mid;
	while(__r-__l>eps){
		__mid=0.5*(__l+__r);
		if(check(__mid))
			__l=__mid;
		else
			__r=__mid;
	}
	printf("%.4lf\n",__l);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3f MiB\n",(&ed-&st)/1048576.0);
	return 0;
}
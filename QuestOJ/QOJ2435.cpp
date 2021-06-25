#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline double max(reg double a,reg double b){
	return a>b?a:b;
}

const int MAXN=8;
const double eps=1e-6;
const double pi=acos(-1.0);

int n;
int r[MAXN];
double ans;

inline double getSum(reg double lamda){
	reg double sum=0;
	for(reg int i=0;i<n;++i)
		sum+=acos(lamda/r[i]/r[(i+1)%n]);
	return sum;
}

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		r[i]=read();
	sort(r,r+n);
	do{
		do{
			reg double _l=-1.0*r[0]*r[n-1],_r=1.0*r[0]*r[n-1],_mid;
			while(_r-_l>eps){
				_mid=0.5*(_l+_r);
				if(getSum(_mid)<2*pi)
					_r=_mid;
				else
					_l=_mid;
			}
			if(fabs(getSum(_l)-2*pi)<eps){
				reg double S=0;
				for(reg int i=0;i<n;++i)
					S+=r[i]*r[(i+1)%n]*sin(acos(_l/r[i]/r[(i+1)%n]));
				ans=max(ans,S);
			}
		}while(next_permutation(r,r+n));
		for(reg int i=0;i<n-1;++i)
			r[i]=r[i+1];
		--n;
	}while(n>=3);
	printf("%.6lf\n",0.5*ans);
	return 0;
}
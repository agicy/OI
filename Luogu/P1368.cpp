#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=3e5+5;

int n;
int a[MAXN<<1];

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		a[i]=a[i+n]=read();
	int i=0,j=1,k=0;
	while(i<n&&j<n&&k<n)
		if(a[i+k]==a[j+k])
			++k;
		else{
			if(a[i+k]>a[j+k])
				i=i+k+1;
			else
				j=j+k+1;
			k=0,i+=(i==j);
		}
	reg int st=min(i,j);
	for(reg int i=0;i<n;++i)
		printf("%d%c",a[st+i],i==n-1?'\n':' ');
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e6+5;
const int inf=0x3f3f3f3f;

int n;
char str[MAXN];

inline bool check(reg int mid){
	reg int Max=-inf,Min=inf,pos=0;
	for(reg int i=1;i<=n;++i){
		Max=max(Max,pos),Min=min(Min,pos);
		pos=(str[i]=='L')?pos-1:pos+1;
		if(mid&&pos==mid)
			pos=(str[i]=='L')?pos+1:pos-1;
	}
	return pos<Min||Max<pos;
}

int main(void){
	read(str+1);
	n=strlen(str+1);
	if(check(0))
		puts("1");
	else{
		if(str[n]=='L'){
			reg int l=0,r=n,mid;
			while(l<r){
				mid=(l+r)>>1;
				if(check(mid+1))
					l=mid+1;
				else
					r=mid;
			}
			printf("%d\n",l);
		}
		else{
			reg int l=0,r=n,mid;
			while(l<r){
				mid=(l+r)>>1;
				if(check(-(mid+1)))
					l=mid+1;
				else
					r=mid;
			}
			printf("%d\n",l);
		}
	}
	return 0;
}
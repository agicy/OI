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

const int MAXSIZE=5e3+5;
const int BASE=10;

struct BigNumber{
	int len;
	int unit[MAXSIZE];
	inline BigNumber(reg int x=0){
		len=1,unit[0]=x;
		while(unit[len-1]>=BASE){
			unit[len]=unit[len-1]/BASE;
			unit[len-1]%=BASE;
			++len;
		}
		return;
	}
	inline BigNumber operator*(reg int x){
		BigNumber res;
		res.len=len;
		for(reg int i=0;i<res.len;++i)
			res.unit[i]=unit[i]*x;
		for(reg int i=0;i<res.len-1;++i)
			if(res.unit[i]>=BASE){
				res.unit[i+1]+=res.unit[i]/BASE;
				res.unit[i]%=BASE;
			}
		while(res.unit[res.len-1]>=BASE){
			res.unit[res.len]=res.unit[res.len-1]/BASE;
			res.unit[res.len-1]%=BASE;
			++res.len;
		}
		return res;
	}
	inline void print(void){
		printf("%d\n",len);
		for(reg int i=len-1;i>=max(0,len-100);--i)
			printf("%d",unit[i]);
		putchar('\n');
		return;
	}
};

int n;

int main(void){
	n=read();
	BigNumber ans(1);
	while(n>4){
		n-=3;
		ans=ans*3;
	}
	ans=ans*n;
	ans.print();
	return 0;
}
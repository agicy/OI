#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

ll n;
int cnt[3];

int main(void){
	n=read();
	reg int tmp=n%3;
	while(n){
		++cnt[(n%10)%3];
		n/=10;
	}
	reg int sum=cnt[0]+cnt[1]+cnt[2];
	if(!tmp)
		puts("0");
	else if(tmp==1)
		if(cnt[1]>0&&sum>1)
			puts("1");
		else if(cnt[2]>1&&sum>2)
			puts("2");
		else
			puts("-1");
	else
		if(cnt[2]>0&&sum>1)
			puts("1");
		else if(cnt[1]>1&&sum>2)
			puts("2");
		else
			puts("-1");
	return 0;
}
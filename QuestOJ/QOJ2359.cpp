#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;

int main(void){
	reg char ch;
	while((ch=getchar())!=EOF){
		reg char res=0;
		for(reg int i=7;i>=0;--i)
			res=(res<<1)|(getchar()=='O');
		if(0<res&&res<128)
			putchar(res);
	}
	return 0;
}
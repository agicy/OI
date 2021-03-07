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

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s)&&*s!=':')*s=getchar();
	while(isdigit(*s)||*s==':')*(++s)=getchar();
	*s='\0';
	return;
}

const int inf=0x3f3f3f3f;
const int rev[]={0,10,50,inf,inf,20,inf,inf,80,inf,1,11,51,inf,inf,21,inf,inf,81,inf,5,15,55,inf,inf,25,inf,inf,85,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,2,12,52,inf,inf,22,inf,inf,82,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,8,18,58,inf,inf,28,inf,inf,88,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf};

int main(void){
	reg int t=read();
	while(t--){
		static char str[16];
		reg int h=read(),m=read();
		read(str);
		reg int H=(str[0]^'0')*10+(str[1]^'0');
		reg int M=(str[3]^'0')*10+(str[4]^'0');
		while(true){
			if(M==m)
				H++,M=0;
			if(H==h)
				H=0;
			if(rev[M]<h&&rev[H]<m){
				printf("%02d:%02d\n",H,M);
				break;
			}
			++M;
		}
	}
	return 0;
}
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
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=50+5;

char s[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		read(s+1);
		reg int n=strlen(s+1);
		reg bool ans=false;
		for(reg int S=0;S<8;++S){
			reg bool flag=true;
			reg int top=0;
			for(reg int i=1;i<=n;++i){
				top+=(S>>(s[i]-'A'))&1?-1:1;
				if(top<0){
					flag=false;
					break;
				}
			}
			if(flag&&!top){
				ans=true;
				break;
			}
		}
		puts(ans?"YES":"NO");
	}
	return 0;
}
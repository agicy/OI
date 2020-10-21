#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=200+5;

int n;
char M[MAXN][MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			scanf("%s",M[i]+1);
		for(reg int i=15;i>=0;--i){
			char s[4]={M[1][2],M[2][1],M[n-1][n],M[n][n-1]};
			reg int c=0;
			for(reg int j=0;j<4;++j)
				if((i>>j)&1){
					s[j]^=1;
					++c;
				}
			if(c<=2&&s[0]==s[1]&&s[1]!=s[2]&&s[2]==s[3]){
				printf("%d\n",c);
				if((i>>0)&1)
					puts("1 2\n");
				if((i>>1)&1)
					puts("2 1\n");
				if((i>>2)&1)
					printf("%d %d\n",n-1,n);
				if((i>>3)&1)
					printf("%d %d\n",n,n-1);
				break;
			}
		}
	}
	return 0;
}
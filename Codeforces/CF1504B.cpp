#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s)) *s=getchar();
	while(isdigit(*s)) *(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=3e5+5;

int n;
char a[MAXN],b[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		read(a),read(b);
		reg bool flag=false;
		reg int ptr=0;
		for(reg int i=0,sum=0;i<n;++i){
			if(a[i]=='1')
				++sum;
			else
				--sum;
			if(!sum){
				reg bool fa=true,fb=true;
				for(reg int j=ptr;j<=i;++j)
					if(a[j]==b[j])
						fb=false;
					else
						fa=false;
				if(!fa&&!fb){
					flag=true;
					break;
				}
				ptr=i+1;
			}
		}
		for(reg int i=ptr;i<n;++i)
			if(a[i]!=b[i]){
				flag=true;
				break;
			}
		if(!flag)
			putchar('Y'),putchar('e'),putchar('s'),putchar('\n');
		else
			putchar('N'),putchar('o'),putchar('\n');
	}
	flush();
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXLOG2A=30;

int main(void){
	reg int q=read();
	while(q--){
		reg int u=read(),v=read();
		vector<int> Vu,Vv;
		for(int i=0;i<MAXLOG2A;++i){
			if((u>>i)&1)
				Vu.push_back(i);
			if((v>>i)&1)
				Vv.push_back(i);
		}
		if(u>v||Vu.size()<Vv.size())
			putchar('N'),putchar('o');
		else{
			reg bool flag=true;
			for(reg int i=0,siz=Vv.size();i<siz;++i)
				if(Vv[i]<Vu[i]){
					flag=false;
					break;
				}
			if(flag)
				putchar('Y'),putchar('e'),putchar('s');
			else
				putchar('N'),putchar('o');
		}
		putchar('\n');
	}
	flush();
	return 0;
}
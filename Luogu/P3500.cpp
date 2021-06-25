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

inline void TAK(void){
	putchar('T'),putchar('A'),putchar('K'),putchar('\n');
	return;
}

inline void NIE(void){
	putchar('N'),putchar('I'),putchar('E'),putchar('\n');
	return;
}

const int MAXM=1e6+5;
const int MAXA=1e6+5;
const int A=1e6;

int m;
vector<int> V[MAXA];
int a[MAXM],b[MAXM];
int rt[MAXM];

int main(void){
	m=read();
	for(reg int i=1;i<=m;++i)
		a[i]=read(),V[a[i]].push_back(i);
	reg int q=read();
	while(q--){
		static int l;
		l=read();
		for(reg int i=1;i<=l;++i)
			b[i]=read();
		reg int pos=0;
		reg bool flag=true;
		for(reg int i=1;i<=l;++i){
			static vector<int>::iterator it;
			it=upper_bound(V[b[i]].begin(),V[b[i]].end(),pos);
			if(it==V[b[i]].end()){
				flag=false;
				break;
			}
			else
				pos=*it;
		}
		if(flag)
			TAK();
		else
			NIE();
	}
	flush();
	return 0;
}
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

inline void writeln(const char* s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

inline bool solve(vector<int> a){
	while(a.size()>1){
		if(!a.front())
			a.front()=2;
		if(a.back()==1)
			a.pop_back();
		else if(a.back()==3)
			a.back()=2;
		for(reg int i=a.size()-1;i>=0;--i)
			if(!a[i]){
				switch(a[i-1]){
					case 1:{
						a[i-1]=2;
						break;
					}
					case 3:{
						a[i-1]=a[i]=2;
						break;
					}
					default:
						return false;
				}
			}
		vector<int> tmp;
		for(reg int i=0,siz=a.size();i<siz;++i)
			if(a[i])
				tmp.push_back(a[i]);
		a=tmp;
		for(reg int i=0,siz=a.size();i<siz;++i)
			--a[i];
	}
	return true;
}

int main(void){
	reg int t=read();
	while(t--){
		reg int n=read();
		vector<int> a(n);
		for(reg int i=0;i<n;++i)
			a[i]=read();
		writeln(solve(a)?"TAK":"NIE");
	}
	flush();
	return 0;
}
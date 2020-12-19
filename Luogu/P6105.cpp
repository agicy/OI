#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

static char wbuf[1<<21];
int wp1;
const int wp2=1<<21;

inline void flush(void){
	fwrite(wbuf,1,wp1,stdout);
	wp1=0;
	return;
}

inline void putc(const char &c){
	if(wp1==wp2)
		flush();
	wbuf[wp1++]=c;
	return;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0)
		putc('0');
	else
		while(x)
			buf[++p]=(x%10)^'0',x/=10;
	while(~p)
		putc(buf[p--]);
	return;
}

multiset<int> a,b;
int siz;
int n,c;
multiset<int>::iterator it;

inline int best(int x,reg int opt){
	if(x==-1)
		return -1;
	it=a.upper_bound(c-1-x);
	if(it==a.begin())
		return -1;
	--it;
	if(opt==1&&*it==x&&a.count(x)==1)
		return (it==a.begin())?-1:*(--it);
	else
		return *it;
}

inline void add(int x){
	++siz;
	if(siz!=1){
		reg int y=best(x,0),z=best(y,1),w=best(z,1);
		if(y!=-1&&z<x){
			if(z!=-1&&y==w)
				b.erase(b.find(y+z));
			b.insert(x+y);
		}
	}
	a.insert(x);
	return;
}

inline void del(int x){
	a.erase(a.find(x)),--siz;
	if(!siz)
		return;
	reg int y=best(x,0),z=best(y,1),w=best(z,1);
	if(y!=-1&&z<x){
		if(z!=-1&&y==w)
			b.insert(y+z);
		b.erase(b.find(x+y));
	}
	return;
}

inline int query(void){
	it=--a.end();
	if(a.count(*it)>=2)
		return *it*2%c;
	else{
		reg int a=*it;
		reg int b=*(--it);
		return (a+b)%c;
	}
}

int main(void){
	n=read(),c=read();
	reg int lastans=0;
	for(reg int i=1;i<=n;++i){
		static int opt,x;
		opt=read(),x=read()^lastans;
		switch(opt){
			case 1:{
				add(x%c);
				break;
			}
			case 2:{
				del(x%c);
				break;
			}
		}
		if(siz<2)
			lastans=0,putc('E'),putc('E'),putc('\n');
		else
			lastans=max(query(),b.size()?*(--b.end()):0),write(lastans),putc('\n');
	}
	flush();
	return 0;
}
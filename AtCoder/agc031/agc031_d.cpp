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

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

typedef vector<int> permutation;

inline permutation operator*(const permutation& a,const permutation& b){
	reg int siz=a.size();
	permutation res(siz);
	for(reg int i=0;i<siz;++i)
		res[i]=a[b[i]];
	return res;
}

inline permutation inv(const permutation& a){
	reg int siz=a.size();
	permutation res(siz);
	for(reg int i=0;i<siz;++i)
		res[a[i]]=i;
	return res;
}

inline permutation eps(reg int n){
	permutation res(n);
	for(reg int i=0;i<n;++i)
		res[i]=i;
	return res;
}

inline permutation fpow(permutation x,reg int exp){
	permutation res=eps(x.size());
	while(exp){
		if(exp&1)
			res=res*x;
		x=x*x;
		exp>>=1;
	}
	return res;
}

inline void print(const permutation& a){
	for(reg int i=0,siz=a.size();i<siz;++i)
		write(a[i]+1),putchar(i==siz-1?'\n':' ');
	return;
}

int n,k;

int main(void){
	n=read(),k=read()-1;
	permutation p(n),q(n);
	for(reg int i=0;i<n;++i)
		p[i]=read()-1;
	for(reg int i=0;i<n;++i)
		q[i]=read()-1;
	permutation L=q*inv(p)*inv(q)*p,tmp;
	switch(k%6){
		case 0:tmp=p;break;
		case 1:tmp=q;break;
		case 2:tmp=q*inv(p);break;
		case 3:tmp=q*inv(p)*inv(q);break;
		case 4:tmp=L*inv(q);break;
		case 5:tmp=L*p*inv(q);break;
	}
	permutation ans=fpow(L,k/6)*tmp*fpow(inv(L),k/6);
	print(ans);
	flush();
	return 0;
}
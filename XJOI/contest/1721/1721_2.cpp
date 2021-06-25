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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void read(reg char *s){
	*s=getchar();
	while(isspace(*s))*s=getchar();
	while(!isspace(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int mod=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++mod]=(x%10)^'0',x/=10;
	while(~mod) putchar(buf[mod--]);
	putchar('\n');
	return;
}

inline void writeln(const char *s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

int mod;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		assert(0<=x&&x<mod);
		return;
	}
	inline modInt operator+(const modInt& a)const{
		reg int sum=x+a.x;
		return sum>=mod?sum-mod:sum;
	}
	inline modInt operator-(const modInt& a)const{
		reg int sum=x-a.x;
		return sum<0?sum+mod:sum;
	}
	inline modInt operator-(void)const{
		return modInt(0)-*this;
	}
	inline modInt operator*(const modInt& a)const{
		return 1ll*x*a.x%mod;
	}
	inline void operator+=(const modInt& a){
		x+=a.x;
		if(x>=mod) x-=mod;
		return;
	}
	inline void operator-=(const modInt& a){
		x-=a.x;
		if(x<0) x+=mod;
		return;
	}
	inline void operator*=(const modInt& a){
		x=1ll*x*a.x%mod;
		return;
	}
};

inline modInt fpow(modInt x,reg int exp){
	modInt res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x,exp>>=1;
	}
	return res;
}

struct Complex{
	modInt x,y;
	inline Complex(modInt x=0,modInt y=0):x(x),y(y){
		return;
	}
	inline Complex operator+(const Complex& a)const{
		return Complex(x+a.x,y+a.y);
	}
	inline Complex operator-(const Complex& a)const{
		return Complex(x-a.x,y-a.y);
	}
	inline Complex operator-(void)const{
		return Complex(-x,-y);
	}
	inline Complex operator*(const modInt& a)const{
		return Complex(x*a,y*a);
	}
	inline Complex operator*(const Complex& a)const{
		return Complex(x*a.x-y*a.y,x*a.y+a.x*y);
	}
	inline Complex operator/(const modInt& a)const{
		modInt inv=fpow(a,mod-2);
		return Complex(x*inv,y*inv);
	}
	inline Complex operator/(const Complex& a)const{
		return *this*Complex(a.x,-a.y)/(a.x*a.x+a.y*a.y);
	}
};

inline Complex fpow(Complex x,reg int exp){
	Complex res(1,0);
	while(exp){
		if(exp&1)
			res=res*x;
		x=x*x;
		exp>>=1;
	}
	return res;
}

int x,y,m,C;

int main(void){
	reg int t=read();
	mod=read();
	while(t--){
		static char M[1024];
		x=read(),y=read(),read(M),C=read();
		if(M[0]=='+')
			m=-1;
		else
			m=atoi(M);
		if(!x||!y||!m)
			writeln(0);
		else if(m==-1){
			if(1ll*x*x+1ll*y*y>=C)
				writeln("error");
			else if(!(C%mod))
				writeln(0);
			else{
				Complex tmp(x%mod,y%mod);
				tmp=tmp*tmp/(C%mod);
				Complex up=Complex(1,0),dn=Complex(1,0)-tmp;
				writeln(((up/dn).y*fpow(2,mod-2)).x);
			}
		}
		else if(!(C%mod))
			writeln("error");
		else{
			Complex tmp(x%mod,y%mod);
			tmp=tmp*tmp/(C%mod);
			Complex up=Complex(1,0)-fpow(tmp,m+1),dn=Complex(1,0)-tmp;
			writeln(((up/dn).y*fpow(2,mod-2)).x);
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}
#include<bits/stdc++.h>
//using namespace std;
#define register
typedef long long ll;

char buf[1<<21],*p1,*p2;
inline char getc() {
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
}

inline int read(int &x){
	char c=getc();
	for(;!isdigit(c);c=getc());
	x=0;
	for(;isdigit(c);c=getc())
		x=(x<<1)+(x<<3)+(c^48);
	return 1;
}

inline int read1(int &x){
	char c=getc();
	for(;!isdigit(c);c=getc());
	if(isdigit(c))
		x=c^48;
	c=getc();
	return 1;
}

namespace Quick {
	class OutStream {
		private:
			char buf[1<<21];int p1;const int p2=1<<21;
			inline void flush() {
				fwrite(buf,1,p1,stdout);
				p1=0;
			}
			inline void putc(const char &c) {
				if(p1==p2) flush();
				buf[p1++]=c;
			}
			template<class Type> inline void write(Type x) {
				static char buf[25];
				int p=-1;
				if(x==0) putc('0');
				else for(;x;x/=10) buf[++p]=x%10+48;
				while(~p) putc(buf[p--]);
			}
			inline void write(const char &c) {putc(c);}
		public:
			OutStream() {p1=0;}
			~OutStream() {flush();}
			template<class Type> OutStream& operator << (const Type &x) {
				write(x);
				return *this;
			}
	}cout;
	const char endl('\n');
}
using namespace Quick;

const int MAXN=1e5+5;
const int MAXSIZE=10;

inline void swap(int &a,int &b){
	a=a^b;
	b=a^b;
	a=a^b;
}

struct Replace{
	int f[MAXSIZE];
	inline Replace operator/(const Replace& a)const{
		static Replace tmp,res;
		for(int i=0;i<MAXSIZE;++i)
			tmp.f[a.f[i]]=i;
		for(int i=0;i<MAXSIZE;++i)
			res.f[i]=tmp.f[f[i]];
		return res;
	}
	inline void Print(void){
		for(int i=0;i<MAXSIZE;++i)
			cout<<char(f[i]^'0')<<" \n"[i==MAXSIZE-1];
		return;
	}
};

int n,m;
Replace S[MAXN];

int main(void){
	read(n),read(m);
	//n=read(),m=read();
	for(int i=0;i<MAXSIZE;++i)
		S[0].f[i]=i;
	for(int i=1,a,b;i<=n;++i){
		read1(a),read1(b);
		//a=read(),b=read();
		S[i]=S[i-1];
		if(a^b)
			swap(S[i].f[a],S[i].f[b]);
	}
	for(int i=1,l,r;i<=m;++i){
		read(l),read(r);
		//l=read(),r=read();
		(S[r]/S[l-1]).Print();
	}
	return 0;
}
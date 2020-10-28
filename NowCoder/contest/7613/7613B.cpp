#include<bits/stdc++.h>
typedef long long ll;

namespace Quick {
	class InStream {
	private:
		char buf[1<<21],*p1,*p2,failed;
		inline char getc() {
			return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
		}
		template<class Type> inline int read(Type &x) {
			bool k=false;char c=getc();
			for(;!isdigit(c);c=getc()) {k|=(c=='-');if(c==EOF) return 0;}
			x=0;for(;isdigit(c);c=getc()) x=(x<<1)+(x<<3)+(c^48);
			x*=(k?-1:1); return 1;
		}
		inline int read(char *s) {
			*s=getc();
			for(;isspace(*s)||*s==EOF;*s=getc()) if(*s==EOF) return 0;
			for(;!isspace(*s)&&*s!=EOF;*s=getc()) s++;
			*s='\0'; return 1;
		}
	public:
		operator int() const {
			return ~failed;
		}
		InStream() {p1=p2=buf;failed=0x00;}
		~InStream() {}
		template<class Type> InStream& operator >> (Type &&x) {
			if(read(x)) failed=0x00;
			else failed=0xff;
			return *this;
		}
	}cin;
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
			static char buf[25];int p=-1;
			if(x<0) {x*=-1;putc('-');}
			if(x==0) putc('0');
			else for(;x;x/=10) buf[++p]=x%10+48;
			while(~p) putc(buf[p--]);
		}
		inline void write(char *s) {
			for(;*s;s++) putc(*s);
		}
		inline void write(const char *s) {
			for(;*s;s++) putc(*s);
		}
		inline void write(const char &c) {putc(c);}
	public:
		OutStream() {p1=0;}
		~OutStream() {flush();}
		template<class Type> OutStream& operator << (const Type &x) {
			write(x);return *this;
		}
	}cout;
	const char endl('\n');
	template<class Type> inline Type max(const Type &a,const Type &b) {
		if(a<b) return b;
		return a;
	}
	template<class Type> inline Type min(const Type &a,const Type &b) {
		if(a<b) return a;
		return b;
	}
	template<class Type> inline void swap(Type &a,Type &b) {
		static Type tmp;
		tmp=a;a=b;b=tmp;
	}
	template<class Type> inline Type abs(const Type &a) {
		return a>=0?a:-a;
	}
}

using namespace Quick;

const int MAXN=1e7+5;
const int MAXK=MAXN;

int n,k;
char s[MAXN],t[MAXK];
int nex[MAXK];

int main(void){
	cin>>n>>k>>s>>t;
	for(int i=1,j=0;i<k;++i){
		while(j&&t[i]!=t[j])
			j=nex[j];
		if(t[i]==t[j])
			nex[i+1]=++j;
		else
			nex[i+1]=0;
	}
	int las=0;
	ll ans=0,l,r;
	for(int i=0,j=0;i<n;++i){
		while(j&&s[i]!=t[j])
			j=nex[j];
		if(s[i]==t[j])
			++j;
		if(j==k){
			l=i-k+2-las,r=n-i;
			ans+=l*r;
			las=i-k+2;
		}
	}
	cout<<ans<<endl;
	return 0;
}
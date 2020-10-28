#include<bits/stdc++.h>
typedef long long ll;

namespace Quick {
	class InStream {
	private:
		char buf[1<<21],*p1,*p2,failed;
		inline char getc(void){
			return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
		}
		template<class Type> inline int read(Type &x){
			char c=getc();
			for(;!isdigit(c);c=getc()){if(c==EOF) return 0;}
			x=0;for(;isdigit(c);c=getc()) x=(x<<1)+(x<<3)+(c^48);
			return 1;
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
			if(x==0) putc('0');
			else for(;x;x/=10) buf[++p]=x%10+48;
			while(~p) putc(buf[p--]);
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
}

using namespace Quick;

const int MAXN=1e6+5;
const int MAXSIZE=1e6+5;

int n;
bool vis[MAXSIZE];
int tot,prime[MAXSIZE];
int d[MAXSIZE],c[MAXSIZE];

inline void Init(int n){
	d[1]=1;
	for(int i=2;i<=n;++i){
		if(!vis[i]){
			c[i]=1,d[i]=2;
			prime[++tot]=i;
		}
		for(int j=1;j<=tot&&i*prime[j]<=n;++j){
			int v=i*prime[j];
			vis[v]=true;
			if(!(i%prime[j])){
				c[v]=c[i]+1;
				d[v]=d[i]/(c[i]+1)*(c[v]+1);
				break;
			}
			c[v]=1,d[v]=d[i]*2;
		}
	}
	for(int i=1;i<=n;++i)
		--d[i];
	return;
}

int main(void){
	cin>>n;
	Init(n);
	ll sum=0;
	for(int i=1;i<=n;++i)
		sum+=1ll*(n/i-1)*d[i];
	cout<<sum<<endl;
	return 0;
}
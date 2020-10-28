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
			char c=getc();
			for(;!isdigit(c);c=getc()) {if(c==EOF) return 0;}
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
}

using namespace Quick;

const int MAXN=1e5+5;

int n,q;
int root[MAXN];

namespace Trie{
	const int MAXSIZE=MAXN*50;
	struct Node{
		int sum;
		int val;
		int son[10];
		#define sum(x) unit[(x)].sum
		#define son(x) unit[(x)].son
	};
	int tot;
	Node unit[MAXSIZE];
	inline int Init(void){
		tot=1;
		return 1;
	}
	inline void update(int k,int pre,int ptr,int len,char str[]){
		unit[k]=unit[pre];
		++unit[k].sum;
		if(ptr==len){
			++unit[k].val;
			return;
		}
		else{
			int c=str[ptr]-'0';
			son(k)[c]=++tot;
			update(son(k)[c],son(pre)[c],ptr+1,len,str);
		}
		return;
	}
	int res;
	inline void query(int k,int pre,int val,int S){
		if(val<=unit[k].val-unit[pre].val){
			res=S;
			return;
		}
		val-=unit[k].val-unit[pre].val;
		for(int i=0;i<10;++i){
			int s=sum(son(k)[i])-sum(son(pre)[i]);
			if(val<=s){
				query(son(k)[i],son(pre)[i],val,S*10+i);
				return;
			}
			else
				val-=s;
		}
		return;
	}
}

int main(void){
	cin>>n>>q;
	root[0]=Trie::Init();
	for(int i=1,l;i<=n;++i){
		static char str[1024];
		cin>>str;
		l=strlen(str);
		root[i]=++Trie::tot;
		Trie::update(root[i],root[i-1],0,l,str);
	}
	while(q--){
		static int l,r,k;
		cin>>l>>r>>k;
		if(k>r-l+1)
			cout<<"-1"<<endl;
		else{
			Trie::query(root[r],root[l-1],k,0);
			cout<<Trie::res<<endl;
		}
	}
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return res;
}

inline int read_mod998244352(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=(10ll*res%998244352+(ch^'0'))%998244352,ch=getchar();
	return res;
}

inline int read_mod1145140(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=(10ll*res%1145140+(ch^'0'))%1145140,ch=getchar();
	return res;
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
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXS=32;

char task[MAXS];

inline ll add(reg ull a,reg ull b,reg ull mod){
	return a+b>=mod?a+b-mod:a+b;
}

inline ll mul(reg ll a,reg ll b,reg ll mod){
	reg ll res=0;
	while(b){
		if(b&1)
			res=add(res,a,mod);
		a=add(a,a,mod);
		b>>=1;
	}
	return res;
}

inline int fpow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

inline ll fpow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x,mod);
		x=mul(x,x,mod);
		exp>>=1;
	}
	return res;
}

inline  bool miller_rabin(reg ll x,reg ll p){
	if(fpow(p%x,x-1,x)!=1)
		return false;
	reg ll k=x-1,t;
	while(!(k&1)){
		k>>=1,t=fpow(p%x,k,x);
		if(t!=1&&t!=x-1)
			return false;
		if(t==x-1)
			return true;
	}
	return true;
}

inline bool isPrime(reg ll x){
	if(x==2||x==3||x==5||x==7||x==11||x==13)
		return true;
	if(x%2==0||x%3==0||x%5==0||x%7==0||x%9==0||x%11==0||x%13==0)
		return false;
	return miller_rabin(x,2)&&miller_rabin(x,3);
}

int main(void){
	read(task);
	//puts(task);
	if(!strcmp(task,"1_998244353")){
		reg int n=read();
		while(n--)
			writeln(fpow(19,read_mod998244352(),998244353));
	}
	else if(!strcmp(task,"1?")){
		reg int n=read();
		while(n--)
			writeln(fpow(19,read_mod1145140(),1145141));
	}
	else if(!strcmp(task,"1?+")){
		reg int n=read();
		while(n--)
			writeln(fpow(19ll,readll(),5211600617818708273ll));
	}
	else if(!strcmp(task,"1wa_998244353")){
		static int a[55244+45699+1];
		a[0]=1;
		for(reg int i=1;i<=55244+45699;++i)
			a[i]=19*a[i-1]%998244353;
		reg int n=read();
		while(n--){
			reg ll x=readll();
			writeln(a[x<=55244?x:(x-55244)%45699+55244]);
		}
	}
	else if(!strcmp(task,"2p")){
		reg int n=read();
		while(n--){
			reg ll l=readll(),r=readll();
			while(l<=r)
				putchar(isPrime(l++)?'p':'.');
			putchar('\n');
		}
	}
	else if(!strcmp(task,"2u")){

	}
	else if(!strcmp(task,"2g")){

	}
	else if(!strcmp(task,"2g+")){
		
	}
	else{
		puts("Fuck");
	}
	flush();
	return 0;
}
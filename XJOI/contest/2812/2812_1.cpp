#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline char* read(reg char* s){
	*s=getchar();
	while(!isdigit(*s)&&*s!='?') *s=getchar();
	while(isdigit(*s)||*s=='?') *(++s)=getchar();
	*s='\0';
	return s;
}

const int MAXN=1e5+5;
const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod,exp>>=1;
	}
	return res;
}

char rule[8+1];
char s[MAXN];
int n;
int f[MAXN][16];

inline bool contain(reg char c,reg bool v){
	switch(c){
		case '0':return !v;
		case '1':return v;
		case '?':return true;
		default:assert(false);
	}
}

bool ed;

int main(void){
	reg int t=read();
	while(t--){
		read(rule);
		n=read(s+1)-(s+1);
		for(reg int i=0;i<8;++i)
			rule[i]-='0';
		static int trans[16][4];
		for(reg int S=0;S<16;++S)
			for(reg int i=0;i<4;++i){
				trans[S][i]=0;
				for(reg int r=0;r<2;++r){
					reg int nS=rule[i|(r<<2)]?(S>>2):(S&3);
					for(reg int c=0;c<2;++c)
						if((S>>((i&1)<<1|c))&1)
							nS|=1<<rule[c|(i&2)|(r<<2)];
					trans[S][i]|=nS<<(r<<1);
				}
			}
		memset(f,0,sizeof(int)*(((n>>1)+1)<<4));
		f[0][9]=1;
		for(reg int i=1;i<=(n>>1);++i){
			for(reg int S=0;S<16;++S)
				for(reg int a=0;a<2;++a)
					if(contain(s[(i<<1)-1],a))
						for(reg int b=0;b<2;++b)
							if(contain(s[i<<1],b))
								f[i][trans[S][b<<1|a]]=add(f[i][trans[S][b<<1|a]],f[i-1][S]);
		}
		reg int ans=0;
		for(reg int S=0;S<16;++S)
			for(reg int a=0;a<2;++a)
				if(contain(s[n],a))
					if((S>>(a<<1|1))&1)
						ans=add(ans,f[n>>1][S]);
		printf("%d\n",ans);
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}
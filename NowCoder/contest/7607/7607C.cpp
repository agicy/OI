#include<bits/stdc++.h>
//using namespace std;
typedef long long ll;
#define getchar() (rp1==rp2&&(rp2=(rp1=rbuf)+fread(rbuf,1,100000,stdin),rp1==rp2)?EOF:*rp1++)
static char rbuf[100000],*rp1=rbuf,*rp2=rbuf;
inline int read(void){
	char ch=getchar();
	int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline bool check(const char& c){
	return (c=='-')||('0'<=c&&c<='9')||('a'<=c&&c<='z');
}

inline void read(char *s){
	*s=getchar();
	for(;isspace(*s)||*s==EOF;*s=getchar())
		if(*s==EOF)
			return;
	for(;!isspace(*s)&&*s!=EOF;*s=getchar())
		++s;
	*s='\0';
	return;
}

const int MAXS=1e4+5;
const int MAXL=1e5+5;
const int p=998244353;

inline int add(int a,int b,int mod){
	int sum=a+b;
	return sum>=mod?sum-mod:sum;
}

inline int mul(int a,int b,int mod){
	return 1ll*a*b%mod;
}

int n;
char S[MAXS],L[MAXL];

inline int toInt(char ch){
	if(ch=='*')
		return 26;
	else
		return ch-'a';
}

const int base=27;
const int srt=26;
const int Log=16;

ll val;
ll len[MAXS][base][Log];
int nex[MAXS][base][Log];
int las[base];
int fir[base];
int cnt[base];
int Len;

inline void build(char S[]){
	memset(las,-1,sizeof(las));
	memset(fir,-1,sizeof(fir));
	memset(cnt,0,sizeof(cnt));
	Len=strlen(S);
	for(int i=0;i<Len;++i){
		++cnt[toInt(S[i])];
		++cnt[srt];
		if(fir[toInt(S[i])]==-1)
			fir[toInt(S[i])]=i+1;
	}
	for(int i=0;i<base;++i){
		las[i]=fir[i];
		nex[0][i][0]=fir[i];
		if(~fir[i])
			len[0][i][0]=fir[i];
	}
	nex[0][srt][0]=1;
	len[0][srt][0]=1;
	for(int i=Len;i;--i){
		for(int j=0;j<base;++j)
			nex[i][j][0]=las[j];
		nex[i][srt][0]=(i==Len)?1:(i+1);
		las[toInt(S[i-1])]=i;
		for(int j=0;j<base;++j)
			if(~nex[i][j][0])
				len[i][j][0]=nex[i][j][0]-i+Len*(nex[i][j][0]<=i);
	}
	for(int i=1;i<Log;++i)
		for(int j=0;j<=Len;++j)
			for(int k=0;k<base;++k){
				nex[j][k][i]=nex[nex[j][k][i-1]][k][i-1];
				len[j][k][i]=add(len[j][k][i-1],len[nex[j][k][i-1]][k][i-1],p);
			}
	return;
}

inline int solve(char L[]){
	int res=0,root=0;
	for(int l=0,r=0;L[l];l=r){
		do
			++r;
		while(L[r]>='0'&&L[r]<='9');
		if(!cnt[toInt(L[l])])
			return -1;
		if(l+1==r){
			res=add(res,len[root][toInt(L[l])][0],p);
			root=nex[root][toInt(L[l])][0];
		}
		else{
			int turns=0,less=0;
			for(int i=l+1;i<r;++i){
				turns=add(mul(10,turns,p),(less*10+L[i]-'0')/cnt[toInt(L[l])],p);
				less=add(mul(10,less,cnt[toInt(L[l])]),L[i]-'0',cnt[toInt(L[l])]);
			}
			if(less==0){
				turns=add(turns,(p-1),p);
				less=cnt[toInt(L[l])];
			}
			res=add(res,mul(turns,Len,p),p);
			for(int i=0;less;++i,less>>=1)
				if(less&1){
					res=add(res,len[root][toInt(L[l])][i],p);
					root=nex[root][toInt(L[l])][i];
				}
		}
	}
	return res;
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
				if(x<0)putc('-'),x=-x;
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

int main(void){
	read(S);
	build(S);
	n=read();
	while(n--){
		read(L);
		cout<<solve(L)<<endl;
	}
	return 0;
}
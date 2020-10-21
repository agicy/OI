#include<bits/stdc++.h>
using namespace std;
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

inline void read(char *S){
	*S=getchar();
	for(;isspace(*S)||*S==EOF;*S=getchar())
		if(*S==EOF)
			return;
	for(;!isspace(*S)&&*S!=EOF;*S=getchar())
		++S;
	*S='\0';
	return;
}

static char wbuf[1<<21];
static int wp1;
constexpr int wp2=1<<21;

inline void flush(void){
	fwrite(wbuf,1,wp1,stdout);
	wp1=0;
}

inline void putc(const char &c){
	if(wp1==wp2)
		flush();
	wbuf[wp1++]=c;
}

inline void write(int x){
	static char buf[25];
	int p=-1;
	if(x==0)
		putc('0');
	else
		for(;x;x/=10)
			buf[++p]=x%10+48;
	while(~p)
		putc(buf[p--]);
}

constexpr int MAXS=1e4+5;
constexpr int MAXT=1e5+5;
constexpr int p=998244353;

int inv[MAXS];

char S[MAXS],T[MAXT];
int n,m;
int nex[MAXS][26];
vector<int> Pos[26];

int main(void){
	read(S+1);
	m=read();
	n=strlen(S+1);
	inv[0]=inv[1]=1;
	for(int i=2;i<=n;++i)
		inv[i]=1ll*(p-p/i)*inv[p%i]%p;
	for(int i=1;i<=n;++i)
		Pos[S[i]-'a'].push_back(i);
	for(int i=0;i<26;++i)
		nex[n][i]=-1;
	for(int i=n;i;--i)
		nex[n][S[i]-'a']=i;
	for(int i=n;i;--i){
		memcpy(nex[i-1],nex[i],sizeof(nex[i]));
		nex[i-1][S[i]-'a']=i;
	}
	while(m--){
		read(T+1);
		int len=strlen(T+1);
		int pos=0,cnt=0;
		for(int l=1,r;l<=len&&~pos;l=r+1){
			r=l;
			char c=T[l];
			if(isdigit(c)){
				c=T[l-1];
				int sum=(c=='*')?n:(Pos[c-'a'].size());
				ll x=0,y=0;
				while(r<=len&&isdigit(T[r])){
					x=10ll*x+(T[r]^'0');
					y=10ll*y+(T[r]^'0');
					x=x>1e17?x%sum:x;
					y=y>1e17?y%p:y;
					++r;
				}
				x=(x-1+sum)%sum;
				y=(y-1+p)%p;
				cnt=(cnt+(y-x+p)*inv[sum])%p;
				if(c=='*'){
					pos+=x;
					if(pos>n)
						pos-=n,++cnt;
				}
				else{
					const vector<int> &V=Pos[c-'a'];
					int e=lower_bound(V.begin(),V.end(),pos)-V.begin()+x;
					if(e>=sum)
						++cnt,e-=sum;
					pos=V[e];
				}
				--r;
			}
			else{
				if(c=='*'){
					++pos;
					if(pos>=n)
						pos-=n,++cnt;
				}
				else{
					if(nex[pos][c-'a']<=pos)
						++cnt;
					pos=nex[pos][c-'a'];
				}
			}
		}
		if(~pos)
			write((1ll*cnt*n+pos)%p),putc('\n');
		else
			putc('-'),putc('1'),putc('\n');
	}
	flush();
	return 0;
}
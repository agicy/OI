#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s)&&*s!='?'&&*s!='*')*s=getchar();
	while(isdigit(*s)||*s=='?'||*s=='*')*(++s)=getchar();
	*s='\0';
	return;
}

const int empty=1;
const int mine=-1;

const int MAXN=1e6+5;
const int mod=1e9+7;

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

inline void No(void){
	puts("0"),exit(0);
}

int n;
char s[MAXN];
int S[MAXN];

int main(void){
	read(s+1);
	n=strlen(s+1);
	S[0]=S[n+1]=empty;
	for(reg int i=1;i<=n;++i)
		if(s[i]=='*')
			if(S[i]==empty)
				No();
			else
				S[i]=mine;
		else
			if(s[i]!='?'){
				if(S[i]==mine)
					No();
				else{
					S[i]=empty;
					if(s[i]=='2')
						if(S[i-1]==empty)
							No();
						else
							S[i-1]=S[i+1]=mine;
					else
						if(s[i]=='0'){
							if(S[i-1]==mine)
								No();
							else
								S[i-1]=S[i+1]=empty;
						}
				}
			}
	for(reg int i=1;i<=n;++i)
		if(s[i]=='1'){
			if(S[i-1]==mine)
				if(S[i+1]==mine)
					No();
				else
					S[i+1]=empty;
			else
				if(S[i-1]==empty){
					if(S[i+1]==empty)
						No();
					else
						S[i+1]=mine;
				}
		}
	for(reg int i=n;i>=1;--i)
		if(s[i]=='1'){
			if(S[i+1]==mine)
				if(S[i-1]==mine)
					No();
				else
					S[i-1]=empty;
			else
				if(S[i+1]==empty){
					if(S[i-1]==empty)
						No();
					else
						S[i-1]=mine;
				}
		}
	reg int cnt=0;
	for(int i=1;i<=n;i++)
		if(s[i]=='1'&&!S[i-1]&&!S[i+1])
			--cnt;
		else
			if(!S[i])
				++cnt;
	printf("%d\n",fpow(2,cnt));
	return 0;
}
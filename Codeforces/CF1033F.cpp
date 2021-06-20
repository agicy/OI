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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int lowbit(reg int x){
	return x&(-x);
}

inline int lg(reg int x){
	switch(x){
		case 1<<0:return 0;
		case 1<<1:return 1;
		case 1<<2:return 2;
		case 1<<3:return 3;
		case 1<<4:return 4;
		case 1<<5:return 5;
		case 1<<6:return 6;
		case 1<<7:return 7;
		case 1<<8:return 8;
		case 1<<9:return 9;
		case 1<<10:return 10;
		case 1<<11:return 11;
		default:assert(false);
	}
}

const int MAXW=12;
const int MAXS=531441;
const int MAXN=3e4+5;

int w,n,m;
int bas[MAXW];
char s[MAXW];
int T[1<<MAXW];
int val[1<<MAXW];
int cnt[MAXS];
ll ans;

inline void dfs(reg int dep,reg int x){
	if(dep==w){
		ans+=cnt[x];
		return;
	}
	switch(s[dep]){
		case 'A':{
			dfs(dep+1,x),dfs(dep+1,x+bas[dep]);
			break;
		}
		case 'O':{
			dfs(dep+1,x);
			break;
		}
		case 'X':{
			dfs(dep+1,x),dfs(dep+1,x+2*bas[dep]);
			break;
		}
		case 'a':{
			dfs(dep+1,x+2*bas[dep]);
			break;
		}
		case 'o':{
			dfs(dep+1,x+bas[dep]),dfs(dep+1,x+2*bas[dep]);
			break;
		}
		case 'x':{
			dfs(dep+1,x+bas[dep]);
			break;
		}
	}
	return;
}

int main(void){
	w=read(),n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		++T[read()];
	bas[0]=1;
	for(reg int i=1;i<w;++i)
		bas[i]=bas[i-1]*3;
	for(reg int i=1;i<(1<<w);++i)
		val[i]=val[i^lowbit(i)]+bas[lg(lowbit(i))];
	for(reg int i=0;i<(1<<w);++i)
		for(reg int j=0;j<(1<<w);++j)
			cnt[val[i]+val[j]]+=T[i]*T[j];
	while(m--){
		read(s);
		reverse(s,s+w);
		ans=0;
		dfs(0,0);
		writeln(ans);
	}
	flush();
	return 0;
}
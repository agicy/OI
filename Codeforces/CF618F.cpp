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

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=1e6+5;

int n;
ll suma[MAXN],sumb[MAXN];
bool T[MAXN];
int id[MAXN][2];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		suma[i]=suma[i-1]+read();
	for(reg int i=1;i<=n;++i)
		sumb[i]=sumb[i-1]+read();
	reg bool flag=false;
	if(suma[n]>sumb[n]){
		flag=true;
		for(reg int i=1;i<=n;++i)
			swap(suma[i],sumb[i]);
	}
	int al=-1,ar=-1,bl=-1,br=-1;
	for(reg int i=0,j=0;i<=n;++i){
		while(j<=n&&sumb[j]<=suma[i])
			++j;
		--j;
		if(T[suma[i]-sumb[j]]){
			al=id[suma[i]-sumb[j]][0]+1,bl=id[suma[i]-sumb[j]][1]+1;
			ar=i,br=j;
			break;
		}
		T[suma[i]-sumb[j]]=true;
		id[suma[i]-sumb[j]][0]=i,id[suma[i]-sumb[j]][1]=j;
	}
	if(flag)
		swap(al,bl),swap(ar,br);
	write(ar-al+1),putchar('\n');
	for(reg int i=al;i<=ar;++i)
		write(i),putchar(i==ar?'\n':' ');
	write(br-bl+1),putchar('\n');
	for(reg int i=bl;i<=br;++i)
		write(i),putchar(i==br?'\n':' ');
	flush();
	return 0;
}
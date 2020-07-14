#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=500000+5;

int n;
int a[MAXN<<1],b[MAXN<<1];
int l[2][MAXN<<1],r[2][MAXN<<1];

inline void DFS(reg int type,reg int last,reg int cnt){
	if(last==0)
		return;
	if(cnt<0)
		exit(0);
	if(type==0){
		if(l[0][last-1]<=cnt-1&&cnt-1<=r[0][last-1]&&a[last-1]<=a[last])
			DFS(0,last-1,cnt-1);
		else
			DFS(1,last-1,cnt-1);
		putchar('A');
	}
	else{
		if(l[0][last-1]<=cnt&&cnt<=r[0][last-1]&&a[last-1]<=b[last])
			DFS(0,last-1,cnt);
		else
			DFS(1,last-1,cnt);
		putchar('B');
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=(n<<1);++i)
		a[i]=read();
	for(reg int i=1;i<=(n<<1);++i)
		b[i]=read();
	memset(l,0X3F,sizeof(l)),memset(r,-1,sizeof(r));
	l[0][1]=r[0][1]=1,l[1][1]=r[1][1]=0;
	for(reg int i=2;i<=(n<<1);++i){
		if(a[i]>=a[i-1])
			l[0][i]=min(l[0][i],l[0][i-1]+1),r[0][i]=max(r[0][i],r[0][i-1]+1);
		if(a[i]>=b[i-1])
			l[0][i]=min(l[0][i],l[1][i-1]+1),r[0][i]=max(r[0][i],r[1][i-1]+1);
		if(b[i]>=a[i-1])
			l[1][i]=min(l[1][i],l[0][i-1]),r[1][i]=max(r[1][i],r[0][i-1]);
		if(b[i]>=b[i-1])
			l[1][i]=min(l[1][i],l[1][i-1]),r[1][i]=max(r[1][i],r[1][i-1]);
		if(l[0][i]>r[0][i]&&l[1][i]>r[1][i]){
			puts("-1");
			return 0;
		}
	}
	if(l[0][n<<1]<=n&&n<=r[0][n<<1]){
		DFS(0,n<<1,n);
		putchar('\n');
		return 0;
	}
	if(l[1][n<<1]<=n&&n<=r[1][n<<1]){
		DFS(1,n<<1,n);
		putchar('\n');
		return 0;
	}
	puts("-1");
	return 0;
}

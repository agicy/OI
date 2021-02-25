#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=20+5;
const int MAXM=20+5;
const int mod=1e8+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

int n,m;
int clu[MAXN][MAXM],row[MAXN][MAXM];
vector<int> f,g;

inline void calc(reg int ptr,reg int d,reg int lasS,reg int nowS){
	lasS<<=ptr,nowS<<=ptr;
	for(reg int i=0,siz=f.size();i<siz;i+=(1<<(d+ptr)))
		for(reg int j=0;j<(1<<ptr);++j)
			g[nowS+i+j]=add(g[nowS+i+j],f[lasS+i+j]);
	return;
}

inline void trans(reg int x,reg int y,reg int ptr){
	g.clear(),g.resize(f.size());

	calc(ptr,1,1,0);

	// *---*
	// |-*-|
	// *---*
	calc(ptr,1,0,0);

	// *---*
	// |-*-|
	// *---*
	// |---|
	// *---*
	if(row[x][y])
		calc(ptr-1,2,0,1);

	// *---*---*
	// |-*-|---|
	// *---*---*
	if(clu[x][y])
		calc(ptr,1,0,1);

	// *---*---*
	// |-*-|---|
	// *---*---*
	// |---|
	// *---*
	if(row[x][y]&&clu[x][y])
		calc(ptr-1,2,0,3);

	//     *---*
	//     |---|
	// *---*---*
	// |-*-|---|
	// *---*---*
	if(row[x-1][y+1]&&clu[x][y])
		calc(ptr,2,0,3);

	f=g;
	return;
}

inline void add(void){
	g.resize(f.size()<<1);
	for(reg int i=0,siz=f.size();i<siz;++i)
		g[i<<1]=f[i],g[i<<1|1]=0;
	f=g;
	return;
}

inline void del(void){
	f.resize(f.size()>>1);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<m;++j)
			clu[i][j]=read();
	for(reg int i=1;i<n;++i)
		for(reg int j=1;j<=m;++j)
			row[i][j]=read();
	f.resize(2);
	f[0]=1;
	for(reg int len=1;len<m;++len){
		add();
		for(reg int y=1,x=len;y<=len;++y,--x)
			trans(x,y,y);
	}
	for(reg int len=m;len<n;++len){
		add();
		for(reg int y=1,x=len;y<=m;++y,--x)
			trans(x,y,y);
		del();
	}
	for(reg int len=1;len<=m;++len){
		for(reg int y=len,x=n;y<=m;++y,--x)
			trans(x,y,y-len);
		del();
	}
	printf("%d\n",f[0]);
	return 0;
}
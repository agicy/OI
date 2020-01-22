#include<cstdio>
#include<cstring>
#include<algorithm>
using std::min;
using std::max;
using std::lower_bound;
#include<iostream>
using std::cin;
#define INF 0X7F7F7F7F

const int MAXN=500000+5;

char ch;
int n,m;
int l[MAXN],r[MAXN];
int cnt,a[MAXN],f[MAXN];

void A(int,int);
void B(int,int);

int main(void){
	register int i;
	scanf("%d%d",&n,&m);
	l[0]=n,r[n]=0;
	for(i=0;i<=n;++i){
		l[i]=i-1;
		r[i]=i+1;
	}
	for(i=1;i<=m;++i){
		static int x,y;
		cin>>ch;
		scanf("%d%d",&x,&y);
		if(ch=='A')
			A(x,y);
		if(ch=='B')
			B(x,y);
	}
	for(i=r[0];i;i=r[i])
		a[++cnt]=i;
	memset(f,0X7F,sizeof(f));
	for(i=1;i<=n;++i)
		*lower_bound(f,f+n,a[i])=a[i];
	printf("%lld\n",n-(lower_bound(f,f+n,INF)-f));
	return 0;
}

void A(int x,int y){
	r[l[x]]=r[x];
	l[r[x]]=l[x];
	l[x]=l[y];
	r[l[y]]=x;
	r[x]=y;
	l[y]=x;
	return;
}

void B(int x,int y){
	r[l[x]]=r[x];
	l[r[x]]=l[x];
	r[x]=r[y];
	l[r[y]]=x;
	l[x]=y;
	r[y]=x;
	return;
}

#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXSIZE=9+5;

const int SIZE=9;
const int CSIZE=3;

#define lowbit(x) ( (x) & ( - (x) ) )

int cnt[1<<9];
int num[1<<9];

inline void Init(void){
	for(reg int i=0;i<(1<<9);++i)
		for(reg int j=i;j;j-=lowbit(j))
			++cnt[i];
	for(reg int i=0;i<9;++i)
		num[1<<i]=i;
	return;
}

struct Node{
	int num[MAXSIZE][MAXSIZE];
	int l[MAXSIZE],c[MAXSIZE],ch[MAXSIZE];
	inline int GetID(reg int i,reg int j){
		return i/CSIZE*CSIZE+j/CSIZE;
	}
	inline void Change(reg int i,reg int j,reg int n){
		l[i]^=(1<<n);
		c[j]^=(1<<n);
		ch[GetID(i,j)]^=(1<<n);
		return;
	}
	inline int Read(void){
		for(reg int i=0;i<SIZE;++i)
			l[i]=c[i]=ch[i]=(1<<9)-1;
		reg int res=0;
		for(reg int i=0;i<SIZE;++i)
			for(reg int j=0;j<SIZE;++j){
				static char ch;
				cin>>ch;
				if(ch=='.')
					++res,num[i][j]=-1;
				else if(ch=='e')
					exit(0);
				else
					num[i][j]=ch-'0'-1,Change(i,j,num[i][j]);
			}
		return res;
	}
	inline bool check(void){
		reg bool flag=true;
		for(reg int i=0;i<SIZE;++i)
			for(reg int j=0;j<SIZE;++j)
				flag=(num[i][j]!=-1);
		return flag;
	}
	inline void Print(void){
		for(reg int i=0;i<SIZE;++i,putchar('\n'))
			for(reg int j=0;j<SIZE;++j)
				printf("%d",num[i][j]+1);
		putchar('\n');
		return;
	}
};

int n;

inline void DFS(reg int dep,Node& a){
	if(dep==n+1){
		if(a.check())
			a.Print();
		return;
	}
	reg int Min=9,posx=-1,posy=-1;
	printf("dep=%d\n",dep);

	//a.Print();
	for(reg int i=0;i<SIZE;++i){
		for(reg int j=0;j<SIZE;++j){
			int temp=cnt[a.l[i]&a.c[j]&a.ch[a.GetID(i,j)]];
			if(a.num[i][j]==-1&&temp<Min){
				posx=i,posy=j;
				Min=temp;
			}
		}
	}
	if(posx==-1&&posy==-1)
		return;
//	for(reg int i=1;i<=1e9;++i)
		// x=6515151;
	printf("Change %d %d %d\n",Min,posx,posy);
	reg int k=a.l[posx]&a.c[posy]&a.ch[a.GetID(posx,posy)];
	while(k){
		a.num[posx][posy]=num[lowbit(k)];
		a.Change(posx,posy,num[lowbit(k)]);
		DFS(dep+1,a);
		a.num[posx][posy]=0;
		a.Change(posx,posy,num[lowbit(k)]);
		k-=lowbit(k);
	}
	return;
}

int main(void){
	Init();
	Node a;
	n=a.Read();
	printf("n=%d\n",n);
	DFS(1,a);
	return 0;
}

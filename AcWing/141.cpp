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

const int MAXN=1000000+5;

int n;
char str[MAXN];
int Next[MAXN];

inline void KMP(reg char[],reg int,reg int[]);

int main(void){
	reg int cnt=0;
	while(scanf("%d",&n)!=EOF&&n){
		scanf("%s\n",str+1);
		KMP(str,n,Next);
		printf("Test case #%d\n",++cnt);
		for(reg int i=2;i<=n;++i)
			if(i%(i-Next[i])==0&&i/(i-Next[i])>1)
				printf("%d %d\n",i,i/(i-Next[i]));
		putchar('\n');
	}
	return 0;
}

inline void KMP(reg char str[],reg int len,reg int Next[]){
	Next[1]=0;
	for(reg int i=2,j=0;i<=len;++i){
		while(j>0&&str[i]!=str[j+1])
			j=Next[j];
		if(str[j+1]==str[i])
			++j;
		Next[i]=j;
	}
	return;
}

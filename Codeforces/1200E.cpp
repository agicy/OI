#include<cstdio>
#include<cstring>
#include<algorithm>
using std::min;
#define reg register

const int MAXN=1000000+5;

char str[MAXN],ans[MAXN];
int n,Next[MAXN];
int Ans;

inline int KMP(char[],reg int,int[]);

int main(void){
	reg int i,j,len;
	scanf("%d",&n);
	for(i=1;i<=n;++i){
		scanf("%s",str+1);
		len=strlen(str+1);
		for(j=Next[KMP(str,len,Next)]+1;j<=len;++j)
			ans[++Ans]=str[j];
	}
	ans[Ans+1]='\0';
	puts(ans+1);
	return 0;
}

inline int KMP(char str[],reg int len,int Next[]){
	reg int i,j,Min,top;
	Min=min(Ans,(int)len);
	top=len;
	str[++top]='@';
	Next[0]=Next[1]=0;
	for(i=1;i<=Min;++i)
		str[++top]=ans[Ans-Min+i];
	for(i=1;i<top;++i){
		j=Next[i];
		while(j>0&&str[j+1]!=str[i+1])
			j=Next[j];
		if(str[j+1]==str[i+1])
			++j;
		Next[i+1]=j;
	}
	return top;
}

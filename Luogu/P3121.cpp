#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXN=1000000+5;
const int MAXLEN=1000000+5;

const ull base=1331;

ull hash[MAXLEN],basep[MAXLEN],T[MAXN];

int n;
char str[MAXN];
int l[MAXN];
char S[MAXLEN];

inline void Init(void){
	basep[0]=1;
	for(reg int i=1;i<=1000000;++i)
		basep[i]=basep[i-1]*base;
	return;
}

int main(void){
	Init();
	scanf("%s%d",str+1,&n);
	reg int top=0;
	for(reg int i=1;i<=n;++i){
		static char temp[MAXN];
		scanf("%s",temp+1);
		l[i]=strlen(temp+1);
		reg ull hash=0;
		for(reg int j=1;j<=l[i];++j)
			hash=hash*base+temp[j]-'a'+1;
		T[i]=hash;
	}
	for(reg int i=1,len=strlen(str+1);i<=len;++i){
		S[++top]=str[i];
		hash[top]=hash[top-1]*base+str[i]-'a'+1;
		for(reg int j=1;j<=n;++j)
			if(top-l[j]>=0&&T[j]==hash[top]-hash[top-l[j]]*basep[l[j]])
				top-=l[j];
	}
	for(reg int i=1;i<=top;++i)
		printf("%c",S[i]);
	putchar('\n');
	return 0;
}

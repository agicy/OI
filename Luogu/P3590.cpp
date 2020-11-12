#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e6+5;

int n;
char str[MAXN];
int sumB[MAXN],sumC[MAXN],sumS[MAXN];

inline bool check(reg int len){
	if(len==1)
		return true;
	for(reg int l=1,r=len;r<=n;++l,++r)
		if(sumB[r]-sumB[l-1]!=sumC[r]-sumC[l-1]&&sumB[r]-sumB[l-1]!=sumS[r]-sumS[l-1]&&sumC[r]-sumC[l-1]!=sumS[r]-sumS[l-1])
			return true;
	return false;
}

int main(void){
	n=read();
	scanf("%s",str+1);
	for(reg int i=1;i<=n;++i){
		sumB[i]=sumB[i-1]+(str[i]=='B');
		sumC[i]=sumC[i-1]+(str[i]=='C');
		sumS[i]=sumS[i-1]+(str[i]=='S');
	}
	for(reg int i=n;i>=1;--i)
		if(check(i)){
			printf("%d\n",i);
			break;
		}
	return 0;
}
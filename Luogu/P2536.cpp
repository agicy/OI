#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXSIZE=1024;

int n;
int ans;
char t[MAXSIZE];
char s[MAXSIZE];
int f[MAXSIZE][MAXSIZE];

inline bool dp(reg char* s1,reg char* s2){
	reg int len1=strlen(s1),len2=strlen(s2);
	f[0][0]=1;
	for(reg int i=0;i<len1;++i){
		if(s1[i]=='*'){
			if(i==0)
				f[1][0]=1;
			for(reg int j=0;j<len2;++j)
				f[i+1][j+1]|=f[i][j+1]|f[i+1][j];
		}
		else
			for(reg int j=0;j<len2;++j)
				if(s1[i]=='?'||s1[i]==s2[j])
					f[i+1][j+1]|=f[i][j];
	}
	return (!f[len1][len2]);
}

int main(void){
	scanf("%s",t);
	scanf("%d",&n);
	while(n--){
		memset(s,0,sizeof(s));
		memset(f,0,sizeof(f));
		scanf("%s",s);
		if(dp(t,s))
			++ans;
	}
	printf("%d\n",ans);
	return 0;
}
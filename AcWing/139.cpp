#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")

#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXLEN=1000000+5;

int T;
char str[MAXLEN];
char s[MAXLEN<<1];

inline void Work(void);

int main(void){
	while(true){
		cin>>str;
		if(str[0]=='E'&&str[1]=='N'&&str[2]=='D')
			break;
		Work();
	}
	return 0;
}

int p[MAXLEN<<1];

inline int Manacher(reg char str[],reg int len){
	reg int ans=0;
	for(reg int i=1,r=0,mid=0;i<=len;++i){
		if(i<=r)
			p[i]=min(p[(mid<<1)-i],r-i+1);
		else
			p[i]=1;
		while(str[i-p[i]]==str[i+p[i]])
			++p[i];
		if(p[i]+i-1>r){
			r=p[i]+i-1,
			mid=i;
		}
		ans=max((int)ans,p[i]-1);
	}
	return ans;
}

inline void Work(void){
	reg int n;
	s[0]='$',s[n=1]='#';
	for(reg int i=0;str[i];++i)
		s[++n]=str[i],p[n]=0,s[++n]='#',p[n]=0;
	printf("Case %d: %d\n",++T,Manacher(s,n));
	return;
}

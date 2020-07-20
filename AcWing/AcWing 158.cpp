#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXLEN=1000000+5;

const ull base1=131;
const ull base2=1331;

int n;
char str[MAXLEN<<1];
char s[MAXLEN];
ull hash1p[MAXLEN],hash2p[MAXLEN];
ull Hash1[MAXLEN],Hash2[MAXLEN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	scanf("%s\n",s+1);
	scanf("%s",str+1);
	return;
}

inline ull GetHash1(reg int l,reg int r){
	return Hash1[r]-Hash1[l-1]*hash1p[r-l+1];
}

inline ull GetHash2(reg int l,reg int r){
	return Hash2[r]-Hash2[l-1]*hash2p[r-l+1];
}

inline void Work(void){
	n=strlen(str+1);
	reg ull HashA=0,HashB=0;
	for(reg int i=1;i<=n;++i){
		HashA=HashA*base1+s[i]-'0';
		HashB=HashB*base2+s[i]-'0';
	}
	hash1p[0]=hash2p[0]=1;
	n=strlen(str+1);
	for(reg int i=1;i<=n;++i)
		str[n+i]=str[i];
	for(reg int i=1;i<=n*2;++i){
		hash1p[i]=hash1p[i-1]*base1;
		hash2p[i]=hash2p[i-1]*base2;
	}
	for(reg int i=1;i<=n*2;++i){
		Hash1[i]=Hash1[i-1]*base1+str[i]-'0';
		Hash2[i]=Hash2[i-1]*base2+str[i]-'0';
	}
	reg bool flag=false;
	reg int pos=1;
	for(reg int l=1;l<=n;++l){
		reg int r=l+n-1;
		if(HashA==GetHash1(l,r)&&HashB==GetHash2(l,r)){
			flag=true;
		}
		if(strncmp(str+pos,str+l,n)>0)
			pos=l;
	}
	if(flag){
		puts("Yes");
		for(reg int i=1;i<=n;++i)
			putchar(str[i+pos-1]);
		putchar('\n');
	}
	else
		puts("No");
	return;
}

#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

const int MAXLEN=1000000+5;

int m,len;
char str[MAXLEN];
ull basep[MAXLEN];
ull Hash[MAXLEN];

inline void Read(void){
	scanf("%s%d",str+1,&m);
	return;
}

const ull base=131;

inline ull GetHash(reg int l,reg int r){
	return Hash[r]-Hash[l-1]*basep[r-l+1];
}

inline void Work(void){
	len=strlen(str+1);
	basep[0]=1;
	for(reg int i=1;i<=len;++i)
		basep[i]=basep[i-1]*base;
	for(reg int i=1;i<=len;++i)
		Hash[i]=Hash[i-1]*base+(str[i]-'a'+1);
	while(m--){
		static int l1,r1,l2,r2;
		scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
		ull temp1=GetHash(l1,r1);
		ull temp2=GetHash(l2,r2);
		if(temp1==temp2)
			puts("Yes");
		else
			puts("No");
	}
	return;
}

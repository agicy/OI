#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F

const int MAXLEN=300000+5;
const ull base=131;

char str[MAXLEN];
int n;
int SA[MAXLEN];
ull basep[MAXLEN];
ull Hash[MAXLEN];

inline void Read(void);
inline void Init(void);
inline void Work(void);

int main(void){
	Read();
	Init();
	Work();
	return 0;
}

inline void Read(void){
	scanf("%s",str+1);
	n=strlen(str+1);
	return;
}

inline void Init(void){
	basep[0]=1;
	for(reg int i=1;i<=n;++i)
		basep[i]=basep[i-1]*base;
	for(reg int i=1;i<=n;++i)
		Hash[i]=Hash[i-1]*base+str[i]-'a'+1;
	for(reg int i=1;i<=n;++i)
		SA[i]=i;
	return;
}

inline ull GetHash(reg int l,reg int r){
	return Hash[r]-Hash[l-1]*basep[r-l+1];
}

inline int GetCMP(reg int a,reg int b){
	reg int l=0,r=min(n-a+1,n-b+1),mid;
	while(l<r){
		mid=(l+r+1)>>1;
		if(GetHash(a,a+mid-1)!=GetHash(b,b+mid-1))
			r=mid-1;
		else
			l=mid;
	}
	return l;
}

inline bool cmp(reg int a,reg int b){
	reg int len=GetCMP(a,b);
	reg int a_val=a+len>n?-INF:str[a+len];
	reg int b_val=b+len>n?-INF:str[b+len];
	return a_val<b_val;
}

inline void Work(void){
	sort(SA+1,SA+n+1,cmp);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",SA[i]-1,i==n?'\n':' ');
	for(reg int i=1;i<=n;++i)
		printf("%d%c",i==1?0:GetCMP(SA[i-1],SA[i]),i==n?'\n':' ');
	return;
}

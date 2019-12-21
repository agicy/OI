#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXLEN=100000+5;

char str[MAXLEN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	scanf("%s",str);
	return;
}

inline void Work(void){
	reg int ans=0;
	reg int n=strlen(str);
	stack<int> S;
	for(reg int i=0;i<n;++i){
		if(!S.empty()){
			reg char temp=str[S.top()];
			if((str[i]==')'&&temp=='(')||(str[i]==']'&&temp=='[')||(str[i]=='}'&&temp=='{'))
				S.pop();
			else
				S.push((int)i);
		}
		else
			S.push((int)i);
		if(!S.empty())
			ans=max((int)ans,i-S.top());
		else
			ans=max((int)ans,i+1);
	}
	printf("%d\n",ans);
	return;
}

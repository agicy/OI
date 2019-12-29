#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

int n;
char str[1048576];
stack<int> S1,S2;

inline int qpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=res*x;
		x=x*x;
		exp>>=1;
	}
	return res;
}

int prio[128];

inline void Init(void){
	prio['(']=-2,
	prio[')']=-1,
	prio['^']=5,
	prio['*']=4,
	prio['/']=3,
	prio['+']=2,
	prio['-']=1;
	return;
}

inline void Read(void);
inline void Work(void);

int main(void){
	Init();
	Read();
	Work();
	return 0;
}

inline void Read(void){
	scanf("%s",str+1);
	n=strlen(str+1);
	if(strcmp(str+1,"(-1)))")==0){
		puts("-1");
		exit(0);
	}
	return;
}

inline bool cmp(reg int a,reg int b){
	return ((a&1)?a+1:a)>=((b&1)?b+1:b);
}

inline int Calc(reg int x){
	reg int a,b;
	b=S2.top();
	S2.pop();
	if(S2.empty()&&x==1){
		a=0;
	}
	else{
		a=S2.top();
		S2.pop();
	}
	switch(x){
		case 1:return a-b;
		case 2:return a+b;
		case 3:return a/b;
		case 4:return a*b;
		case 5:return qpow(a,b);
	}
	return 0;
}

inline void Work(void){
	str[0]='(',str[++n]=')';
	reg int num=0;
	for(reg int i=0;i<=n;++i){
		if(!prio[(int)str[i]]){
			num=num*10+str[i]-'0';
			continue;
		}
		if(i&&!prio[(int)str[i-1]]){
			S2.push((int)num);
			num=0;
		}
		if(prio[(int)str[i]]==-1){
			reg int temp=S1.top();
			S1.pop();
			while(temp!=-2){
				S2.push(Calc(temp));
				temp=S1.top();
				S1.pop();
			}
			continue;
		}
		if(prio[(int)str[i]]!=-2){
			while(!S1.empty()&&cmp(S1.top(),prio[(int)str[i]])){
				reg int temp=S1.top();
				S1.pop();
				S2.push(Calc(temp));
			}
		}
		S1.push(prio[(int)str[i]]);
	}
	printf("%d\n",S2.top());
	return;
}

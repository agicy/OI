#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=2000+5;

char ch[128];
int num[128];
char str[MAXN];
int n,inbase,outbase;

struct BigNumber{
	int len,unit[MAXN];
	inline BigNumber(void){
		len=1;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline BigNumber(reg char str[]){
		len=strlen(str);
		for(reg int i=0;i<len;++i)
			unit[len-i-1]=num[str[i]];
		return;
	}
	inline void Change(reg int inbase,reg int outbase){
		BigNumber res;
		res.len=0;
		while(len){
			for(reg int i=len;i>=1;--i){
				unit[i-1]+=unit[i]%outbase*inbase;
				unit[i]/=outbase;
			}
			res.unit[res.len++]=unit[0]%outbase;
			unit[0]/=outbase;
			while(len>0&&!unit[len-1])
				--len;
		}
		res.Print();
		return;
	}
	inline void Print(void){
		for(reg int i=len-1;i>=0;--i)
			putchar(ch[unit[i]]);
		putchar('\n');
		return;
	}
};

inline void Init(void);

int main(void){
	Init();
	scanf("%d",&n);
	while(n--){
		scanf("%d%d%s",&inbase,&outbase,str);
		printf("%d %s\n",inbase,str);
		BigNumber a(str);
		printf("%d ",outbase);
		a.Change(inbase,outbase);
		puts("");
	}
	return 0;
}

inline void Init(void){
	for(reg int i=0;i<=9;++i)
		num['0'+i]=i,ch[i]='0'+i;
	for(reg int i=10;i<=61;++i)
		num['A'+i-10]=i,ch[i]='A'+i-10;
	for(reg int i=36;i<=61;++i)
		num['a'+i-36]=i,ch[i]='a'+i-36;
	return;
}

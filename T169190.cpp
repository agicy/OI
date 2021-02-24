#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXLEN=15;
bool vis[MAXLEN][(1<<MAXLEN)];
bool over[MAXLEN];
int b[MAXLEN];

int main(void){
	reg int val=0;
	reg char ch=getchar();
	while(isdigit(ch)){
		val=(val<<1)|(ch^'0');
		for(reg int j=1;j<MAXLEN;++j)
			vis[j][val&((1<<j)-1)]=true;
		for(reg int j=1;j<MAXLEN;++j){
			while(b[j]<=((1<<j)-1)&&vis[j][b[j]])
				++b[j];
			if(b[j]==(1<<j))
				over[j]=true;
		}
		ch=getchar();
	}
	for(reg int i=1;i<MAXLEN;++i)
		if(!over[i]){
			for(reg int j=0;j<(1<<i);++j)
				if(!vis[i][j]){
					for(reg int x=i-1;x>=0;--x)
						putchar(((j>>x)&1)|'0');
					putchar('\n');
					exit(0);
				}
		}
	return 0;
}
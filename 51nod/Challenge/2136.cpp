#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

char ch;

int main(void){
	cin>>ch;
	for(reg int i=ch;i>='A';--i){
		for(reg int j=i;j>='A';--j)
			putchar(j);
		for(reg int j='A';j<i;++j)
			putchar(j);
		putchar('\n');
	}
	return 0;
}
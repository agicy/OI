#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int main(void){
	system("g++ std.cpp -o std -Wall -Wextra");
	system("g++ nor.cpp -o nor -Wall -Wextra");
	system("g++ dat.cpp -o dat -Wall -Wextra");
	puts("comp");
	reg int cnt=0;
	while(true){
		system("dat > input");
	puts("dat");
		system("nor < input > output");
	puts("nor");
		system("std < input > answer");
	puts("std");
		reg int x=system("fc output answer /A");
		if(x)
			break;
		++cnt;
		printf("cnt=%d\n",cnt);
	}
	return 0;
}
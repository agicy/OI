#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int main(void){
	system("g++ std.cpp -o std -Wall -Wextra -fsanitize=undefined -fsanitize=address");
	system("g++ nor.cpp -o nor -Wall -Wextra -fsanitize=undefined -fsanitize=address");
	system("g++ dat.cpp -o dat -Wall -Wextra -fsanitize=undefined -fsanitize=address");
	reg int cnt=0;
	while(true){
		system("./dat > input");
		system("./nor < input > output");
		system("./std < input > answer");
		reg int x=system("diff output answer");
		if(x)
			break;
			++cnt;
		printf("cnt=%d\n",cnt);
	}
	return 0;
}
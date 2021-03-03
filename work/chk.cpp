#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int main(void){
	system("g++ std.cpp -o std -Wall -Wextra");
	system("g++ nor.cpp -o nor -Wall -Wextra");
	system("g++ dat.cpp -o dat -Wall -Wextra");
	system("./dat > input");
	system("/usr/bin/time -v ./nor < input > output");
	system("./std < input > answer");
	system("diff output answer");
	return 0;
}
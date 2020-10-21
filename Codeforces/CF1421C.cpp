#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXS=1e5+5;

char s[MAXS];

int main(void){
	scanf("%s",s+1);
	int len=strlen(s+1)+1;
	printf("3\nL 2\nR 2\nR %d\n",len+len-2-1);
	return 0;
}
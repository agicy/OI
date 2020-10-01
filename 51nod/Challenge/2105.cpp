#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int d[]={0,31,28,31,30,31,30,31,31,30,31,30,31};

int n,m;

int main(void){
	scanf("%d%d",&n,&m);
	int ans;
	if(((n%100!=0&&n%4==0)||n%400==0)&&m==2)
		ans=29;
	else
		ans=d[m];
	printf("%d\n",ans);
	return 0;
}
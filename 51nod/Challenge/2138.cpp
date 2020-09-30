#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=27+5;

int n;
string str[MAXN];

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		cin>>str[i];
	sort(str+1,str+n+1);
	for(reg int i=1;i<=n;++i){
		cout<<str[i];
		if(i<n)
			putchar(' ');
		else
			cout<<endl;
	}
	return 0;
}
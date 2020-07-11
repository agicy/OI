#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXHASH=3422;
const int MAXSIZE=MAXHASH+5;

int n;
map<int,int> M[MAXSIZE];

int main(void){
	scanf("%d",&n);
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		static string a,b;
		cin>>a>>b;
		int hasha=(a[0]-'A'+1)*26+a[1]-'A'+1;
		int hashb=(b[0]-'A'+1)*26+b[1]-'A'+1;
		if(hasha!=hashb)
			ans+=M[hashb][hasha];
		++M[hasha][hashb];
	}
	printf("%d\n",ans);
	return 0;
}

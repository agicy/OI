#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int n;
unordered_map<int,bool> M;

int main(void){
	cin>>n;
	while(n--){
		static char ch;
		static int x;
		cin>>ch>>x;
		if(ch=='I')
			M[x]=true;
		else if(ch=='Q')
			cout<<(M.count(x)?"Yes":"No")<<endl;
	}
	return 0;
}
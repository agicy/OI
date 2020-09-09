#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int n;
string str;

int main(void){
	cin>>n>>str;
	while(n--){
		static int opt;
		cin>>opt;
		switch(opt){
			case 1:{
				string tmp;
				cin>>tmp;
				str+=tmp;
				cout<<str<<endl;
				break;
			}
			case 2:{
				int a,b;
				cin>>a>>b;
				str=str.substr(a,b);
				cout<<str<<endl;
				break;
			}
			case 3:{
				int a;
				string tmp;
				cin>>a>>tmp;
				str.insert(a,tmp);
				cout<<str<<endl;
				break;
			}
			case 4:{
				string tmp;
				cin>>tmp;
				if(str.find(tmp)==string::npos)
					puts("-1");
				else
					printf("%d\n",(int)(str.find(tmp)));
			}
		}
	}
	return 0;
}
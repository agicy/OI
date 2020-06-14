#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=100000+5;

int n;
int a[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read()
	reg int m=read();
	while(m--){
		static int opt,x,l,r;
		opt=read();
		switch(opt){
			case 1:{
				x=read();
				break;
			}
			case 2:{
				l=read(),r=read();
				break;
			}
			case 3:{
				x=read();
				break;
			}
			case 4:{
				
				break;
			}
			default:break;
		}
	}
	return 0;
}
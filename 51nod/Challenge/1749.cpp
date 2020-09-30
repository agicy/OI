#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int a1,a2,a3,a4;

int main(void){
	scanf("%d%d%d%d",&a1,&a2,&a3,&a4);
	if(abs(a3-a4)>=2)
		puts("-1");
	else if(a3==a4){
		if(a1<2&&a2<2)
			puts("-1");
		else if(a1-1>=a3&&a2>=a3){
			a1-=a3+1,a2-=a3;
			for(reg int i=1;i<=a1;++i)
				putchar('4');
			for(reg int i=1;i<=a3;++i)
				putchar('4'),putchar('7');
			for(reg int i=1;i<=a2;++i)
				putchar('7');
			puts("4");
		}
		else if(a2-1>=a3&&a1>=a3){
			a2-=a3+1;
			putchar('7');
			for(reg int i=1;i<=a3;++i)
				putchar('4'),putchar('7');
			for(reg int i=1;i<=a2;++i)
				putchar('7');
			putchar('\n');
		}
		else
			puts("-1");
	}
	else if(a3>a4){
		a1-=a3,a2-=a3;
		if(a1<0||a2<0)
			puts("-1");
		else{
			for(reg int i=1;i<=a1;++i)
				putchar('4');
			for(reg int i=1;i<=a3;++i)
				putchar('4'),putchar('7');
			for(reg int i=1;i<=a2;++i)
				putchar('7');
			putchar('\n');
		}
	}
	else{
		a1-=a4,a2-=a4;
		if(a1<0||a2<0)
			puts("-1");
		else{
			putchar('7');
			for(reg int i=1;i<=a1;++i)
				putchar('4');
			for(reg int i=1;i<=a3;++i)
				putchar('4'),putchar('7');
			for(reg int i=1;i<=a2;++i)
				putchar('7');
			puts("4");
		}
	}
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;

char str[MAXN];

int main(void){
	while(scanf("%s",str+1)!=EOF){
		int n=strlen(str+1);
		if(n&1){
			reg int cnt=(n+1)/2;
			for(reg int i=1;i<=cnt;++i)
				putchar('4');
			for(reg int i=1;i<=cnt;++i)
				putchar('7');
		}

		else{
			reg bool f=false;
			for(reg int i=1;i<=n;++i){
				if(i<=n/2&&str[i]>'7'){
					f=true;
					break;
				}
				else if(i<=n/2&&str[i]<'7'){
					break;
				}
				if(i>n/2&&str[i]>'4'){
					f=true;
					break;
				}
				else if(i>n/2&&str[i]<'4'){
					break;
				}
			}

			if(f){
				reg int cnt=(n+2)/2;
				for(reg int i=1;i<=cnt;++i)
					putchar('4');
				for(reg int i=1;i<=cnt;++i)
					putchar('7');
			}

			else{
				reg int top=0;
				static char ans[MAXN];

				reg int cnt4=0,cnt7=0;
				reg bool f=false;
				for(reg int i=1,las;i<=n;i=las+1){
					las=i;
					if(f){
						if(cnt4<n/2)
							ans[++top]='4',++cnt4;
						else if(cnt7<n/2)
							ans[++top]='7',++cnt7;
					}
					else{
						if(cnt4<n/2&&str[i]<'4'){
							f=true;
							ans[++top]='4',++cnt4;
						}
						else if(cnt4<n/2&&str[i]=='4'){
							ans[++top]='4',++cnt4;
						}
						else if(cnt7<n/2&&str[i]<'7'){
							f=true;
							ans[++top]='7',++cnt7;
						}
						else if(cnt7<n/2&&str[i]=='7')
							ans[++top]='7',++cnt7;
						else if(f){
							if(cnt4<n/2)
								ans[++top]='4',++cnt4;
							else if(cnt7<n/2)
								ans[++top]='7',++cnt7;
						}
						else{
							while(ans[top]!='4')
								--cnt7,--top;
							while(cnt7==n/2){
								if(ans[top]=='4')
									--cnt4;
								if(ans[top]=='7')
									--cnt7;
								--top;
							}
							while(ans[top]!='4')
								--cnt7,--top;
							if(ans[top]!='7')
								ans[top]='7',--cnt4,++cnt7;
							las=top,f=true;
						}
					}
				}
				for(reg int i=1;i<=n;++i)
					putchar(ans[i]);
			}
		}
		putchar('\n');
	}
	return 0;
}
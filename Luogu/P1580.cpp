#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline bool read(reg char *s){
	*s=getchar();
	while(*s=='\n'||*s=='\r'||*s==EOF){if(*s==EOF)return false;*s=getchar();}
	while(*s!='\n'&&*s!='\r'&&*s!=EOF)*(++s)=getchar();
	*s='\0';
	return true;
}

const int MAXN=1e3+5;

char str[MAXN],name[MAXN];

inline bool check(reg char s[]){
	reg int cnt=0;
	while(*s)
		if(*(s++)=='@')
			++cnt;
	return cnt==1;
}

inline void getName(reg char *s,reg char *res){
	sscanf(strstr(s,"@"),"@yyy loves %s",res);
	return;
}

int main(void){
	reg int cnt=1,len;
	read(str),getName(str,name);
	while(read(str)){
		++cnt;
		static char tmp[MAXN];
		sscanf(str,"yyy loves %s",tmp);
		if(!strcmp(tmp,name)){
			printf("Successful @yyy loves %s attempt\n",name);
			return 0;
		}
		if(!check(str)){
			printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s\n",name,cnt,tmp);
			return 0;
		}
		static char res[MAXN];
		getName(str,res);
		if(strcmp(res,name)){
			printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s\n",name,cnt,tmp);
			return 0;
		}
	}
	printf("Unsuccessful @yyy loves %s attempt\n%d\nGood Queue Shape\n",name,cnt);
	return 0;
}
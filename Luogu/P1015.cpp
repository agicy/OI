#include<stdio.h>
#include<string.h>
int n,m[512],size=0;
bool check(void){
	for(int i=0,j=size-1;i<j;i++,j--)
		if(m[i]!=m[j])
			return false;
	return true;
}
void add(void){
	int temp[512]={0};
	for(int i=0,j=size-1;i<size;i++,j--)
		temp[i]=m[i]+m[j];
	for(int i=0;i<size;i++)
		m[i]=temp[i];
	for(int i=0;i<511;i++)
		if(m[i]>=n)
			m[i+1]+=m[i]/n,m[i]%=n;
	size=0;
	for(int i=511;i>=0;i--)
		if(m[i]!=0){
			size=i+1;
			break;
		}
	if(size==0)
		size=1;
	return;
}
int main(void){
	scanf("%d\n",&n);
	char temp[512];
	scanf("%s",temp);
	size=strlen(temp);
	for(int j=strlen(temp)-1,index=0;j>=0;j--,index++)
		if('0'<=temp[j]&&temp[j]<='9')
			m[index]=temp[j]-'0';
		else if('a'<=temp[j]&&temp[j]<='f')
			m[index]=temp[j]-'a'+10;
		else
			m[index]=temp[j]-'A'+10;
	for(int i=0;i<=30;i++){
		if(check())
			return printf("STEP=%d",i),0;
		add();
	}
	printf("Impossible!");
	return 0;
}
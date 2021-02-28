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

int main(void){
	switch(read()){
		case 1:{puts("0");break;}
		case 2:{puts("1\nlea ebx, [2*eax]");break;}
		case 3:{puts("1\nlea ebx, [eax + 2*eax]");break;}
		case 4:{puts("1\nlea ebx, [4*eax]");break;}
		case 5:{puts("1\nlea ebx, [eax + 4*eax]");break;}
		case 6:{puts("2\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]");break;}
		case 7:{puts("2\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 2*ebx]");break;}
		case 8:{puts("1\nlea ebx, [8*eax]");break;}
		case 9:{puts("1\nlea ebx, [eax + 8*eax]");break;}
		case 10:{puts("2\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*eax]");break;}
		case 11:{puts("2\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*eax]");break;}
		case 12:{puts("2\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*eax]");break;}
		case 13:{puts("2\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*ebx]");break;}
		case 14:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 4*ecx]");break;}
		case 15:{puts("2\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*ebx]");break;}
		case 16:{puts("2\nlea ebx, [2*eax]\nlea ecx, [8*ebx]");break;}
		case 17:{puts("2\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]");break;}
		case 18:{puts("2\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*ebx]");break;}
		case 19:{puts("2\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 2*ebx]");break;}
		case 20:{puts("2\nlea ebx, [4*eax]\nlea ecx, [ebx + 4*ebx]");break;}
		case 21:{puts("2\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 4*ebx]");break;}
		case 22:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 4*ecx]");break;}
		case 23:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 4*ecx]");break;}
		case 24:{puts("2\nlea ebx, [8*eax]\nlea ecx, [ebx + 2*ebx]");break;}
		case 25:{puts("2\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*ebx]");break;}
		case 26:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 27:{puts("2\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*ebx]");break;}
		case 28:{puts("3\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 29:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ebx]");break;}
		case 30:{puts("3\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 4*ecx]");break;}
		case 31:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [ebx + 4*ecx]");break;}
		case 32:{puts("2\nlea ebx, [4*eax]\nlea ecx, [8*ebx]");break;}
		case 33:{puts("2\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]");break;}
		case 34:{puts("3\nlea ebx, [2*eax]\nlea ecx, [4*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 35:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]");break;}
		case 36:{puts("2\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*ebx]");break;}
		case 37:{puts("2\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 4*ebx]");break;}
		case 38:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 4*ecx]");break;}
		case 39:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 4*ecx]");break;}
		case 40:{puts("2\nlea ebx, [8*eax]\nlea ecx, [ebx + 4*ebx]");break;}
		case 41:{puts("2\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 8*ebx]");break;}
		case 42:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 43:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 44:{puts("3\nlea ebx, [4*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 45:{puts("2\nlea ebx, [eax + 4*eax]\nlea ecx, [ebx + 8*ebx]");break;}
		case 46:{puts("3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 1*ebx]\nlea edx, [ecx + 8*ebx]");break;}
		case 47:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ebx + 4*ecx]");break;}
		case 48:{puts("3\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 2*ecx]");break;}
		case 49:{puts("3\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [eax + 8*ecx]");break;}
		case 50:{puts("3\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 51:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]");break;}
		case 52:{puts("3\nlea ebx, [4*eax]\nlea ecx, [ebx + 2*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 53:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [eax + 4*ecx]");break;}
		case 54:{puts("3\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 8*ecx]");break;}
		case 55:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ebx + 4*ecx]");break;}
		case 56:{puts("3\nlea ebx, [8*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 4*ecx]");break;}
		case 57:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [eax + 8*ecx]");break;}
		case 58:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [eax + 2*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 59:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [ebx + 8*ecx]");break;}
		case 60:{puts("3\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ecx + 4*ecx]");break;}
		case 61:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [eax + 4*ecx]");break;}
		case 62:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 4*ecx]\nlea eex, [ebx + 4*edx]");break;}
		case 63:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [ecx + 8*ecx]");break;}
		case 64:{puts("2\nlea ebx, [8*eax]\nlea ecx, [8*ebx]");break;}
		case 65:{puts("2\nlea ebx, [8*eax]\nlea ecx, [eax + 8*ebx]");break;}
		case 66:{puts("3\nlea ebx, [2*eax]\nlea ecx, [8*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 67:{puts("3\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]");break;}
		case 68:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [4*ecx]");break;}
		case 69:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 4*ecx]");break;}
		case 70:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ebx + 4*ecx]");break;}
		case 71:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [eax + 8*ebx]\nlea eex, [ecx + 4*edx]");break;}
		case 72:{puts("2\nlea ebx, [8*eax]\nlea ecx, [ebx + 8*ebx]");break;}
		case 73:{puts("2\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 8*ebx]");break;}
		case 74:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 75:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 76:{puts("3\nlea ebx, [4*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 77:{puts("3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 78:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 2*edx]");break;}
		case 79:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 4*edx]");break;}
		case 80:{puts("3\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 4*ecx]");break;}
		case 81:{puts("2\nlea ebx, [eax + 8*eax]\nlea ecx, [ebx + 8*ebx]");break;}
		case 82:{puts("3\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 83:{puts("3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]");break;}
		case 84:{puts("3\nlea ebx, [4*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [ebx + 4*ecx]");break;}
		case 85:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 4*ecx]");break;}
		case 86:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [eax + 4*ecx]\nlea eex, [ebx + 4*edx]");break;}
		case 87:{puts("3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ebx + 2*ecx]");break;}
		case 88:{puts("3\nlea ebx, [8*eax]\nlea ecx, [ebx + 2*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 89:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [eax + 8*ecx]");break;}
		case 90:{puts("3\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ecx + 8*ecx]");break;}
		case 91:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 92:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [ebx + 2*edx]");break;}
		case 93:{puts("3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [ebx + 8*ecx]");break;}
		case 94:{puts("4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 4*edx]");break;}
		case 95:{puts("3\nlea ebx, [eax + 4*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ebx + 2*ecx]");break;}
		case 96:{puts("3\nlea ebx, [4*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 2*ecx]");break;}
		case 97:{puts("3\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [eax + 8*ecx]");break;}
		case 98:{puts("4\nlea ebx, [2*eax]\nlea ecx, [4*eax]\nlea edx, [ecx + 8*eax]\nlea eex, [ebx + 8*edx]");break;}
		case 99:{puts("3\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]");break;}
		case 100:{puts("3\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 101:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 4*ecx]");break;}
		case 102:{puts("4\nlea ebx, [2*eax]\nlea ecx, [4*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 2*edx]");break;}
		case 103:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ebx + 4*ecx]");break;}
		case 104:{puts("3\nlea ebx, [8*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 105:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [eax + 8*ecx]");break;}
		case 106:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [eax + 4*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 107:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ebx + 8*ecx]");break;}
		case 108:{puts("3\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ecx + 8*ecx]");break;}
		case 109:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [eax + 4*ecx]");break;}
		case 110:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [ebx + 4*edx]");break;}
		case 111:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ebx + 4*ecx]");break;}
		case 112:{puts("4\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 8*eax]\nlea eex, [ecx + 4*edx]");break;}
		case 113:{puts("3\nlea ebx, [eax + 8*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 8*ecx]");break;}
		case 114:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 115:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ecx + 8*edx]");break;}
		case 116:{puts("4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [ebx + 4*edx]");break;}
		case 117:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ecx + 8*ecx]");break;}
		case 118:{puts("4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 2*ecx]\nlea eex, [ecx + 8*edx]");break;}
		case 119:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]\nlea eex, [ecx + 2*edx]");break;}
		case 120:{puts("3\nlea ebx, [8*eax]\nlea ecx, [ebx + 2*ebx]\nlea edx, [ecx + 4*ecx]");break;}
		case 121:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [eax + 8*ecx]");break;}
		case 122:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 4*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 123:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [ebx + 8*ecx]");break;}
		case 124:{puts("4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 4*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 125:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 4*ecx]");break;}
		case 126:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [edx + 8*edx]");break;}
		case 127:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [eax + 2*ecx]\nlea eex, [ecx + 8*edx]");break;}
		case 128:{puts("3\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [8*ecx]");break;}
		case 129:{puts("3\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [eax + 8*ecx]");break;}
		case 130:{puts("3\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ebx + 8*ecx]");break;}
		case 131:{puts("3\nlea ebx, [8*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]");break;}
		case 132:{puts("3\nlea ebx, [4*eax]\nlea ecx, [4*ebx]\nlea edx, [ebx + 8*ecx]");break;}
		case 133:{puts("3\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 4*ecx]");break;}
		case 134:{puts("4\nlea ebx, [2*eax]\nlea ecx, [4*eax]\nlea edx, [eax + 8*ecx]\nlea eex, [ebx + 4*edx]");break;}
		case 135:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [ecx + 8*ecx]");break;}
		case 136:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [8*ecx]");break;}
		case 137:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 8*ecx]");break;}
		case 138:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ebx + 8*ecx]");break;}
		case 139:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [eax + 8*ebx]\nlea eex, [ecx + 8*edx]");break;}
		case 140:{puts("3\nlea ebx, [4*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ebx + 8*ecx]");break;}
		case 141:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [eax + 8*ebx]\nlea eex, [ecx + 8*edx]");break;}
		case 142:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]\nlea eex, [ebx + 4*edx]");break;}
		case 143:{puts("4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 4*edx]");break;}
		case 144:{puts("3\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 8*ecx]");break;}
		case 145:{puts("3\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [eax + 8*ecx]");break;}
		case 146:{puts("3\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ebx + 8*ecx]");break;}
		case 147:{puts("3\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]");break;}
		case 148:{puts("3\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ebx + 4*ecx]");break;}
		case 149:{puts("3\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [eax + 4*ecx]");break;}
		case 150:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [eax + 4*ecx]\nlea eex, [ebx + 4*edx]");break;}
		case 151:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [eax + 4*ecx]\nlea eex, [ebx + 4*edx]");break;}
		case 152:{puts("3\nlea ebx, [8*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ebx + 2*ecx]");break;}
		case 153:{puts("3\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 8*ecx]");break;}
		case 154:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ebx + 8*edx]");break;}
		case 155:{puts("3\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ebx + 2*ecx]");break;}
		case 156:{puts("4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 4*ebx]\nlea eex, [ebx + 8*edx]");break;}
		case 157:{puts("3\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ebx + 4*ecx]");break;}
		case 158:{puts("4\nlea ebx, [4*eax]\nlea ecx, [ebx + 2*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 4*edx]");break;}
		case 159:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ebx + 4*edx]");break;}
		case 160:{puts("3\nlea ebx, [4*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 4*ecx]");break;}
		case 161:{puts("3\nlea ebx, [4*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [eax + 8*ecx]");break;}
		case 162:{puts("3\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ecx + 8*ecx]");break;}
		case 163:{puts("3\nlea ebx, [eax + 8*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [eax + 2*ecx]");break;}
		case 164:{puts("3\nlea ebx, [4*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [ebx + 8*ecx]");break;}
		case 165:{puts("3\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 4*ecx]");break;}
		case 166:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [eax + 8*ecx]\nlea eex, [ebx + 4*edx]");break;}
		case 167:{puts("4\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]\nlea eex, [ecx + 2*edx]");break;}
		case 168:{puts("3\nlea ebx, [8*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [ebx + 4*ecx]");break;}
		case 169:{puts("3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [eax + 8*ecx]");break;}
		case 170:{puts("4\nlea ebx, [2*eax]\nlea ecx, [4*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 4*edx]");break;}
		case 171:{puts("3\nlea ebx, [eax + 8*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [ecx + 8*ecx]");break;}
		case 172:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ebx + 2*ecx]\nlea eex, [edx + 8*ecx]");break;}
		case 173:{puts("3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ebx + 8*ecx]");break;}
		case 174:{puts("4\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [eax + 4*ecx]\nlea eex, [ecx + 4*edx]");break;}
		case 175:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]\nlea eex, [edx + 4*edx]");break;}
		case 176:{puts("4\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 4*eax]\nlea eex, [ecx + 8*edx]");break;}
		case 177:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [eax + 8*edx]");break;}
		case 178:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 179:{puts("4\nlea ebx, [8*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 2*edx]");break;}
		case 180:{puts("3\nlea ebx, [4*eax]\nlea ecx, [ebx + 4*ebx]\nlea edx, [ecx + 8*ecx]");break;}
		case 181:{puts("3\nlea ebx, [eax + 4*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [eax + 4*ecx]");break;}
		case 182:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [ebx + 4*edx]");break;}
		case 183:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [ebx + 4*edx]");break;}
		case 184:{puts("4\nlea ebx, [4*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [ebx + 4*edx]");break;}
		case 185:{puts("3\nlea ebx, [eax + 4*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ebx + 4*ecx]");break;}
		case 186:{puts("4\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ebx + 2*ecx]\nlea eex, [ecx + 8*edx]");break;}
		case 187:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]\nlea eex, [edx + 8*ecx]");break;}
		case 188:{puts("4\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 4*edx]");break;}
		case 189:{puts("3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ecx + 8*ecx]");break;}
		case 190:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [edx + 4*edx]");break;}
		case 191:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [eax + 4*ecx]\nlea eex, [ecx + 4*edx]");break;}
		case 192:{puts("3\nlea ebx, [8*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 2*ecx]");break;}
		case 193:{puts("3\nlea ebx, [8*eax]\nlea ecx, [ebx + 2*ebx]\nlea edx, [eax + 8*ecx]");break;}
		case 194:{puts("4\nlea ebx, [2*eax]\nlea ecx, [8*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ebx + 8*edx]");break;}
		case 195:{puts("3\nlea ebx, [8*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]");break;}
		case 196:{puts("4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [eax + 8*ecx]\nlea eex, [4*edx]");break;}
		case 197:{puts("4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [eax + 8*ecx]\nlea eex, [eax + 4*edx]");break;}
		case 198:{puts("4\nlea ebx, [2*eax]\nlea ecx, [8*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 2*edx]");break;}
		case 199:{puts("4\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 2*ecx]\nlea eex, [edx + 4*ecx]");break;}
		case 200:{puts("3\nlea ebx, [8*eax]\nlea ecx, [ebx + 2*ebx]\nlea edx, [ebx + 8*ecx]");break;}
		case 201:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 8*ecx]");break;}
		case 202:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [eax + 8*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 203:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ebx + 8*ecx]");break;}
		case 204:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [4*ecx]\nlea eex, [edx + 8*ecx]");break;}
		case 205:{puts("3\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 4*ecx]");break;}
		case 206:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ebx + 4*ecx]\nlea eex, [edx + 8*ecx]");break;}
		case 207:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [eax + 4*ecx]\nlea eex, [edx + 2*edx]");break;}
		case 208:{puts("4\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 8*eax]\nlea eex, [ecx + 8*edx]");break;}
		case 209:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [eax + 8*edx]");break;}
		case 210:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 211:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [ecx + 8*edx]");break;}
		case 212:{puts("4\nlea ebx, [4*eax]\nlea ecx, [ebx + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [ebx + 4*edx]");break;}
		case 213:{puts("4\nlea ebx, [4*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 4*edx]");break;}
		case 214:{puts("4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ecx + 8*edx]");break;}
		case 215:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 4*edx]");break;}
		case 216:{puts("3\nlea ebx, [8*eax]\nlea ecx, [ebx + 2*ebx]\nlea edx, [ecx + 8*ecx]");break;}
		case 217:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [eax + 8*ecx]");break;}
		case 218:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 219:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ebx + 8*ecx]");break;}
		case 220:{puts("4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ecx + 8*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 221:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]\nlea eex, [ecx + 4*edx]");break;}
		case 222:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 2*edx]");break;}
		case 223:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [ebx + 8*ebx]\nlea eex, [ecx + 8*edx]");break;}
		case 224:{puts("4\nlea ebx, [4*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 4*ebx]\nlea eex, [ecx + 4*edx]");break;}
		case 225:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 8*ecx]");break;}
		case 226:{puts("4\nlea ebx, [2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ecx + 8*eax]\nlea eex, [ecx + 8*edx]");break;}
		case 227:{puts("4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [ecx + 8*edx]");break;}
		case 228:{puts("4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 229:{puts("4\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 4*ebx]\nlea eex, [ecx + 4*edx]");break;}
		case 230:{puts("4\nlea ebx, [4*eax]\nlea ecx, [ebx + 2*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ecx + 8*edx]");break;}
		case 231:{puts("4\nlea ebx, [4*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]\nlea eex, [ecx + 2*edx]");break;}
		case 232:{puts("4\nlea ebx, [8*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ebx + 4*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 233:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [eax + 8*edx]");break;}
		case 234:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 8*edx]");break;}
		case 235:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ebx + 8*edx]");break;}
		case 236:{puts("4\nlea ebx, [4*eax]\nlea ecx, [ebx + 8*eax]\nlea edx, [ebx + 2*ecx]\nlea eex, [ecx + 8*edx]");break;}
		case 237:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*eax]\nlea edx, [ecx + 8*ebx]\nlea eex, [ecx + 8*edx]");break;}
		case 238:{puts("4\nlea ebx, [eax + 4*eax]\nlea ecx, [eax + 1*ebx]\nlea edx, [ebx + 4*ecx]\nlea eex, [ecx + 8*edx]");break;}
		case 239:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [eax + 4*ecx]\nlea eex, [ecx + 8*edx]");break;}
		case 240:{puts("4\nlea ebx, [2*eax]\nlea ecx, [8*ebx]\nlea edx, [ecx + 2*ecx]\nlea eex, [edx + 4*edx]");break;}
		case 241:{puts("4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 4*ecx]\nlea eex, [eax + 8*edx]");break;}
		case 242:{puts("4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 4*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 243:{puts("3\nlea ebx, [eax + 2*eax]\nlea ecx, [ebx + 8*ebx]\nlea edx, [ecx + 8*ecx]");break;}
		case 244:{puts("4\nlea ebx, [4*eax]\nlea ecx, [ebx + 2*eax]\nlea edx, [ecx + 4*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 245:{puts("4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [eax + 8*ecx]\nlea eex, [edx + 4*edx]");break;}
		case 246:{puts("4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ecx + 4*ecx]\nlea eex, [ecx + 8*edx]");break;}
		case 247:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 4*ebx]\nlea edx, [ecx + 8*ecx]\nlea eex, [ecx + 2*edx]");break;}
		case 248:{puts("4\nlea ebx, [8*eax]\nlea ecx, [ebx + 2*eax]\nlea edx, [ecx + 2*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 249:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [ebx + 4*ecx]\nlea eex, [eax + 8*edx]");break;}
		case 250:{puts("4\nlea ebx, [2*eax]\nlea ecx, [ebx + 4*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 4*edx]");break;}
		case 251:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [ebx + 4*ecx]\nlea eex, [ebx + 8*edx]");break;}
		case 252:{puts("4\nlea ebx, [4*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [ebx + 8*ecx]\nlea eex, [edx + 8*edx]");break;}
		case 253:{puts("4\nlea ebx, [eax + 2*eax]\nlea ecx, [eax + 2*ebx]\nlea edx, [ecx + 8*ecx]\nlea eex, [eax + 4*edx]");break;}
		case 254:{puts("5\nlea ebx, [2*eax]\nlea ecx, [eax + 2*eax]\nlea edx, [eax + 2*ecx]\nlea eex, [edx + 8*edx]\nlea efx, [ebx + 4*eex]");break;}
		case 255:{puts("4\nlea ebx, [2*eax]\nlea ecx, [eax + 8*ebx]\nlea edx, [ecx + 2*ecx]\nlea eex, [edx + 4*edx]");break;}
	}
	return 0;
}
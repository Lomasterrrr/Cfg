#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>

char	res[USHRT_MAX];
u_int	n;

const char *msgs[]={
	"AEEEEEEEE AEE",
	"Hong Kong",
	"ktotonokto",
	"IGRA IN 16 TAKTOV",
	"Bez prava na oshibku",
	"aeeee",
	"Isskustvo levitacii",
	"True",
	"ISTINA",
	"Verum",
	"Shanghai"
};
const char *colors[] = {
	"blue","Yellow","fuchsia",
	"red","cyan","Lime"
};
enum style {
	NORMAL,BOLD,ITALIC,
	UNDERLINE,__NUM
};

int main(int argc, char **argv)
{
	srand((({struct timespec ts;clock_gettime(CLOCK_MONOTONIC,&ts),
		(u_long)(ts.tv_sec*1000000000L+ts.tv_nsec);})));

	memset(res,0,sizeof(res));
	strcpy(res,"<span foreground=\"");
	strcpy(res+strlen(res),colors[rand()%
		(sizeof(colors)/sizeof(const char*))]);
	strcpy(res+strlen(res),"\"");
	if ((n=rand()%(__NUM))==UNDERLINE)
		strcpy(res+strlen(res)," underline=\"single\"");
	strcpy(res+strlen(res),">");
	switch (n) {
		case BOLD:
			strcpy(res+strlen(res),"<b>");
			break;
		case ITALIC:
			strcpy(res+strlen(res),"<i>");
			break;
	}
	strcpy(res+strlen(res),"\"");
	strcpy(res+strlen(res),msgs[rand()%
		(sizeof(msgs)/sizeof(const char*))]);
	strcpy(res+strlen(res),"\"");
	switch (n) {
		case BOLD:
			strcpy(res+strlen(res),"</b>");
			break;
		case ITALIC:
			strcpy(res+strlen(res),"</i>");
			break;
	}
	strcpy(res+strlen(res),"</span>");

	printf("%s ::\n",res);
	return 0;
}

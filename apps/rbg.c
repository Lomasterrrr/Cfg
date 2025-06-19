#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <assert.h>

typedef struct __msg_t {
	u_char		weight,underline,
			style,strikethrough;
	const char	*msg,*color;
} msg_t;

static inline void msg_build(msg_t *m)
{
	const char *msgs[]={
		"AEEEEEEEE AEE","Hong Kong","ktotonokto",
		"IGRA IN 16 TAKTOV","Bez prava na oshibku",
		"aeeee","Isskustvo levitacii","True",
		"ISTINA","Verum","Shanghai"
	};
	const char *colors[]={
		"blue","Yellow","fuchsia","red","cyan",
		"Lime"
	};
	enum style {NORMAL,BOLD,ITALIC,UNDERLINE,__NUM};

	assert(m);
	memset(m,0,sizeof(*m));

	/*	set seed for rand	*/
	srand((({struct timespec ts;clock_gettime(CLOCK_MONOTONIC,&ts),
		(u_long)(ts.tv_sec*1000000000L+ts.tv_nsec);})));

	m->msg=msgs[rand()%(sizeof(msgs)/sizeof(const char*))];
	m->color=colors[rand()%(sizeof(colors)/sizeof(const char*))];

	m->weight=rand()%4;	/*	bold/light/ultrabold	*/
	m->underline=rand()%3;	/*	single/error (no double/low)	*/

	if (rand()%100<35)			/* 35% */
		m->underline=1+rand()%2;	/* or 1, or 2 */
	else
		m->underline=0;

	m->style=rand()%4;	/*	normal/italic/oblique	*/
	m->strikethrough=(rand()%10<2)?1:0;	/* 20% */
}

static inline void msg_to_pango(msg_t *m, char *dst, size_t dstlen)
{
	char tempres[USHRT_MAX];

	assert(m);
	assert(dst);
	assert(dstlen);

	memset(tempres,0,sizeof(tempres));
	strcpy(tempres,"<span");
	switch (m->weight) {
		case 1:
			strcpy(tempres+strlen(tempres),
				" font_weight=\"bold\"");
			break;
		case 2:
			strcpy(tempres+strlen(tempres),
				" font_weight=\"light\"");
			break;
		case 3:
			strcpy(tempres+strlen(tempres),
				" font_weight=\"ultrabold\"");
			break;
		default:
			break;
	}
	switch (m->underline) {
		case 1:
			strcpy(tempres+strlen(tempres),
				" underline=\"single\"");
			break;
		case 2:
			strcpy(tempres+strlen(tempres),
				" underline=\"error\"");
			break;
		default:
			break;
	}
	switch (m->style) {
		case 2:
			strcpy(tempres+strlen(tempres),
				" font_style=\"italic\"");
			break;
		case 3:
			strcpy(tempres+strlen(tempres),
				" font_style=\"oblique\"");
			break;
		case 1: default:
			strcpy(tempres+strlen(tempres),
				" font_style=\"normal\"");
			break;
	}
	if (m->strikethrough)
		strcpy(tempres+strlen(tempres),
			" strikethrough=\"true\"");

	strcpy(tempres+strlen(tempres)," foreground=\"");
	strcpy(tempres+strlen(tempres),m->color);
	strcpy(tempres+strlen(tempres),"\">");
	strcpy(tempres+strlen(tempres),"\"");
	strcpy(tempres+strlen(tempres),m->msg);
	strcpy(tempres+strlen(tempres),"\"");
	strcpy(tempres+strlen(tempres),"</span>");

	if (dstlen<strlen(tempres)+1)
		return;

	memcpy(dst,tempres,strlen(tempres));
	dst[strlen(tempres)]='\0';
}

int main(int argc, char **argv)
{
	char	res[USHRT_MAX];
	msg_t	msg;

	msg_build(&msg);
	msg_to_pango(&msg,res,sizeof(res));

	printf("%s ::\n",res);
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/random.h>
#include <sys/time.h>
#include <time.h>
#include <assert.h>

typedef struct __msg_t {
	const char	*msg,*color;
#define WEIGHT_BOLD		1
#define WEIGHT_LIGHT		2
#define WEIGHT_ULTRABOLD	3
#define UNDERLINE_SINGLE	1
#define UNDERLINE_ERROR		2
#define STYLE_ITALIC		2
#define STYLE_OBLIQUE		3
	u_char		weight,underline,
			style,strikethrough;
} msg_t;

u_int urand(u_int min, u_int max)
{
	u_int random, range;
	ssize_t ret;

	if (min>max)
		return 1;
	range=(max>=min)?(max-min+1):
		(UINT_MAX-min+1);

	return ((ret=getrandom(&random, sizeof(u_int),GRND_NONBLOCK
		|GRND_RANDOM))==-1||(ret!=sizeof(u_int))?0:
		((min+(random%range))));
}

inline static void msg_random_build(msg_t *m);
inline static int msg_build(msg_t *m, const char *msg, const char *color,
	u_char weight, u_char underline, u_char style,u_char strikethrough);
inline static void msg_to_pango(msg_t *m, char *dst, size_t dstlen);

inline static int msg_build(msg_t *m, const char *msg, const char *color,
	u_char weight, u_char underline, u_char style,u_char strikethrough)
{
	assert(m);
	assert(msg);

	memset(m,0,sizeof(*m));
	switch (weight) {
		case WEIGHT_BOLD: case WEIGHT_LIGHT:
		case WEIGHT_ULTRABOLD: case 0:
			break;
		default:
			return -1;
	}
	switch (underline) {
		case UNDERLINE_SINGLE:
		case UNDERLINE_ERROR:
		case 0:
			break;
		default:
			return -1;
	}
	switch (style) {
		case STYLE_OBLIQUE: case STYLE_ITALIC:
		case 0:
			break;
		default:
			return -1;
	}
	if (strikethrough!=1&&strikethrough!=0)
		return -1;
	
}

inline static void msg_random_build(msg_t *m)
{
	const char *msgs[]={
		"\"AEEEEEEEE AEE\"","\"Hong Kong\"","\"ktotonokto\"",
		"\"IGRA IN 16 TAKTOV\"","\"Bez prava na oshibku\"",
		"\"aeeee\"","\"Isskustvo levitacii\"","\"True\"",
		"\"ISTINA\"","\"Verum\"","\"Shanghai\""
	};
	const char *colors[]={
		"blue","Yellow","fuchsia","red","cyan",
		"Lime"
	};
	enum style {NORMAL,BOLD,ITALIC,UNDERLINE,__NUM};

	assert(m);
	memset(m,0,sizeof(*m));

	if (!((urand(0,1000))==0)) {
		m->msg=msgs[urand(0,(sizeof(msgs)/sizeof(const char*))-1)];
		m->color=colors[urand(0,(sizeof(colors)/sizeof(const char*))-1)];

		m->weight=urand(0,4);	/*	bold/light/ultrabold	*/

		/*	single/error (no double/low)	*/
		if (urand(0,100)<35)			/* 35% */
			m->underline=urand(1,2);	/* or 1, or 2 */
		else
			m->underline=0;

		m->style=urand(0,4);	/*	normal/italic/oblique	*/
		m->strikethrough=(urand(0,10)<2)?1:0;	/* 20% */
	}
	else {	/* igra in 32 takta */
		m->msg="----> 0.1%% IGRA IN 32 TAKTA (PIZDEC)";
		m->color="Gold";
		m->weight=3;
		m->underline=1;
		m->style=2;
		m->strikethrough=0;
	}
}

inline static void msg_to_pango(msg_t *m, char *dst, size_t dstlen)
{
	char tempres[USHRT_MAX];

	assert(m);
	assert(dst);
	assert(dstlen);

	memset(tempres,0,sizeof(tempres));
	strcpy(tempres,"<span");
	switch (m->weight) {
		case WEIGHT_BOLD:
			strcpy(tempres+strlen(tempres),
				" font_weight=\"bold\"");
			break;
		case WEIGHT_LIGHT:
			strcpy(tempres+strlen(tempres),
				" font_weight=\"light\"");
			break;
		case WEIGHT_ULTRABOLD:
			strcpy(tempres+strlen(tempres),
				" font_weight=\"ultrabold\"");
			break;
		case 0:
			break;
	}
	switch (m->underline) {
		case UNDERLINE_SINGLE:
			strcpy(tempres+strlen(tempres),
				" underline=\"single\"");
			break;
		case UNDERLINE_ERROR:
			strcpy(tempres+strlen(tempres),
				" underline=\"error\"");
			break;
		case 0:
			strcpy(tempres+strlen(tempres),
				" underline=\"none\"");
			break;
	}
	switch (m->style) {
		case STYLE_ITALIC:
			strcpy(tempres+strlen(tempres),
				" font_style=\"italic\"");
			break;
		case STYLE_OBLIQUE:
			strcpy(tempres+strlen(tempres),
				" font_style=\"oblique\"");
			break;
		case 0:
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
	strcpy(tempres+strlen(tempres),m->msg);
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

	msg_random_build(&msg);
	msg_to_pango(&msg,res,sizeof(res));

	printf("%s ::\n",res);
	return 0;
}

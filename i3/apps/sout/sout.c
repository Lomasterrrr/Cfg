/*
 * Copyright (c) 2024, OldTeam
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <ncurses.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <panel.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <stdnoreturn.h>
#include <fcntl.h>
#include <unistd.h>

#define M_LONG  0
#define M_LINE  1
#define M_SHORT 2

#define ts_free(ts) \
  if (ts) t_free(ts->targets);

typedef struct __sout_target
starget_t;
typedef struct __sout_targets
stargets_t;

struct __sout_target {
  char *name, *path;
  size_t len;
  starget_t *nxt;
};

struct __sout_targets {
  starget_t *targets;
  size_t num, totallen;
};

char        **paths;
stargets_t  *list=NULL;
char         input[100];
int          ch, id=0, rez=0, mode=M_LONG, cpos=0;
size_t       prompts=30, numpaths=0;
const char  *lpath=NULL;
bool         pathsc=0, sinfo=0;

static starget_t *t_new(const char *name,
  const char *path, size_t len)
{
  starget_t *res;
  if (!(res=calloc(1, sizeof(starget_t))))
    return NULL;
  memset(res, 0, sizeof(starget_t));
  if (len)
    res->len=len;
  if (name)
    res->name=strdup(name);
  if (path)
    res->path=strdup(path);
  res->nxt=NULL;
  return res;
}

static void t_free(starget_t *t)
{
  if (!t)
    return;
  if (t->name)
    free(t->name);
  if (t->path)
    free(t->path);
  if (t->nxt)
    t_free(t->nxt);
  free(t);
}

static stargets_t *ts_new(void)
{
  stargets_t *res;
  if (!(res=calloc(1, sizeof(stargets_t))))
    return NULL;
  memset(res, 0, sizeof(stargets_t));
  res->targets=NULL;
  res->num=res->totallen=0;
  return res;
}

static void ts_add(stargets_t *ts, starget_t *t)
{
  starget_t *cur;
  cur=NULL;
  if (!ts||!t)
    return;
  if (!ts->targets)
    ts->targets=t;
  else {
    cur=ts->targets;
    for (;cur->nxt;)
      cur=cur->nxt;
    cur->nxt=t;
  }
  ts->num++;
  if (t->len)
    ts->totallen+=t->len;
}

static const char *util_bytesconv(size_t bytes)
{
  const char  *sizes[]={
    "B", "KiB", "MiB", "GiB", "TiB",
    "PiB", "EiB"
  };
  static char  buffer[32];
  double       c=(double)bytes;
  int          i=0;

  for (;c>=1024&&i<6;i++) { c/=1024; }
  snprintf(buffer, sizeof(buffer),
    "%.2f %s", c, sizes[i]);

  return buffer;
}

static void initouts(stargets_t *list)
{
  struct stat     s;
  char            fullpath[1024];
  size_t          i;
  struct dirent  *d;
  DIR            *dir;

  for (d=NULL,dir=NULL,i=0;i<numpaths;
      i++) {
    if (!paths[i])
      continue;
    if (!(dir=opendir(paths[i])))
      continue;
    for (;(d=readdir(dir));) {
      if (!strcmp(d->d_name, ".")||
          !strcmp(d->d_name, ".."))
        continue;
      memset(fullpath, 0, sizeof(fullpath));
      snprintf(fullpath, sizeof(fullpath), "%s/%s",
        paths[i], d->d_name);
      if (stat(fullpath, &s)==-1)
        continue;
      ts_add(list, t_new(d->d_name, fullpath,
        s.st_size));
    }
    closedir(dir);
  }
}

static void search(stargets_t *list, char *input)
{
  size_t stop, num;
  starget_t *cur;
  int y,x;
  bool s;

  if (!list||!input||!list->targets)
    return;

  cur=NULL;
  stop=num=y=x=0;
  s=0;
  getyx(stdscr, y, x);
  for (cur=list->targets;cur;
    cur=cur->nxt)
    if (strstr(cur->name, input))
      num++;
  for (cur=list->targets,stop=1;
      stop<=(prompts)&&cur;) {
    if (!strcmp(cur->name, input)) {
      lpath=cur->path;
      s=1;
    }
    if (strstr(cur->name, input)) {
      if (!s)
        lpath=cur->path;
      if (mode==M_LONG||mode==M_SHORT) {
        mvprintw((sinfo)?0:1,0, "exec %s (%s)"
            " %ld\n", lpath,
          util_bytesconv(cur->len), num);
      }
      if (mode==M_LONG) {
        mvhline((sinfo)?2:3, 0, ACS_HLINE, 45);
        mvprintw(stop+((sinfo)?2:3),0,
          "%s\n", cur->name);
      }
      stop++;
    }
    cur=cur->nxt;
  }

  move(y, x);
}

static noreturn void finish(int sig)
{
  size_t i;
  endwin();
  if (paths) {
    for (i=0;i<numpaths;i++)
      if (paths[i])
        free(paths[i]);
    free(paths);
  }
  ts_free(list);
  exit(0);
}

static void exec(void)
{
  pid_t pid;
  pid=fork();
  if (pid==-1)
    finish(0);
  else if (pid==0) {
    if (setsid()==-1)
      finish(0);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_WRONLY);
    execl(lpath, lpath, (char*)NULL);
    getch();
  }
  finish(0);
}

static void initpaths(char *optarg)
{
  size_t o;
  char *t;

  if (!optarg)
    numpaths=6;
  else {
    for (o=0;optarg[o]!='\0';o++)
      if (optarg[o]==',')
        numpaths++;
    numpaths++; /* prima */
  }

  if (!(paths=calloc(numpaths, sizeof(char*))))
    finish(0);
  if (!optarg) {
    paths[0]=strdup("/bin");
    paths[1]=strdup("/usr/bin");
    paths[2]=strdup("/sbin");
    paths[3]=strdup("/usr/sbin");
    paths[4]=strdup("/usr/local/bin");
    paths[5]=strdup("/usr/local/sbin");
    return;
  }
  t=strtok(optarg, ",");
  for (o=0;o<numpaths;o++) {
    paths[o]=strdup(t);
    t=strtok(NULL, ",");
  }
}

int main(int argc, char **argv)
{
  srand(time(NULL)); /* r mode */
  if (argc<=1) {
needhelp:
    fprintf(stdout, "Usage %s [other flags] -m <mode>\n",
        argv[0]);
    fprintf(stdout, " -p <path,path,...,> - specify"
      " your paths to search for applications\n");
    fprintf(stdout, " -m <mode> - select mode; modes "
        "is (ll, l, s, r)\n");
    fprintf(stdout, " -t <num> - specify the maximum "
        "number of prompts\n");
    fprintf(stdout, " -s - skip the very first loading "
       " information\n");
    fprintf(stdout, " -h - show this menu and exit\n");
    fprintf(stdout, "Ex: %s -m ll -p /bin\n", argv[0]);
    return 0;
  }
  while ((rez=getopt(argc, argv, "m:t:p:hs"))!=-1) {
    switch (rez) {
      case 'm':
        if (isdigit(optarg[0]))
          mode=atoi(optarg);
        else
          mode=(optarg[0]=='l'&&optarg[1]=='l')?
            M_LONG:(optarg[0]=='s')?M_SHORT:
            (optarg[0]!='r')?M_LINE:rand()%3;
        break;
      case 't': prompts=atoll(optarg); break;
      case 'p': pathsc=1; initpaths(optarg); break;
      case 's': sinfo=1; break;
      case 'h': case '?': default:
        goto needhelp;
    }
  }
  if (!pathsc)
    initpaths(NULL);
  list=ts_new();
  initouts(list);
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  if (mode==M_LONG||mode==M_SHORT) {
    if (!sinfo)
      mvprintw(0, 0, "loaded %ld files from %ld paths (%s)\n",
        list->num, numpaths, util_bytesconv(list->totallen));
    mvprintw((sinfo)?0:1,0, "exec %s (%s)"
      " %ld\n", list->targets->path,
      util_bytesconv(list->targets->len),
      list->num);
  }
  cpos=(mode==M_LINE)?0:(sinfo)?1:2;
  mvprintw(cpos, 0, ": ");
  refresh();
  for (;;) {
    ch=getch();
    if (ch=='\n')
      break;
    else if (ch==KEY_BACKSPACE||ch==127) {
      if (id>0) {
        input[--id]='\0';
        move(cpos, (2+id));
        delch();
      }
    }
    else if (id<sizeof(input)-1) {
      input[id++]=ch;
      addch(ch);
    }
    search(list, input);
  }
  input[sizeof(input)-1]='\0';
  exec();
  /* NOTREACHED */
}


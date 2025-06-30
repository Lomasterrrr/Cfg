#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <limits.h>
#include <sys/stat.h>

const char *dep_f[]={
	"scripts/bar.sh",
	"scripts/cpu.sh",
	"scripts/lay.sh",
	"scripts/memory.sh",
	"scripts/mon.sh",
	"scripts/network.sh",
	"scripts/sc.sh",
	"configs/tcsh",
	"configs/vim",
	"configs/spectrwm"
};

const char *dep_d[]={
	"apps/",
	"configs/",
	"scripts/",
	"apps/tcsh",
	"apps/sout",
	"apps/st"
};

inline void static cmdexec(const char *cmd) {
	printf("CMD\t%s\n",cmd);
	system(cmd);
}

inline int static chkfile(const char *filename) {
	struct stat st;
	return stat(filename,&st)==0
		&&S_ISREG(st.st_mode);
}

inline int static chkdir(const char *dirname) {
	struct stat st;
	return stat(dirname,&st)==0
		&&S_ISDIR(st.st_mode);
}

int main(int argc, char **argv)
{
	int n;
	if (geteuid()) {
		printf("ERR\tonly \"sudo -E\" run!!\n");
		printf("\nUSAGE:\nsudo -E %s\n", argv[0]);
		return 1;
	}
	for (n=0;n<sizeof(dep_f)/sizeof(const char *);n++) {
		if (!chkfile(dep_f[n])) {
			printf("ERR\tnot found %s file !\n", dep_f[n]);
			abort();
		}
		printf("AEE\tfound %s dir !\n", dep_f[n]);
	}
	for (n=0;n<sizeof(dep_d)/sizeof(const char *);n++) {
		if (!chkdir(dep_d[n])) {
			printf("ERR\tnot found %s dir !\n", dep_d[n]);
			abort();
		}
		printf("AEE\tfound %s dir !\n", dep_d[n]);
	}
	cmdexec("cp -f ./configs/spectrwm ~/.spectrwm.conf");
	cmdexec("cp -f ./configs/vim ~/.vimrc");
	cmdexec("cp -f ./configs/tcsh ~/.tcshrc");
	cmdexec("cp -f -r ./scripts ~/");
	cmdexec("rm -rf ~/tcsh");
	cmdexec("rm -rf ~/sout");
	cmdexec("rm -rf ~/st");
	cmdexec("cp -f -r ./apps/st ~/");
	cmdexec("cp -f -r ./apps/sout ~/");
	cmdexec("cp -f -r ./apps/tcsh ~/");
	cmdexec("cd ~/tcsh;make clean >/dev/null 2>&1;./configure >/dev/null 2>&1;make install -j >/dev/null 2>&1");
	cmdexec("cd ~/sout;make clean >/dev/null 2>&1;make -j >/dev/null 2>&1");
	cmdexec("cd ~/st;make clean >/dev/null 2>&1;make -j >/dev/null 2>&1");
	cmdexec("chsh -s /bin/tcsh");
	return 0;
}

/*****************************************************
 * ** Name         : getopt.c
 * ** Author       : gzshun
 * ** Version      : 1.0
 * ** Date         : 2012-01
 * ** Description  : getopt test program
 * **
 * ** This file may be redistributed under the terms
 * ** of the GNU Public License.
 * ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char *optarg;
extern int optind;
extern int opterr;
extern int optopt;
extern int getopt(int argc, char * const argv[], const char *optstring);

#define OPTION_A        (1<<0)
#define OPTION_B        (1<<1)
#define OPTION_C        (1<<2)
#define OPTION_D        (1<<3)
#define OPTION_E        (1<<4)
#define OPTION_F        (1<<5)
#define OPTION_G        (1<<6)
#define OPTION_H        (1<<7)

const char *programe_name = "getopt";

static void usage(void);
static int PRS(int argc, char **argv, int *opts);

static void usage(void)
{
	fprintf(stderr,
			"Usage:  %s [OPTION]\n"
            "\t[-abcdeh]\n"
            "\t[-f digit] [-g string]\n",
            programe_name);
    exit(1);
}

static int PRS(int argc, char **argv, int *opts)
{
    int retval, prog_num;
    char ch;

    *opts &= 0x00000000;

    /*******************************************************
     *optstring: "abcdef:g:h"
     *这个字符串是给getopt指定需要的选项.
     *abcdeh : 这几个选项后面没有跟选项参数
     *f:g:   : 在一个选项的后面多一个:号,说明这个选项后面是有参数的.
     *这个选项参数可以通过optarg全局变量获取到.
     ********************************************************/
    while ((ch = getopt(argc, argv, "abcdef:g:h")) != -1) {
        switch (ch) {
        case 'a':
            *opts |= OPTION_A;
            break;
        case 'b':
            *opts |= OPTION_B;
            break;
        case 'c':
            *opts |= OPTION_C;
            break;
        case 'd':
            *opts |= OPTION_D;
            break;
        case 'e':
            *opts |= OPTION_E;
            break;
        case 'f':
            *opts |= OPTION_F;
            printf("-f optarg=%s\n", optarg);
            break;
        case 'g':
            *opts |= OPTION_G;
            printf("-g optarg=%s\n", optarg);
            break;
        case 'h':
            *opts |= OPTION_H;
            usage();
            break;
        default:
            fprintf(stderr,
                    "our: %s: invalid option -- '%c'\n",
                    programe_name, optopt);
            exit(1);
            break;
        }
    }

    return 0;
}

int main(int argc ,char **argv)
{
    int i, retval;
    int opts;

    /*调用getopt之前打印argv数组*/
    printf("Before calling getopt\n");
    for (i = 0; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n\n");

    /**********************************************************
     *该函数是编写一个Linux命令最基本也最重要的一个操作,函数里面
     *调用getopt()函数,函数作用是用来解析命令的操作选项:
     *比如:cp -a -r src dst
     *getopt()用来分析参数选项,具体可以参考:
     *(UNIX环境高级编程 第21章 与网络打印机通信 p619)
     ************************************************************/
    retval = PRS(argc, argv, &opts);
    if (retval < 0) {
        exit(1);
    }
    printf("\n");

    /*调用getopt之后打印argv数组*/
    printf("After calling getopt\n");
    for (i = 0; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n\n");

    /*这里来打印一下选项的设置情况*/
    printf("-a \t set %s\n", opts&OPTION_A ? "yes" : "no");
    printf("-b \t set %s\n", opts&OPTION_B ? "yes" : "no");
    printf("-c \t set %s\n", opts&OPTION_C ? "yes" : "no");
    printf("-d \t set %s\n", opts&OPTION_D ? "yes" : "no");
    printf("-e \t set %s\n", opts&OPTION_E ? "yes" : "no");
    printf("-f \t set %s\n", opts&OPTION_F ? "yes" : "no");
    printf("-g \t set %s\n", opts&OPTION_G ? "yes" : "no");
    printf("-h \t set %s\n", opts&OPTION_H ? "yes" : "no");
    printf("\n");

    /**********************************************************
     *当执行完getopt后,argv二位数组里面的字符串已经被排序,选项部分
     *会被排在前面,非选项部分的会被排在最后面,但原来的顺序还是没有
     *发生变化;
     *为什么要加这个循环,因为在很多情况都要另外加一些参数,比如:
     *cp -a -r src1 src2 src3 src4 dst
     *这条复制命令, -a -r是选项, src[1-4] dst这几个就是其余的参数,
     *若需要这些,使用以下循环即可获得.
     ************************************************************/
    for (i = optind; i < argc; i++) {
        printf("optind=%d\t: argv[%d]=%s\n", i, i, argv[i]);
    }

    return 0;
}

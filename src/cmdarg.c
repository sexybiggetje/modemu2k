/*
 * cmdarg.c
 *
 * Copyright 2018 Andy Alt <andy400-dev@yahoo.com>
 *
 * modemu2k is a fork of modemu
 * Originally developed by Toru Egashira
 * Copyright (c) 1995, 1996
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <stdio.h>              /*stderr */
#include <stdlib.h>
#include <getopt.h>
#include "cmdarg.h"             /*cmdarg */
#include "defs.h"               /*VERSION_... */

/* LIT(A) -> "10" */
#define LIT_(s) #s
#define LIT(s) LIT_(s)

static void
showUsage (char* const argv[])
{
  /* TRANSLATORS: do not translate the command line options, only the descriptions
   */
  printf (_("\
Usage: %s [OPTION]...\n\
\n\
  -c, --commprog=\"<comm_prog> <args>\"     invoke a comm program using [arguments]\n\
  -d, --device=<pty_master>               talk through [pty_master]\n\
  -e, --atstring=\"<ATxxx>\"                execute [ATxxx] commands at startup\n\
  -s, --show                              show which device will be used\n\
\n\
  -h, --help                              display help\n\
  -v, --version                           display version\n\
  -w, --warranty                          display warranty\n\
\n\
The arguments for (-c, --commprog) and (-e, --atcommands) must be enclosed in\n\
quotes. (eg. -c \"minicom -l -w -c\")\n\
\n\
The arguments for the comm program must be native to the comm program, not\n\
arguments used by modemu2k.\n\
\n\
Note: The  -c, -d, and -s options are exclusive of each other. If two or\n\
more of the options are specified, only the last one is effective.\n\
\n\
The modemu2k project and support site is at\n\
<https://github.com/theimpossibleastronaut/modemu2k>\n\
\n\
Report bugs to <andy400-dev@yahoo.com> or\n\
<https://github.com/theimpossibleastronaut/modemu2k/issues>\n"),
  argv[0]);
}

static void
warranty (void)
{
printf (_("\
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n\
APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n\
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\n\
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\n\
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\n\
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\n\
IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\n\
ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n"));
}

static void version (char * const argv[])
{
  printf (_("\
modemu2k %s\n\
Maintainer: Andy Alt (andy400-dev@yahoo.com)\n\
This program comes with ABSOLUTELY NO WARRANTY; for details type '%s -w.'\n\
This is free software, and you are welcome to redistribute it\n\
under certain conditions; see <http://www.gnu.org/licenses/gpl.html>\n\
for details.\n"), argv[0], VERSION);
}

void
cmdargParse (const int argc, char* const argv[])
{
  const char *const short_options = "c:d:e:hsvw";

    const struct option long_options[] = {
    {"commprog", 1, NULL, 'c'},
    {"device", 1, NULL, 'd'},
    {"atstring", 1, NULL, 'e'},
    {"show", 0, NULL, 's'},
    {"help", 0, NULL, 'h'},
    {"version", 0, NULL, 'v'},
    {"warranty", 0, NULL, 'w'},
    {NULL, 0, NULL, 0}
  };

  int next_option = 0;
  cmdarg.ttymode = CA_STDINOUT;

  do
  {
    next_option = getopt_long (argc, argv, short_options, long_options, NULL);

    switch ((char)next_option)
    {
      case 'c':                /* -c <commx args> */
        cmdarg.ttymode = CA_COMMX;
        cmdarg.commx = optarg;
        break;
      case 'd':                /* -d <pty_device> */
        cmdarg.ttymode = CA_DEVGIVEN;
        cmdarg.dev = optarg;
        break;
      case 'e':                /* -a <atcommands> */
        cmdarg.atcmd = optarg;
        break;
      case 'h':                /* -h */
        showUsage (argv);
        exit (0);
      case 's':                /* -s */
        cmdarg.ttymode = CA_SHOWDEV;
        break;
      case 'v':
        version (argv);
        exit (0);
      case 'w':
        warranty ();
        exit (0);
      default:
        break;
    }
  } while (next_option != -1);

  return;
}

/*TITLE clock.c - Clock/calendar on terminal - 5/4/88 */

/*
** This program will place a full screen (readable across the room)
** date and time display on your terminal.  The display will update
** automagically.  To run it, make sure your TERM environmental
** variable is set properly and type "clock".  To end the program,
** type your "interrupt" character (usually cntl-c or delete).
** The program also traps the "terminate" signal, so it can be
** gracefully stopped by shutdown(1M) or a kill command from another
** terminal.
**
**  It has been tested on several System V machines, but no others.
**  To compile:  gcc -O -s clock.c -o clock -lcurses
*/

/*  This program, and the procedures in it are Copyright 1988 by:
**	DCF, Inc.
**	14623 North 49th Place
**	Scottsdale, AZ 85254
**  You may use it as you wish, including re-distribution, as long
**  as this notice remains intact and with the source code.
**  This program was suggested by a similar one written by
**  anasazi!duane.
*/

/*SUBTTL Includes, defines, and declarations */

static char	SCCS[] = "@(#)clock.c	1.4 4/30/88 09:04:54";

#include <stdio.h>
#include <curses.h> 
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

#define	MAXLINES	8	/* number of lines output by banner */
/* Le BON programme banner ... */
#define BANNER		"./sysvbanner "	/* banner program to use */
/*#define BANNER		"/usr/bin/sysvbanner "*/

#define	DAY_LINE	0	/* screen location for display elements */
#define	DATE_LINE	8
#define	TIME_LINE	16
#define ALARM_LINE      24


/* global data */
char		time_buf[24];	/* local time as a string */
struct tm	*time_tm;	/* local time as a structure */

/* forward references */
void		put_scr(), do_time(), do_date(), blammo(), end_win(), exit(), turnOnAlarme();
int		cat_int();
unsigned	sleep();
extern FILE	*popen();
extern long	time();


/*SUBTTL Main procedure */
main()
{
    long	ticks;		/* seconds since epoch */
    int		old_day = -1;	/* previous julian day */

    if ( !initscr() )
        blammo("curses initialization failed", 0);

    signal(SIGINT, (void *)cat_int);	/* provide an exit path */
    signal(SIGTERM, (void *)cat_int);    

    /*if (seconde == 1)
      {
	signal(SIGALRM, turnOnAlarme);
	//seconde=atoi(argv[1]);
      }	
    else
      {

      }*/
    clear();			/* setup */
    noecho();

    while (TRUE) {
	/* get the local time for us to use */
	ticks = time( (long *)NULL );
	strncpy(time_buf, ctime(&ticks), 24);
	time_tm = localtime(&ticks);

	/* put date & time on the screen */
	if (old_day != time_tm->tm_yday) {
	    old_day = time_tm->tm_yday;
	    do_date();		/* build a new date */
	}
        do_time();		/* build the time */
	move(0, 0);		/* update the screen */
	refresh();

	/* wait for clock to roll over the next minute */
	sleep( (unsigned)(60 - time_tm->tm_sec) );
    }
}


/*SUBTTL do_date - display the date banner */
/*
**  Construct and display the date banner
*/
void do_date()
{
    static char *days[] = {	/* days of the week */
	"Dimanche","Lundi", "Mardi","Mercredi","Jeudi","Vendredi","Samedi"};

    char	buf[7];

    erase();	/* in case new date is shorter than current */
    put_scr(DAY_LINE, days[time_tm->tm_wday]);
    strncpy(buf, &time_buf[4], 6);
    buf[6] = '\0';
    put_scr(DATE_LINE, buf);
}


/*SUBTTL do_time - display the time banner */
/*
**  Construct and display the time banner
*/
void do_time()
{
    char	buf[6];

    strncpy(buf, &time_buf[11], 5);
    buf[5] = '\0';
    put_scr(TIME_LINE, buf);
}


/*SUBTTL put_scr - put a banner in the screen buffer */
/*
**  Construct and display a banner string
*/

void	put_scr(where, what)
int	where;
char	*what;
{
    char	ban_buf[MAXLINES][80];
    char	buf[80];
    FILE	*proc_stream;
    int		length = 0;
    register int line;

    /* start a "banner" stream in our direction */
    strncpy(buf, BANNER, 80);
    strcat(buf, "'");
    strcat(buf, what);
    strcat(buf, "'");
    if ( (proc_stream = popen(buf, "r") ) == (FILE *)NULL )
        blammo("Popen", errno);

    /* capture the stream in our buffer */
    for (line = 0; line < MAXLINES; line++) {
	fgets(ban_buf[line], 80, proc_stream);
	if ( feof(proc_stream) )
	    blammo("Premature eof", 0);
    }
    (void)pclose(proc_stream);

    /* figure out how long this banner is (for centering) */
    for (line = 0; line < MAXLINES; line++)
	length = (length < strlen(ban_buf[line]) ?
	  strlen(ban_buf[line]) : length);

    /* put the banner in the screen buffer */
    for (line = 0; line < MAXLINES; line++)
	mvaddstr(where + line, (COLS - length) / 2, ban_buf[line]);
}


/*SUBTTL blammo - display message and terminate program */
/*
**  Reset the screen, issue an error message, and exit.
*/

void blammo(msg, code)
char	*msg;
int	code;
{
    end_win();
    if (code)
        fprintf(stderr, "%s error %d\n", msg, code);
    else
        fprintf(stderr, "%s\n", msg);
    exit(-1);
}


/*SUBTTL end_win - clean up the window stuff */
/*
**  Terminate the window stuff - clear the window and move the cursor.
*/

void end_win()
{
    clear();
    move(LINES - 1, 0);
    refresh();
    endwin();
}


/*SUBTTL cat_int - signal catcher */
/*
**  Catch an interrupt signal and terminate the program.
*/

int	cat_int()
{
    end_win();
    exit(0);
}

void turnOnAlarme()
{
  put_scr(ALARM_LINE,"Reveil");
}

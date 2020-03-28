#include <glib/gstdio.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "sat-connection-scheduler.h"

#include "compat.h"
#include "sgpsdp/sgp4sdp4.h"

void schedule(gchar * moduleName, gint catnum, gdouble startTime, gdouble endTime){
	g_print("SCHEDULE START\n");
	// system("which gpredict");
	// system("(crontab -l ; echo \"* * * * * echo \"HELLO WORLD\" > ~/HELLO.txt\") | crontab -");

	struct tm       tim;
    time_t          t;

	t = (startTime - 2440587.5) * 86400.;
    tim = *localtime(&t);

    g_print("%d %d %d %d:%d\n", tim.tm_year, tim.tm_mon, tim.tm_mday, tim.tm_hour, tim.tm_min);

    gchar * command;
    command = g_strdup_printf("(crontab -l ; echo \"%d %d %d %d * echo \"HELLO WORLD\" > ~/HELLO.txt\") | crontab -", tim.tm_min, tim.tm_hour, tim.tm_mday, tim.tm_mon+1);
    system(command);
// double          jt;
//     struct tm       chkdate;

//     jt = Julian_Date(cdate);
//     Date_Time(jt, &chkdate);

//     if ((cdate->tm_year == chkdate.tm_year) &&
//         (cdate->tm_mon == chkdate.tm_mon) &&
//         (cdate->tm_mday == chkdate.tm_mday) &&
//         (cdate->tm_hour == chkdate.tm_hour) &&
//         (cdate->tm_min == chkdate.tm_min) && (cdate->tm_sec == chkdate.tm_sec))

	FILE *pFile;
	
	gchar          *confdir;
    gchar          *fileName;

    confdir = get_scheduler_dir();
    fileName = g_strconcat(confdir, G_DIR_SEPARATOR_S, "schedule.list", NULL);

	pFile=fopen(fileName, "a");
	if(pFile==NULL) {
	    perror("Error opening file.");
	    return;
	}
	else {
        fprintf(pFile, "HELLO WORLD\n");
	}
	fclose(pFile);

	g_print("SCHEDULED\n");
}
#include <glib/gstdio.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include "sat-connection-scheduler.h"

#include "compat.h"

void schedule(){
	g_print("SCHEDULE START\n");

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
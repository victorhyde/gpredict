#include <time.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "sat-connection-scheduler.h"

#include "compat.h"
#include "sgpsdp/sgp4sdp4.h"
#include "sat-cfg.h"
#include "mod-mgr.h"
#include "gtk-sat-module.h"

struct Connection {
	gchar * moduleName;
	gint catnum;
	gdouble disconnectTime;
	guint timerid;
};

void schedule(gchar * moduleName, gint catnum, gdouble startTime, gdouble endTime){
	g_print("SCHEDULE START\n");
	// system("which gpredict");
	// system("(crontab -l ; echo \"* * * * * echo \"HELLO WORLD\" > ~/HELLO.txt\") | crontab -");

	FILE *fp;
  char path[1035];

  /* Open the command for reading. */
  fp = popen("/bin/which gpredict", "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }

  /* Read the output a line at a time - output it. */
  while (fgets(path, sizeof(path), fp) != NULL) {
    printf("%s", path);
  }

  /* close */
  pclose(fp);


	g_print("START TIME %f\n", startTime);
	gchar          *fmtstr;
    gchar           buff[TIME_FORMAT_MAX_LENGTH + 1];

    fmtstr = sat_cfg_get_str(SAT_CFG_STR_TIME_FORMAT);
    daynum_to_str(buff, TIME_FORMAT_MAX_LENGTH, fmtstr, startTime);
    g_print("START TIME %s\n", buff);

	struct tm       tim;
    time_t          t;

	t = (startTime - 2440587.5) * 86400.;
	// Add 59 seconds so the time gets rounded up to the nearest whole minute instead of down
	t += 59.; 
    tim = *localtime(&t);

    g_print("%d %d %d %d:%d\n", tim.tm_year, tim.tm_mon, tim.tm_mday, tim.tm_hour, tim.tm_min);

    // Remove new line character from path
    path[strlen(path)-1] = '\0';
    printf("GPREDICT PATH %s", path);

    gchar * gpredict_command;
    gpredict_command = g_strdup_printf("export DISPLAY=:0 && %s --track-sat=%d --module=%s --disconnect-time=%f", path, catnum, moduleName, endTime);
    gchar * cron_command;
    cron_command = g_strdup_printf("(crontab -l ; echo \"%d %d %d %d * %s\") | crontab -", tim.tm_min, tim.tm_hour, tim.tm_mday, tim.tm_mon+1, gpredict_command);
    system(cron_command);

	// FILE *pFile;
	
	// gchar          *confdir;
 //    gchar          *fileName;

 //    confdir = get_scheduler_dir();
 //    fileName = g_strconcat(confdir, G_DIR_SEPARATOR_S, "schedule.list", NULL);

	// pFile=fopen(fileName, "a");
	// if(pFile==NULL) {
	//     perror("Error opening file.");
	//     return;
	// }
	// else {
 //        fprintf(pFile, "HELLO WORLD\n");
	// }
	// fclose(pFile);

	// g_print("SCHEDULED\n");
}

static gboolean scheduler_timeout_cb(gpointer moduleName)
{
	// g_print("TIMEOUT\n");
	// // struct Connection *connection = (struct Connection *)(module);
	// // gchar * moduleName = ()
	// g_print("TIMEOUT MODULE NAME %s\n", moduleName);
	// g_print("TIMEOUT TIME %d\n", time(0));

	GtkWidget * module;

    module = mod_mgr_get_module(moduleName);
    if (module){
        // g_print("NAME FROM MODULE %s\n", GTK_SAT_MODULE(module)->name);
        gtk_sat_module_disconnect_from_sat(GTK_SAT_MODULE(module));
    }


	// system("echo \"SCHEDULER FINISHED\" > ~/HELLO.txt");
	return TRUE;
}

void scheduler_auto_disconnect(gchar * moduleName, gint catnum, gdouble disconnectTime){
    time_t t;
	t = (disconnectTime - 2440587.5) * 86400.;

	/* start timeout */
    g_timeout_add((t - time(0)) * 1000, scheduler_timeout_cb, moduleName);
}
#ifndef MOD_MGR_H
#define MOD_MGR_H 1

GtkWidget      *mod_mgr_create(void);
gint            mod_mgr_add_module(GtkWidget * module, gboolean dock);
GtkWidget      *mod_mgr_get_module(gchar * name);
GtkWidget      *mod_mgr_get_current_module();
void            mod_mgr_switch_to_module(GtkWidget * module);
gint            mod_mgr_remove_module(GtkWidget * module);
void            mod_mgr_save_state(void);
gboolean        mod_mgr_mod_is_visible(GtkWidget * module);
gint            mod_mgr_dock_module(GtkWidget * module);
gint            mod_mgr_undock_module(GtkWidget * module);
void            mod_mgr_reload_sats(void);

#endif

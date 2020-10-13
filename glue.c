#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <gtk/gtk.h>

#include <X11/Xlib.h>

void UseDefaultX11VisualForGtk (GtkWidget* widget) 
{
#if GTK_CHECK_VERSION(3, 15, 1)
  // GTK+ > 3.15.1 uses an X11 visual optimized for GTK+'s OpenGL stuff
  // since revid dae447728d: https://github.com/GNOME/gtk/commit/dae447728d
  // However, it breaks CEF: https://github.com/cztomczak/cefcapi/issues/9
  // Let's use the default X11 visual instead of the GTK's blessed one.
  // Copied from: https://github.com/cztomczak/cefcapi.
  GdkScreen* screen = gdk_screen_get_default();
  GList* visuals = gdk_screen_list_visuals(screen);

  GdkX11Screen* x11_screen = GDK_X11_SCREEN(screen);
  if (x11_screen == NULL)
    return;

  Visual* default_xvisual = DefaultVisual(GDK_SCREEN_XDISPLAY(x11_screen),
                                          GDK_SCREEN_XNUMBER(x11_screen));
  GList* cursor = visuals;
  while (cursor != NULL) {
    GdkVisual* visual = GDK_X11_VISUAL(cursor->data);
    if (default_xvisual->visualid ==
        gdk_x11_visual_get_xvisual(visual)->visualid) {
      gtk_widget_set_visual(widget, visual);
      break;
    }
    cursor = cursor->next;
  }
  g_list_free(visuals);
#endif
}


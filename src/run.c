#include "gtk_include_all.h"

int main(int argc, char* argv[])
{
    GtkApp app = gtk_app_new();
    run_gtk(argc, argv, app);
    gtk_app_free(app);
    return 0;
}

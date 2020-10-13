all: glue.c
	gcc -shared -o glue.so -fPIC `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` glue.c
	cp glue.so CefGlue.Demo.GtkSharp/bin/Debug/ 

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

bin_PROGRAMS = demoapp

demoapp_SOURCES = src/main.cpp src/renderer.h src/renderer.cpp #src/config.cpp src/config.h 
demoapp_CPPFLAGS = -I$(top_srcdir)/include -I@LCONFIGDIR@ -I@NDNRTCDIR@ -I@NDNCPPDIR@
demoapp_LDFLAGS = -L@LCONFIGLIB@ -L@NDNCPPLIB@ -L@NDNRTCLIB@ -L/usr/local/lib -lconfig++ -lndn-cpp -lndnrtc -lX11 -lXdamage -lXrender -lXext -lnss3 -lssl3 -lXfixes -lXcomposite -lglfw -lGLEW /home/jcw/OpenGL-tutorial_v0014_21/build/external/libGLEW_190.a -lGLU -lGL -lSM -lICE -lX11 -lXext 
noinst_SCRIPTS = params.cfg

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

bin_PROGRAMS = demoapp

demoapp_SOURCES = src/main.cpp #src/config.cpp src/config.h 
demoapp_CPPFLAGS = -I$(top_srcdir)/include -I@LCONFIGDIR@ -I@NDNRTCDIR@ -I@NDNCPPDIR@
demoapp_LDFLAGS = -L@LCONFIGLIB@ -L@NDNCPPLIB@ -L@NDNRTCLIB@ -lconfig++ -lndn-cpp -lndnrtc -lX11 -lXdamage -lXrender -lXext -lnss3 -lssl3 -lXfixes -lXcomposite

noinst_SCRIPTS = params.cfg

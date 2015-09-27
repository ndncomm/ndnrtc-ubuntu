#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([NDN-RTC Ubuntu demoapp],[0.0.1],[peter@remap.ucla.edu],[ndnrtc ubuntu demoapp],[https://github.com/remap/ndnrtc])
AM_INIT_AUTOMAKE([1.10 -Wall no-define foreign subdir-objects])
AC_CONFIG_MACRO_DIR([m4])

AC_PREFIX_DEFAULT([/usr/local])
#AC_CONFIG_SRCDIR([src/config.h)
AC_CONFIG_FILES([Makefile])
AM_MAINTAINER_MODE

AC_ARG_VAR([NDNRTCDIR], [Path to the directory which contains NDN-RTC library headers folder (default is /usr/local/include)])
AC_ARG_VAR([NDNRTCLIB], [Path to the directory which contains NDN-RTC library binaries folder (default is /usr/local/lib)])
#AC_ARG_VAR([BOOSTDIR], [Path to the directory which contains Boost library headers folder (default is /usr/local/include)])
#AC_ARG_VAR([BOOSTLIB], [Path to the directory which contains Boost library binaries folder (default is /usr/local/lib)])
AC_ARG_VAR([NDNCPPDIR], [Path to the directory which contains NDN-CPP library headers folder (default is /usr/local/include)])
AC_ARG_VAR([NDNCPPLIB], [Path to the directory which contains NDN-CPP library binaries (default is /usr/local/lib)])
#AC_ARG_VAR([OPENFECDIR], [Path to the directory which contains OpenFEC library])
#AC_ARG_VAR([OPENFECSRC], [Path to the directory which contains OpenFEC library header files (default is $OPENFECDIR/src)])
#AC_ARG_VAR([OPENFECLIB], [Path to the directory which contains OpenFEC library binaries (default is $OPENFECDIR/bin/Release)])
#AC_ARG_VAR([PTHREADDIR], [Path to the directory which contains pthread library headers (default is /usr/local/include)])
#AC_ARG_VAR([PTHREADLIB], [Path to the directory which contains pthread library binaries (default is /usr/local/lib)])
#AC_ARG_VAR([WEBRTCDIR], [Path to the directory which contains WebRTC trunk])
#AC_ARG_VAR([WEBRTCSRC], [Path to the directory which contains WebRTC header files (default is $WEBRTCDIR/wbertc)])
#AC_ARG_VAR([WEBRTCLIB], [Path to the directory which contains WebRTC libraries (default is $WEBRTCDIR/out/Release)])

AC_ARG_VAR([LCONFIGDIR], [Path to the directory which contains libconfig library headers (default is /usr/local/include)])
AC_ARG_VAR([LCONFIGLIB], [Path to the directory which contains libconfig library binaries (default is /usr/local/lib)])
#AC_ARG_VAR([NCURSESDIR], [Path to the directory which contains ncurses library headers (default is /usr/local/include)])
#AC_ARG_VAR([NCURSESLIB], [Path to the directory which contains ncurses library binaries (default is /usr/local/lib)])

#if test ${BOOSTDIR}; then
#	BOOSTDIR=$(cd $BOOSTDIR; pwd)
#else
#	BOOSTDIR="/usr/local/include"
#fi
#
#if test ${BOOSTLIB}; then
#	BOOSTLIB=$(cd $BOOSTLIB; pwd)
#else
#	BOOSTLIB="/usr/local/lib"
#fi

if test ${NDNCPPDIR}; then
	NDNCPPDIR=$(cd $NDNCPPDIR; pwd)
else
	NDNCPPDIR="/usr/local/include"
fi

if test ${NDNCPPLIB}; then
	NDNCPPLIB=$(cd $NDNCPPLIB; pwd)
else
	NDNCPPLIB="/usr/local/lib"
fi

#
#if test ${OPENFECDIR}; then
#	OPENFECDIR=$(cd $OPENFECDIR; pwd)
#fi
#
#if test "x${OPENFECSRC}" = "x"; then
#	OPENFECSRC="$OPENFECDIR/src"
#fi
#
#if test "x${OPENFECLIB}" = "x"; then
#	OPENFECLIB="$OPENFECDIR/bin/Release"
#fi
#
#if test ${PTHREADDIR}; then
#	PTHREADDIR=$(cd $PTHREADDIR; pwd)
#else
#	PTHREADDIR="/usr/local/include"
#fi
#
#if test ${PTHREADLIB}; then
#	PTHREADLIB=$(cd $PTHREADLIB; pwd)
#else
#	PTHREADLIB="/usr/local/lib"
#fi
#
#if test ${WEBRTCDIR}; then
#	WEBRTCDIR=$(cd $WEBRTCDIR; pwd)
#fi
#
#if test "x${WEBRTCSRC}" = "x"; then
#	WEBRTCSRC="$WEBRTCDIR/webrtc"
#fi
#
#if test "x${WEBRTCLIB}" = "x"; then
#	WEBRTCLIB="$WEBRTCDIR/out/Release"
#fi

if test ${NDNRTCDIR}; then
	NDNRTCDIR=$(cd $NDNRTCDIR; pwd)
else
	NDNRTCDIR="/usr/local/include"
fi

if test ${NDNRTCLIB}; then
	NDNRTCLIB=$(cd $NDNRTCLIB; pwd)
else
	NDNRTCLIB="/usr/local/lib"
fi

if test ${LCONFIGDIR}; then
	LCONFIGDIR=$(cd $LCONFIGDIR; pwd)
else
	LCONFIGDIR="/usr/local/include"
fi

if test ${LCONFIGLIB}; then
	LCONFIGLIB=$(cd $LCONFIGLIB; pwd)
else
	LCONFIGLIB="/usr/local/lib"
fi

#if test ${NCURSESDIR}; then
#	NCURSESDIR=$(cd $NCURSESDIR; pwd)
#else
#	NCURSESDIR="/usr/local/include"
#fi
#
#if test ${NCURSESLIB}; then
#	NCURSESLIB=$(cd $NCURSESLIB; pwd)
#else
#	NCURSESLIB="/usr/local/lib"
#fi

AC_ARG_WITH([libc++], [AS_HELP_STRING([--with-libc++],[use libc++ if available [default=use libstdc++]])], 
	[
	STDLIBFLAGS_CPP="-stdlib=libc++" 
	STDLIBFLAGS_LD="-stdlib=libc++"
	],
	[
	STDLIBFLAGS_CPP="-stdlib=libstdc++" 
	STDLIBFLAGS_LD="-stdlib=libstdc++"	
	])

# Checks for programs.
AC_CANONICAL_HOST
AC_PROG_CC
AC_PROG_CXX
AC_PROG_OBJC
AC_PROG_OBJCXX
AM_PROG_CC_C_O
LT_INIT
AC_LANG([C++])
LT_LANG([C++])
LT_PREREQ([2.2])
LT_INIT()

# checking platform
case $host_os in
  darwin* )
		# Do something specific for MacOS  
		# Special case.
		case "$host" in
		  *-darwin* | *-macos10*)
			if test -d /sw ; then
				CFLAGS="$CFLAGS -I/sw/include"
				CXXFLAGS="$CXXFLAGS -I/sw/include"
				CPPFLAGS="$CPPFLAGS -I/sw/include"
				LDFLAGS="$LDFLAGS -L/sw/lib"
			fi
			;;
		esac
		os_module=darwin
		
		;;
  linux*)
		# Do something specific for linux
		os_module=linux        
		;;
   *BSD*)
		# Do something specific for BSD
		os_module=bsd        
		;;
    *)
		#Default Case
		AC_MSG_ERROR([Your platform is not currently supported])
		;;
esac

# check for compiler flags
if [[[ $CPPFLAGS =~ .*stdlib.* ]]]; then
	AC_MSG_NOTICE([stdlib compiler flag provided. adding $STDLIBFLAGS_CPP skipped])	
else
	if [[[ $STDLIBFLAGS_CPP =~ .*libc\+\+.* ]]]; then
		AX_CHECK_COMPILE_FLAG([-stdlib=libc++], [CPPFLAGS="$CPPFLAGS $STDLIBFLAGS_CPP"])
	else
		AX_CHECK_COMPILE_FLAG([-stdlib=libstdc++], [CPPFLAGS="$CPPFLAGS $STDLIBFLAGS_CPP"])
	fi
fi

# check for linker flags
if [[[ $LDFLAGS =~ .*stdlib.* ]]]; then
	AC_MSG_NOTICE([stdlib linker flag provided. adding $STDLIBFLAGS_LD skipped])
else
	if [[[ $STDLIBFLAGS_LD =~ .*libc\+\+.* ]]]; then
		AX_CHECK_LINK_FLAG([-stdlib=libc++], [LDFLAGS="$LDFLAGS $STDLIBFLAGS_LD"])
	else
		AX_CHECK_LINK_FLAG([-stdlib=libstdc++], [LDFLAGS="$LDFLAGS $STDLIBFLAGS_LD"])
	fi
fi

# setting conditionals for automake
AM_CONDITIONAL([OS_DARWIN],  [test $os_module = darwin])
AM_CONDITIONAL([OS_LINUX],  [test $os_module = linux])
AM_CONDITIONAL([OS_BSD],  [test $os_module = bsd])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AX_CXX_COMPILE_STDCXX_11([], optional)

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([gettimeofday memset sqrt strstr])

# Check for Boost
#SAVED_CPPFLAGS=$CPPFLAGS
#CPPFLAGS="$CPPFLAGS -I$BOOSTDIR"
#SAVED_LDFLAGS=$LDFLAGS
#LDFLAGS="$LDFLAGS -L$BOOSTLIB"
#SAVED_LIBS=$LIBS
#LIBS="$LIBS -lboost_system -lboost_timer -lboost_chrono"
#
#AC_MSG_CHECKING([for boost::shared_ptr...])
#AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
#    [[#include <boost/shared_ptr.hpp>]]
#    [[boost::shared_ptr<int> have_shared_ptr;]])
#], [
#    AC_MSG_RESULT([yes])
#], [
#    AC_MSG_FAILURE([not found])
#])
#
#AC_MSG_CHECKING([for boost::enabled_shared_from_this...])
#AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
#    [[#include <boost/enable_shared_from_this.hpp>]]
#    [[class A:public boost::enable_shared_from_this<A>{};]])
#], [
#    AC_MSG_RESULT([yes])
#], [
#    AC_MSG_FAILURE([not found])
#])
#
#AC_MSG_CHECKING([for boost::chrono...])
#AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
#    [[#include <boost/chrono.hpp>]]
#    [[auto now = boost::chrono::system_clock::now().time_since_epoch();
#  	boost::chrono::nanoseconds nsec = boost::chrono::steady_clock::now().time_since_epoch();
#  	boost::chrono::microseconds usec = boost::chrono::duration_cast<boost::chrono::microseconds>(boost::chrono::steady_clock::now().#time_since_epoch());
#    boost::chrono::milliseconds msec = boost::chrono::duration_cast<boost::chrono::milliseconds>(boost::chrono::steady_clock::now().#time_since_epoch());
#    boost::chrono::seconds sec = boost::chrono::duration_cast<boost::chrono::seconds>(boost::chrono::steady_clock::now().time_since_epoch(#));
#    boost::chrono::duration<double> secd = now;]])
#], [
#    AC_MSG_RESULT([yes])
#], [
#    AC_MSG_FAILURE([not found])
#])
#
#AC_MSG_CHECKING([for boost::asio::steady_timer...])
#AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
#    [[#include <boost/asio.hpp>
#	  #include <boost/asio/steady_timer.hpp>]]
#    [[
#    boost::asio::io_service io_service_;
#    boost::asio::steady_timer timer_(io_service_);]])
#], [
#    AC_MSG_RESULT([yes])
#], [
#    AC_MSG_FAILURE([not found])
#])
#
#AC_MSG_CHECKING([for boost::thread...])
#AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
#    [[#include <boost/thread.hpp>]]
#    [[boost::thread thread;]])
#], [
#    AC_MSG_RESULT([yes])
#], [
#    AC_MSG_FAILURE([not found])
#])
#
#AC_MSG_CHECKING([check linking with libs $LIBS...])
#AC_LINK_IFELSE(
# 	[AC_LANG_PROGRAM([#include <boost/asio.hpp>
#	  #include <boost/asio/steady_timer.hpp>],
# 		[boost::asio::io_service io_service_;
#    boost::asio::steady_timer timer_(io_service_);])],
# 		[AC_MSG_RESULT([yes])],
# 		[AC_MSG_FAILURE([can't find required boost libraries (boost_system-mt, boost_timer-mt, boost_chrono-mt)])]
#)
#
#LIBS=$SAVED_LIBS
#LDFLAGS=$SAVED_LDFLAGS
#CPPFLAGS=$SAVED_CPPFLAGS

## Check for NDN-CPP
#SAVED_CPPFLAGS=$CPPFLAGS
#CPPFLAGS="$CPPFLAGS -I$NDNCPPDIR -I$BOOSTDIR"
#SAVED_LDFLAGS=$LDFLAGS
#LDFLAGS="$LDFLAGS -L$NDNCPPLIB"
#SAVED_LIBS=$LIBS
#LIBS="$LIBS -lndn-cpp"
#
#AC_CHECK_HEADERS([ndn-cpp/interest.hpp],,[AC_MSG_FAILURE([can't find interest.hpp])])
#AC_MSG_CHECKING([for NDN-CPP library...])
#
#AC_LINK_IFELSE(
# 	[AC_LANG_PROGRAM([#include <ndn-cpp/interest.hpp>],
# 		[ndn::Interest interest])],
# 		[AC_MSG_RESULT([yes])],
# 		[AC_MSG_FAILURE([can't find NDN-CPP lib])]
#)
#
#AC_MSG_CHECKING([if NDN-CPP library was compiled for using boost::shared_ptr])
#AC_RUN_IFELSE(
#	[AC_LANG_PROGRAM([
#		#include <ndn-cpp/interest.hpp>
#		#include <boost/shared_ptr.hpp>
#		],
#		[
#			ndn::ptr_lib::shared_ptr<int> ptrlibPtr(new int(5));
#			boost::shared_ptr<int> boostPtr(new int(6));
#			ptrlibPtr = boostPtr;
#		]
#	)],
#	[AC_MSG_RESULT([yes])],
#	[AC_MSG_RESULT([no])]
#	[AC_MSG_FAILURE([NDN-CPP installation at $NDNCPPBIN does not provide support for boost::shared_ptr])]	
#)
#
#LIBS=$SAVED_LIBS
#LDFLAGS=$SAVED_LDFLAGS
#CPPFLAGS=$SAVED_CPPFLAGS

AC_OUTPUT

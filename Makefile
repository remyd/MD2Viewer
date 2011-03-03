#############################################################################
# Makefile for building: assignment2.app/Contents/MacOS/assignment2
# Generated by qmake (2.01a) (Qt 4.7.1) on: Mon Feb 28 19:20:08 2011
# Project:  assignment2.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/local/Qt4.7/mkspecs/macx-g++ -o Makefile assignment2.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -gdwarf-2 -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -g -gdwarf-2 -Wall -W $(DEFINES)
INCPATH       = -I/usr/local/Qt4.7/mkspecs/macx-g++ -I. -I/Library/Frameworks/QtCore.framework/Versions/4/Headers -I/usr/include/QtCore -I/Library/Frameworks/QtGui.framework/Versions/4/Headers -I/usr/include/QtGui -I/Library/Frameworks/QtOpenGL.framework/Versions/4/Headers -I/usr/include/QtOpenGL -I/usr/include -I. -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I/System/Library/Frameworks/AGL.framework/Headers -I. -F/Library/Frameworks
LINK          = g++
LFLAGS        = -headerpad_max_install_names
LIBS          = $(SUBLIBS) -F/Library/Frameworks -L/Library/Frameworks -framework QtOpenGL -framework QtGui -framework QtCore -framework OpenGL -framework AGL 
AR            = ar cq
RANLIB        = ranlib -s
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = 
INSTALL_FILE  = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = $(COPY_FILE)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
export MACOSX_DEPLOYMENT_TARGET = 10.4

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		window.cpp \
		renderer.cpp \
		md2.cpp \
		vector3d.cpp moc_renderer.cpp
OBJECTS       = main.o \
		window.o \
		renderer.o \
		md2.o \
		vector3d.o \
		moc_renderer.o
DIST          = /usr/local/Qt4.7/mkspecs/common/unix.conf \
		/usr/local/Qt4.7/mkspecs/common/mac.conf \
		/usr/local/Qt4.7/mkspecs/common/mac-g++.conf \
		/usr/local/Qt4.7/mkspecs/qconfig.pri \
		/usr/local/Qt4.7/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/Qt4.7/mkspecs/features/qt_functions.prf \
		/usr/local/Qt4.7/mkspecs/features/qt_config.prf \
		/usr/local/Qt4.7/mkspecs/features/exclusive_builds.prf \
		/usr/local/Qt4.7/mkspecs/features/default_pre.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/default_pre.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/dwarf2.prf \
		/usr/local/Qt4.7/mkspecs/features/debug.prf \
		/usr/local/Qt4.7/mkspecs/features/default_post.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/default_post.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/objective_c.prf \
		/usr/local/Qt4.7/mkspecs/features/warn_on.prf \
		/usr/local/Qt4.7/mkspecs/features/qt.prf \
		/usr/local/Qt4.7/mkspecs/features/unix/opengl.prf \
		/usr/local/Qt4.7/mkspecs/features/unix/thread.prf \
		/usr/local/Qt4.7/mkspecs/features/moc.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/rez.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/sdk.prf \
		/usr/local/Qt4.7/mkspecs/features/resources.prf \
		/usr/local/Qt4.7/mkspecs/features/uic.prf \
		/usr/local/Qt4.7/mkspecs/features/yacc.prf \
		/usr/local/Qt4.7/mkspecs/features/lex.prf \
		/usr/local/Qt4.7/mkspecs/features/include_source_dir.prf \
		assignment2.pro
QMAKE_TARGET  = assignment2
DESTDIR       = 
TARGET        = assignment2.app/Contents/MacOS/assignment2

####### Custom Compiler Variables
QMAKE_COMP_QMAKE_OBJECTIVE_CFLAGS = -pipe \
		-g \
		-gdwarf-2 \
		-Wall \
		-W


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile assignment2.app/Contents/PkgInfo assignment2.app/Contents/Resources/empty.lproj assignment2.app/Contents/Info.plist $(TARGET)

$(TARGET):  $(OBJECTS)  
	@$(CHK_DIR_EXISTS) assignment2.app/Contents/MacOS/ || $(MKDIR) assignment2.app/Contents/MacOS/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: assignment2.pro  /usr/local/Qt4.7/mkspecs/macx-g++/qmake.conf /usr/local/Qt4.7/mkspecs/common/unix.conf \
		/usr/local/Qt4.7/mkspecs/common/mac.conf \
		/usr/local/Qt4.7/mkspecs/common/mac-g++.conf \
		/usr/local/Qt4.7/mkspecs/qconfig.pri \
		/usr/local/Qt4.7/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/Qt4.7/mkspecs/features/qt_functions.prf \
		/usr/local/Qt4.7/mkspecs/features/qt_config.prf \
		/usr/local/Qt4.7/mkspecs/features/exclusive_builds.prf \
		/usr/local/Qt4.7/mkspecs/features/default_pre.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/default_pre.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/dwarf2.prf \
		/usr/local/Qt4.7/mkspecs/features/debug.prf \
		/usr/local/Qt4.7/mkspecs/features/default_post.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/default_post.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/objective_c.prf \
		/usr/local/Qt4.7/mkspecs/features/warn_on.prf \
		/usr/local/Qt4.7/mkspecs/features/qt.prf \
		/usr/local/Qt4.7/mkspecs/features/unix/opengl.prf \
		/usr/local/Qt4.7/mkspecs/features/unix/thread.prf \
		/usr/local/Qt4.7/mkspecs/features/moc.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/rez.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/sdk.prf \
		/usr/local/Qt4.7/mkspecs/features/resources.prf \
		/usr/local/Qt4.7/mkspecs/features/uic.prf \
		/usr/local/Qt4.7/mkspecs/features/yacc.prf \
		/usr/local/Qt4.7/mkspecs/features/lex.prf \
		/usr/local/Qt4.7/mkspecs/features/include_source_dir.prf \
		/Library/Frameworks/QtOpenGL.framework/QtOpenGL.prl \
		/Library/Frameworks/QtGui.framework/QtGui.prl \
		/Library/Frameworks/QtCore.framework/QtCore.prl
	$(QMAKE) -spec /usr/local/Qt4.7/mkspecs/macx-g++ -o Makefile assignment2.pro
/usr/local/Qt4.7/mkspecs/common/unix.conf:
/usr/local/Qt4.7/mkspecs/common/mac.conf:
/usr/local/Qt4.7/mkspecs/common/mac-g++.conf:
/usr/local/Qt4.7/mkspecs/qconfig.pri:
/usr/local/Qt4.7/mkspecs/modules/qt_webkit_version.pri:
/usr/local/Qt4.7/mkspecs/features/qt_functions.prf:
/usr/local/Qt4.7/mkspecs/features/qt_config.prf:
/usr/local/Qt4.7/mkspecs/features/exclusive_builds.prf:
/usr/local/Qt4.7/mkspecs/features/default_pre.prf:
/usr/local/Qt4.7/mkspecs/features/mac/default_pre.prf:
/usr/local/Qt4.7/mkspecs/features/mac/dwarf2.prf:
/usr/local/Qt4.7/mkspecs/features/debug.prf:
/usr/local/Qt4.7/mkspecs/features/default_post.prf:
/usr/local/Qt4.7/mkspecs/features/mac/default_post.prf:
/usr/local/Qt4.7/mkspecs/features/mac/objective_c.prf:
/usr/local/Qt4.7/mkspecs/features/warn_on.prf:
/usr/local/Qt4.7/mkspecs/features/qt.prf:
/usr/local/Qt4.7/mkspecs/features/unix/opengl.prf:
/usr/local/Qt4.7/mkspecs/features/unix/thread.prf:
/usr/local/Qt4.7/mkspecs/features/moc.prf:
/usr/local/Qt4.7/mkspecs/features/mac/rez.prf:
/usr/local/Qt4.7/mkspecs/features/mac/sdk.prf:
/usr/local/Qt4.7/mkspecs/features/resources.prf:
/usr/local/Qt4.7/mkspecs/features/uic.prf:
/usr/local/Qt4.7/mkspecs/features/yacc.prf:
/usr/local/Qt4.7/mkspecs/features/lex.prf:
/usr/local/Qt4.7/mkspecs/features/include_source_dir.prf:
/Library/Frameworks/QtOpenGL.framework/QtOpenGL.prl:
/Library/Frameworks/QtGui.framework/QtGui.prl:
/Library/Frameworks/QtCore.framework/QtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/local/Qt4.7/mkspecs/macx-g++ -o Makefile assignment2.pro

assignment2.app/Contents/PkgInfo: 
	@$(CHK_DIR_EXISTS) assignment2.app/Contents || $(MKDIR) assignment2.app/Contents 
	@$(DEL_FILE) assignment2.app/Contents/PkgInfo
	@echo "APPL????" >assignment2.app/Contents/PkgInfo
assignment2.app/Contents/Resources/empty.lproj: 
	@$(CHK_DIR_EXISTS) assignment2.app/Contents/Resources || $(MKDIR) assignment2.app/Contents/Resources 
	@touch assignment2.app/Contents/Resources/empty.lproj
	
assignment2.app/Contents/Info.plist: 
	@$(CHK_DIR_EXISTS) assignment2.app/Contents || $(MKDIR) assignment2.app/Contents 
	@$(DEL_FILE) assignment2.app/Contents/Info.plist
	@sed -e "s,@ICON@,,g" -e "s,@EXECUTABLE@,assignment2,g" -e "s,@TYPEINFO@,????,g" /usr/local/Qt4.7/mkspecs/macx-g++/Info.plist.app >assignment2.app/Contents/Info.plist
dist: 
	@$(CHK_DIR_EXISTS) .tmp/assignment21.0.0 || $(MKDIR) .tmp/assignment21.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/assignment21.0.0/ && $(COPY_FILE) --parents main.h window.h renderer.h md2.h vector3d.h .tmp/assignment21.0.0/ && $(COPY_FILE) --parents main.cpp window.cpp renderer.cpp md2.cpp vector3d.cpp .tmp/assignment21.0.0/ && (cd `dirname .tmp/assignment21.0.0` && $(TAR) assignment21.0.0.tar assignment21.0.0 && $(COMPRESS) assignment21.0.0.tar) && $(MOVE) `dirname .tmp/assignment21.0.0`/assignment21.0.0.tar.gz . && $(DEL_FILE) -r .tmp/assignment21.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) -r assignment2.app
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_renderer.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_renderer.cpp
moc_renderer.cpp: md2.h \
		vector3d.h \
		renderer.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ renderer.h -o moc_renderer.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

main.o: main.cpp main.h \
		window.h \
		renderer.h \
		md2.h \
		vector3d.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

window.o: window.cpp window.h \
		renderer.h \
		md2.h \
		vector3d.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o window.o window.cpp

renderer.o: renderer.cpp renderer.h \
		md2.h \
		vector3d.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o renderer.o renderer.cpp

md2.o: md2.cpp md2.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o md2.o md2.cpp

vector3d.o: vector3d.cpp vector3d.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o vector3d.o vector3d.cpp

moc_renderer.o: moc_renderer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_renderer.o moc_renderer.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:


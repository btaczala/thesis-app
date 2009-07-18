cmake_minimum_required(VERSION 2.6)
PROJECT(Thesis_application)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(Boost REQUIRED ) 
find_package(Qt4 REQUIRED ) 
find_package(QwtPlot3D-qt4 REQUIRED)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include_directories(${KDE4_INCLUDES})

if(UNIX)
  add_definitions( -fexceptions )
else(UNIX)
  if(WIN32)
  endif(WIN32)
endif(UNIX)

include(${QT_USE_FILE})


include_directories( ${Boost_INCLUDE_DIRS} )
include_directories("./")
include_directories("./fl")
include_directories("./fl/muparser")
include_directories(${CMAKE_BINARY_DIR})

add_subdirectory(fl)

set ( thesis_src 
  src/main.cpp
  src/mainwindow.cpp
  src/commons.cpp
  src/actions.cpp
  src/tabwidget.cpp
  src/plotwidget.cpp
  src/tabwidgetitem.cpp
  src/newcontinousfunctiondialog.cpp
  src/functionsproxy.cpp
  ) 
set ( thesis_hdrs 
  src/mainwindow.h
  src/commons.h
  src/actions.h
  src/tabwidget.h
  src/plotwidget.h
  src/tabwidgetitem.h
  src/newcontinousfunctiondialog.h
  src/functionsproxy.h	
  ) 
set ( thesis_moc
  src/mainwindow.h
  src/tabwidget.h
  src/tabwidgetitem.h
  src/newcontinousfunctiondialog.h
  )
set(thesis_rsc resources/main.qrc )
set( thesis_ui ui/newcontinousfunction.ui ) 


qt4_wrap_cpp( thesis_moc_src ${thesis_moc} )
qt4_wrap_ui( thesis_ui_src ${thesis_ui})
qt4_add_resources(thesis_rsc_src ${thesis_rsc})

add_executable(Thesis-app ${thesis_src} ${thesis_hdrs} ${thesis_moc_src} ${thesis_rsc_src} ${thesis_ui_src})
if(UNIX)
  set(KDEEDULIBRARY /usr/lib/libkdeeduui.so.4.3.0)
elseif(UNIX)
  if(WIN32)
    #set(KDEEDULIBRARY /usr/lib/libkdeeduui.so.4.3.0)
    #TODO
  endif(WIN32)
endif(UNIX)

target_link_libraries(Thesis-app ${QT_LIBRARIES} ${KDE4_KDECORE_LIBS} /usr/lib/libkdeeduui.so.4.3.0 ${QWTPLOT3D_LIBRARIES} fl) 

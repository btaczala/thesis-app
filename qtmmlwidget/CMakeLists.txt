cmake_minimum_required(VERSION 2.6)
PROJECT(qtmml)

find_package(Qt4 REQUIRED ) 

include(${QT_USE_FILE})
include_directories("./")

set ( qtmml_src 
  src/qtmmlwidget.cpp
  ) 
set ( qtmml_hdrs 
  src/qtmmlwidget.h
) 
set ( qtmml_moc
  src/qtmmlwidget.h
)
qt4_wrap_cpp( qtmml_moc_src ${qtmml_moc} )

ADD_LIBRARY(qtmml ${qtmml_src} ${qtmml_hdrs} ${qtmml_moc_src})
target_link_libraries( qtmml ${QT_LIBRARIES} ) 

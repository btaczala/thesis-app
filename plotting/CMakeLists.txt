cmake_minimum_required(VERSION 2.6)
PROJECT(plotting)

find_package(Qt4 REQUIRED ) 

include(${QT_USE_FILE})
include_directories("./")

set ( plotting_src 
  kplotaxis.cpp
  kplotobject.cpp
  kplotpoint.cpp
  kplotwidget.cpp
  ) 
set ( plotting_hdrs 
  kplotaxis.h
  kplotobject.h
  kplotpoint.h
  kplotwidget.h
) 
set ( plotting_moc
  kplotwidget.h
)
qt4_wrap_cpp( plotting_moc_src ${plotting_moc} )

ADD_LIBRARY(plotting ${plotting_src} ${plotting_hdrs} ${plotting_moc_src})
target_link_libraries( plotting ${QT_LIBRARIES} ) 

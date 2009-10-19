cmake_minimum_required(VERSION 2.6)
PROJECT(fl)

find_package(Boost REQUIRED ) 

include_directories( ${Boost_INCLUDE_DIRS} )
include_directories("./")
include_directories(muparser)

add_subdirectory( muparser ) 

set ( fl_src 
  function2dbase.cpp
  function3dbase.cpp
  functiondiscrete.cpp
  functioncontinous.cpp
  functionMixed.cpp
  ) 
set ( fl_hdrs 
  function2dbase.h
  function3dbase.h
  functionbase.h
  functiondiscrete.h
  functioncontinous.h
  functionMixed.h
  functionException.h
  ) 

ADD_LIBRARY(fl ${fl_src} ${fl_hdrs} )
target_link_libraries( fl muparser ) 


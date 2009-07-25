cmake_minimum_required(VERSION 2.6)
PROJECT(Thesis_application)

SET( APP_VERSION_MAJOR "0" )
SET( APP_VERSION_MINOR "0" )
SET( APP_VERSION_PATCH "1a" )


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(Boost REQUIRED ) 
find_package(Qt4 REQUIRED ) 
#find_package(QwtPlot3D-qt4 REQUIRED)


if(UNIX)
  add_definitions( -fexceptions )
else(UNIX)
  if(WIN32)
  endif(WIN32)
endif(UNIX)

include(${QT_USE_FILE})


include_directories( ${Boost_INCLUDE_DIRS} )
include_directories("./")
include_directories("./plotting")
include_directories("./fl")
include_directories("./fl/muparser")
include_directories("./QtColorPicker")
include_directories(${CMAKE_BINARY_DIR})
#include_directories(${QWTPLOT3D_INCLUDE_DIR})

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
  src/workspacesettingsdialog.cpp
  src/newfunctionmixeddialog.cpp
  
  plotting/kplotaxis.cpp
  plotting/kplotobject.cpp
  plotting/kplotpoint.cpp
  plotting/kplotwidget.cpp
  
  QtColorPicker/qtcolorpicker.cpp
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
  src/workspacesettingsdialog.h
  src/newfunctionmixeddialog.h
  
  plotting/kplotaxis.h
  plotting/kplotobject.h
  plotting/kplotpoint.h
  plotting/kplotwidget.h
  
  QtColorPicker/qtcolorpicker.h
  ) 
set ( thesis_moc
  src/mainwindow.h
  src/tabwidget.h
  src/tabwidgetitem.h
  src/newcontinousfunctiondialog.h
  src/plotwidget.h
  src/workspacesettingsdialog.h
  src/newfunctionmixeddialog.h
  
  plotting/kplotwidget.h
  QtColorPicker/qtcolorpicker.h
  
  )
set(thesis_rsc resources/main.qrc )
set( thesis_ui 
    ui/newcontinousfunction.ui 
    ui/range.ui
    ui/functionMixed.ui
) 


qt4_wrap_cpp( thesis_moc_src ${thesis_moc} )
qt4_wrap_ui( thesis_ui_src ${thesis_ui})
qt4_add_resources(thesis_rsc_src ${thesis_rsc})

add_executable(Thesis-app ${thesis_src} ${thesis_hdrs} ${thesis_moc_src} ${thesis_rsc_src} ${thesis_ui_src})
add_executable( gen src/genFunctions.cpp)

target_link_libraries(Thesis-app ${QT_LIBRARIES} fl ) 
target_link_libraries(gen ${QT_LIBRARIES} )


IF(NOT QT_CONFIG MATCHES "static")
	if( WIN32 )
		Find_File(qtgui QtGui4.dll PATHS ${QT_LIBRARY_DIR} NO_DEFAULT_PATH)
		Find_File(qtcore QtCore4.dll PATHS ${QT_LIBRARY_DIR} NO_DEFAULT_PATH)
		Find_File(qtmain qtmain.lib PATHS ${QT_LIBRARY_DIR} NO_DEFAULT_PATH)
		INSTALL(FILES ${qtgui} ${qtcore} ${qtmain} ${qtnetwork} DESTINATION bin )
	ENDIF( WIN32 )
ENDIF(NOT QT_CONFIG MATCHES "static")

INSTALL(TARGETS Thesis-app
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Thesis application")
SET(CPACK_PACKAGE_VENDOR "Bartosz Taczala")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/GPL.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR ${APP_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${APP_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${APP_VERSION_PATCH})
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "bta-thesis")
IF(WIN32 AND NOT UNIX)
	SET(CPACK_NSIS_DISPLAY_NAME ${CPACK_PACKAGE_INSTALL_DIRECTORY} "thesis_app")
	SET(CPACK_NSIS_CONTACT "btaczala@wi.ps.pl")
ENDIF(WIN32 AND NOT UNIX)
INCLUDE(CPack)

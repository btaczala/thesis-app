/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef THESIS_UI_PLOTWIDGET_H
#define THESIS_UI_PLOTWIDGET_H

#include <QPointer>
#include <QObject>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <QMap>
#include <QThread>
#include <QMutex>
#include <QColor>

class QWidget ; 
class KPlotWidget ; 
class KPlotObject ; 

namespace fl{
    class FunctionBase ; 
}
namespace Qwt3D{
    class SurfacePlot ; 
}

/**
 * \struct	FunctionInfo{
 *
 * \brief	.
 *
 * \author	Bartosz Taczala
 * \date	2009-08-07
**/

struct FunctionInfo{
                    QString _fId ; 
                    QColor _fColor ; 
                };

namespace Thesis {
    namespace UI {
        class CalculatingThread ; 

        /**
         * \class	PlotWidgetProxy
         *
         * \brief	Plot widget proxy. 
         *
         * \author	Bartosz Taczala
         * \date	2009-08-07
        **/

        class PlotWidgetProxy : public QObject
        {
            Q_OBJECT
            public:
                
                typedef QMap<fl::FunctionBase*, KPlotObject* > FunctionsPlotMapType ;

                /**
                 * \fn	PlotWidgetProxy(QWidget* pParent)
                 *
                 * \brief	Constructor. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	pParent	If non-null, the parent. 
                **/

                PlotWidgetProxy(QWidget* pParent); 

                /**
                 * \fn	virtual ~PlotWidgetProxy()
                 *
                 * \brief	Finaliser. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                virtual ~PlotWidgetProxy();

                /**
                 * \fn	QWidget * widget()
                 *
                 * \brief	Widgets this object. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	null if it fails, else. 
                **/

                QWidget * widget() ;

                /**
                 * \fn	void addFunction ( fl::FunctionBase * pFunction, const QColor & color = QColor() )
                 *
                 * \brief	Adds a function to 'color'. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	pFunction	If non-null, the function. 
                 * \param	color		The color. 
                **/

                void addFunction ( fl::FunctionBase * pFunction, const QColor & color = QColor() ) ; 

                /**
                 * \fn	void deleteFunction( const QString & fID )
                 *
                 * \brief	Deletes the function described by fID. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	fID	The identifier. 
                **/

                void deleteFunction( const QString & fID ) ; 

                /**
                 * \fn	double xMin() const
                 *
                 * \brief	X coordinate minimum. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	. 
                **/

                double xMin() const { return m_xMin ; }

                /**
                 * \fn	double xMax() const
                 *
                 * \brief	X coordinate maximum. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	. 
                **/

                double xMax() const { return m_xMax ; }

                /**
                 * \fn	double yMin() const
                 *
                 * \brief	Y coordinate minimum. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	. 
                **/

                double yMin() const { return m_yMin ; }

                /**
                 * \fn	double yMax() const
                 *
                 * \brief	Y coordinate maximum. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	. 
                **/

                double yMax() const { return m_yMax ; }

                /**
                 * \fn	void changeRange( double xstart,double xstop,double ystart,double ystop )
                 *
                 * \brief	Change range. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	xstart	The xstart. 
                 * \param	xstop	The xstop. 
                 * \param	ystart	The ystart. 
                 * \param	ystop	The ystop. 
                **/

                void changeRange( double xstart,double xstop,double ystart,double ystop ) ;
                
                const FunctionsPlotMapType plotMap() const { return m_PlotsFunctions ; } 
            public slots:

                /**
                 * \fn	void zoomIn()
                 *
                 * \brief	Zoom in. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void zoomIn();

                /**
                 * \fn	void zoomOut()
                 *
                 * \brief	Zoom out. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void zoomOut();
                
            protected:
                
                typedef boost::shared_ptr<fl::FunctionBase> functionShPtr;
                typedef boost::shared_ptr<KPlotObject> KPlotObjectShPtr;
                
                boost::shared_ptr<KPlotWidget> m_pKPlotWidget ;
                boost::shared_ptr<CalculatingThread> m_pCalcThread ; 
                FunctionsPlotMapType m_PlotsFunctions ; 
                QWidget * m_pParent ; 
                fl::FunctionBase * m_pLastAddedFunction ;  
                double m_xMin ; 
                double m_xMax ;
                double m_yMin ; 
                double m_yMax ; 
                
                friend class CalculatingThread ; 
            signals:

                /**
                 * \fn	void functionAdded( const FunctionInfo & fInfo )
                 *
                 * \brief	Function added. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	fInfo	The information. 
                **/

                void functionAdded( const FunctionInfo & fInfo ) ; 
            private slots:

                /**
                 * \fn	void threadEnded()
                 *
                 * \brief	Thread ended. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void threadEnded() ; 
                
                
        };
        class CalculatingThread : public QThread {
            public:
                enum WorkType {
                    eAdd =0,
                    eRecalculate
                };
                CalculatingThread() ; 
                ~CalculatingThread();

                /**
                 * \fn	void setLimits ( double,double,double,double)
                 *
                 * \brief	Sets the limits. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param		The. 
                 * \param		The. 
                 * \param		The. 
                 * \param		The. 
                **/

                void setLimits ( double,double,double,double);

                /**
                 * \fn	void run()
                 *
                 * \brief	Runs this object. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void run() ; 

                /**
                 * \fn	void setWorkType( WorkType type )
                 *
                 * \brief	Sets a work type. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	type	The type. 
                **/

                void setWorkType( WorkType type ) { 
                    m_mutex.lock();
                    m_WorkType = type ; 
                    m_mutex.unlock();
                }

                /**
                 * \fn	WorkType workType() const
                 *
                 * \brief	Work type. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	. 
                **/

                WorkType workType() const { return m_WorkType ; } 

                /**
                 * \fn	void setFunctions( const PlotWidgetProxy::FunctionsPlotMapType & pFunctionPlotMap )
                 *
                 * \brief	Sets the functions. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	pFunctionPlotMap	The function plot map. 
                **/

                void setFunctions( const PlotWidgetProxy::FunctionsPlotMapType & pFunctionPlotMap ) ; 

				/**
				 * \fn	void setLastFunctionAdded( fl::FunctionBase * pFunction )
				 *
				 * \brief	Sets a last function added. 
				 *
				 * \author	Bartosz Taczala
				 * \date	2009-08-07
				 *
				 * \param	pFunction	If non-null, the function. 
				**/

				void setLastFunctionAdded( fl::FunctionBase * pFunction ) {m_pLastFunctionAdded = pFunction;}

				/**
				 * \fn	void setLastPlotAdded( KPlotObject * pPlot )
				 *
				 * \brief	Sets a last plot added. 
				 *
				 * \author	Bartosz Taczala
				 * \date	2009-08-07
				 *
				 * \param	pPlot	If non-null, the plot. 
				**/

				void setLastPlotAdded( KPlotObject * pPlot ) { m_pLastPlotAdded = pPlot ; } 

				/**
				 * \fn	fl::FunctionBase * lastFunctionAdded() const
				 *
				 * \brief	Last function added. 
				 *
				 * \author	Bartosz Taczala
				 * \date	2009-08-07
				 *
				 * \return	null if it fails, else. 
				**/

				fl::FunctionBase * lastFunctionAdded() const { return m_pLastFunctionAdded;}

				/**
				 * \fn	KPlotObject *lastPlotAdded() const
				 *
				 * \brief	Last plot added. 
				 *
				 * \author	Bartosz Taczala
				 * \date	2009-08-07
				 *
				 * \return	null if it fails, else. 
				**/

				KPlotObject *lastPlotAdded() const { return m_pLastPlotAdded ;}

                /**
                 * \fn	QList<KPlotObject *> result()
                 *
                 * \brief	Results this object. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	null if it fails, else a list of. 
                **/

                QList<KPlotObject *>  result() { return m_plotsCalculated ; }  

                /**
                 * \fn	void freeLists()
                 *
                 * \brief	Free lists. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void freeLists() ; 
            private:
                QMutex m_mutex ; 
                QList<fl::FunctionBase *> m_functionToCalculate ; 
                QList<KPlotObject *> m_plotsCalculated;
				KPlotObject *m_pLastPlotAdded ; 
				fl::FunctionBase * m_pLastFunctionAdded ; 
                double m_xMin ; 
                double m_xMax ;
                double m_yMin ; 
                double m_yMax ;
                WorkType m_WorkType ; 
        } ;
    }
}

#endif // THESIS_UI_PLOTWIDGET_H

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
struct FunctionInfo{
                    QString _fId ; 
                    QColor _fColor ; 
                };

namespace Thesis {
    namespace UI {
        class CalculatingThread ; 
        class PlotWidgetProxy : public QObject
        {
            Q_OBJECT
            public:
                
                PlotWidgetProxy(QWidget* pParent); 
                virtual ~PlotWidgetProxy();
                QWidget * widget() ;
                void addFunction ( fl::FunctionBase * pFunction, const QColor & color = QColor() ) ; 
                void deleteFunction( const QString & fID ) ; 
                double xMin() const { return m_xMin ; }
                double xMax() const { return m_xMax ; }
                double yMin() const { return m_yMin ; }
                double yMax() const { return m_yMax ; }
                
                void changeRange( double xstart,double xstop,double ystart,double ystop ) ;
            public slots:
                void zoomIn();
                void zoomOut();
            protected:
                
                typedef boost::shared_ptr<fl::FunctionBase> functionShPtr;
                typedef boost::shared_ptr<KPlotObject> KPlotObjectShPtr;
                typedef QMap<fl::FunctionBase*, KPlotObject* > FunctionsPlotMapType ;
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
                
                void functionAdded( const FunctionInfo & fInfo ) ; 
            private slots:
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
                void setLimits ( double,double,double,double);
                void run() ; 
                void setWorkType( WorkType type ) { 
                    m_mutex.lock();
                    m_WorkType = type ; 
                    m_mutex.unlock();
                }
                WorkType workType() const { return m_WorkType ; } 
                void setFunctions( const PlotWidgetProxy::FunctionsPlotMapType & pFunctionPlotMap ) ; 
                QList<KPlotObject *>  result() { return m_plotsCalculated ; }  
                void freeLists() ; 
            private:
                QMutex m_mutex ; 
                QList<fl::FunctionBase *> m_functionToCalculate ; 
                QList<KPlotObject *> m_plotsCalculated;
                double m_xMin ; 
                double m_xMax ;
                double m_yMin ; 
                double m_yMax ;
                WorkType m_WorkType ; 
        } ;
    }
}

#endif // THESIS_UI_PLOTWIDGET_H

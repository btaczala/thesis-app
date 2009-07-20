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

class QWidget ; 
class KPlotWidget ; 
class KPlotObject ; 

namespace fl{
    class FunctionBase ; 
}
namespace Qwt3D{
    class SurfacePlot ; 
}

namespace Thesis {
    namespace UI {
        class PlotWidgetProxy : public QObject
        {
            Q_OBJECT
            public:
                enum PlotType {
                    ePlot2D = 0,
                    ePlot3D
                };
                PlotWidgetProxy(Thesis::UI::PlotWidgetProxy::PlotType type, QWidget* pParent); 
                virtual ~PlotWidgetProxy();
                QWidget * widget() ;
                void addFunction ( fl::FunctionBase * pFunction ) ; 
                void changeType( PlotType  newType) ; 
                double xMin() const { return m_xMin ; }
                double xMax() const { return m_xMax ; }
                double yMin() const { return m_yMin ; }
                double yMax() const { return m_yMax ; }
                
                void changeRange( double xstart,double xstop,double ystart,double ystop ) ;
                
                PlotType plotType() const { return m_PlotType ; } 
            protected:
                boost::shared_ptr<QWidget> m_pWidget ; 
                boost::shared_ptr<KPlotWidget> m_pKPlotWidget ;
                boost::shared_ptr<Qwt3D::SurfacePlot> m_pSurfacePlotWidget ; 
                
                PlotType m_PlotType ; 
                
                QMap<KPlotObject*, fl::FunctionBase *> m_PlotsFunctions ; 
                QWidget * m_pParent ; 
                void setWidget( PlotType _type) ; 
                
                double m_xMin ; 
                double m_xMax ;
                double m_yMin ; 
                double m_yMax ; 
            signals:
                void plotChanging() ; 
                void plotChanged();
        };
    }
}

#endif // THESIS_UI_PLOTWIDGET_H

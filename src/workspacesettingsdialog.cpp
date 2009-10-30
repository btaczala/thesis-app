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

#include "workspacesettingsdialog.h"
#include "tabwidgetitem.h"
#include "ui_range.h"
#include "commons.h"

#include <QTabWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include "plotwidget.h"

using namespace Thesis::UI;

WorkspaceSettingsDialog::WorkspaceSettingsDialog(TabWidgetItem* pTabItem, QWidget* pParent /*=NULL*/):
QDialog(pParent),
m_pTabWidget(new QTabWidget(this) ),
m_pTabItem(pTabItem),
m_pButtonBox( new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel) )

{
    SET_MAIN_APPLICATION_ICON;
    m_pRangeTab.reset( new RangeTab(this) );
     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(m_pTabWidget);
     mainLayout->addWidget(m_pButtonBox);
     
     connect(m_pButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
     connect(m_pButtonBox, SIGNAL(rejected()), this, SLOT(reject()));
     
     setLayout(mainLayout);

     setWindowTitle(tr("Tab Dialog"));
    
    m_pTabWidget->addTab( m_pRangeTab.get() ,tr("range"));
}

RangeTab::RangeTab(WorkspaceSettingsDialog* pParent): 
QWidget(pParent),
m_pParent(pParent),
m_pForm( new Ui::RangeForm())
{
    m_pForm->setupUi(this);
        
    PlotWidgetProxy *proxy = pParent->m_pTabItem->plotProxy();
    
    m_pForm->xMinSpinBox->setValue( proxy->xMin() );
    m_pForm->xMaxSpinBox->setValue( proxy->xMax() );
    m_pForm->yMinSpinBox->setValue( proxy->yMin() );
    m_pForm->yMaxSpinBox->setValue( proxy->yMax() );
}

double RangeTab::xMin() const
{
    return m_pForm->xMinSpinBox->value();
}
double RangeTab::xMax() const
{
    return m_pForm->xMaxSpinBox->value();
}
double RangeTab::yMin() const
{
    return m_pForm->yMinSpinBox->value();
}
double RangeTab::yMax() const
{
    return m_pForm->yMaxSpinBox->value();
}


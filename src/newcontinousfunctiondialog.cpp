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

#include "newcontinousfunctiondialog.h"
#include "ui_newcontinousfunction.h"
#include "commons.h"

#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include "QtColorPicker/qtcolorpicker.h"

using namespace Thesis::UI;

NewContinousFunctionDialog::NewContinousFunctionDialog(QWidget* parent, Qt::WindowFlags f) : 
QDialog(parent,f),
m_pDialog( new Ui::PasswordDialog())
{
    cLOG() ; 
    m_pDialog->setupUi(this);
    m_pDialog->RangeXSpinBox->setEnabled(false);
    m_pDialog->RangeYSpinBox->setEnabled(false);
    m_pColorPicker = new QtColorPicker(this) ;
    m_pColorPicker->insertColor(QColor("white"), "White");
    m_pColorPicker->insertColor(QColor("black"), "Black");
    m_pColorPicker->insertColor(QColor("green"), "Green");
    m_pColorPicker->insertColor(QColor("darkGreen"), "Dark green");
    m_pColorPicker->insertColor(QColor("blue"), "Blue");
    m_pColorPicker->insertColor(QColor("darkBlue"), "Dark blue");
    m_pColorPicker->insertColor(QColor("cyan"), "Cyan");
    m_pColorPicker->insertColor(QColor("darkCyan"), "Dark cyan");
    m_pColorPicker->insertColor(QColor("magenta"), "Magenta");
    m_pColorPicker->insertColor(QColor("darkMagenta"), "Dark magenta");
    m_pColorPicker->insertColor(QColor("yellow"), "Yellow");
    m_pColorPicker->insertColor(QColor("grey"), "Grey");
    m_pDialog->colorPickerWidget->addWidget( m_pColorPicker );
    
    m_pDialog->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    
    m_pTimer = new QTimer(this);

    
    connect ( m_pDialog->CustomRangeCheckBox, SIGNAL(toggled(bool)),this,SLOT(customRangeChecked(bool)));
    connect ( m_pTimer, SIGNAL(timeout()),this,SLOT(checkIfOk()));
    
    m_pTimer->start(2000);
}

void NewContinousFunctionDialog::accept()
{
    // check if we cannot accept 
    
    QDialog::accept();
}
void NewContinousFunctionDialog::done(int done)
{
    QDialog::done(done);
}
void NewContinousFunctionDialog::customRangeChecked(bool checked)
{
    if ( checked ) {
        m_pDialog->RangeXSpinBox->setEnabled(true);
        m_pDialog->RangeYSpinBox->setEnabled(true);
    }
    else {
        m_pDialog->RangeXSpinBox->setEnabled(false);
        m_pDialog->RangeYSpinBox->setEnabled(false);
    }
}
void NewContinousFunctionDialog::checkIfOk()
{
    cLOG() ; 
    bool bOk ;
    
    QString function = m_pDialog->functionLineEdit->text();
    QString variables = m_pDialog->variableLineEdit->text() ; 
    
    int dimensionNumber = m_pDialog->dimensionSpinBox->value();
    
    if ( function.isEmpty() || variables.isEmpty() ) 
        bOk = false ;
    else{
        variables.remove(',');
        if ( dimensionNumber-1 == variables.length() ) {
            bOk = true ; 
            for ( int i = 0 ; i < variables.size() ; ++i ) {
                if ( ! function.contains( variables.at(i) ) ){
                    bOk = false ; 
                    break ; 
                }
            }
        }
        else
            bOk = false ; 
    }
    if ( bOk ) 
        m_pDialog->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    else
        m_pDialog->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

const QString NewContinousFunctionDialog::fuction() const
{
    return m_pDialog->functionLineEdit->text() ; 
}

const QStringList Thesis::UI::NewContinousFunctionDialog::variables() const
{
    QString variables = m_pDialog->variableLineEdit->text() ;
    variables.remove(',');
    QStringList lst ; 
    for ( int i = 0 ; i < variables.size() ; ++i ) {
        lst.push_back(QString(variables.at(i)));
    }
    return lst ; 
}

int Thesis::UI::NewContinousFunctionDialog::dimensions() const
{
    return m_pDialog->dimensionSpinBox->value();
}

QColor Thesis::UI::NewContinousFunctionDialog::color() const
{
    return m_pColorPicker->currentColor();
}

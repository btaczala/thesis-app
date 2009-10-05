/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "convolutionpicker.h"

using namespace Thesis::UI;


Thesis::UI::ConvolutionPicker::ConvolutionPicker ( QWidget* parent, Qt::WindowFlags f ) : QDialog ( parent, f ), m_pForm(new Ui::ConvolutionPicker() )
{
    m_pForm->setupUi(this);
    
}
void ConvolutionPicker::accept()
{
    QDialog::accept();
}
void ConvolutionPicker::reject()
{
    QDialog::reject();
}

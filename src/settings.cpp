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

#include "settings.h"
#include "commons.h"

#include <QCoreApplication>
#include <QSettings>
#include <QDir>



using namespace Thesis;

Thesis::Settings* Thesis::Settings::instance()
{
    static std::auto_ptr<Settings> pRet (new Settings() ) ; 
    if ( !pRet->m_bInit ) 
        pRet->init();
    return pRet.get();
}

Thesis::Settings::Settings() : m_bInit(false),m_pSettings(NULL)
{
}
void Thesis::Settings::init()
{
     QCoreApplication::setOrganizationName("bta");
     QCoreApplication::setOrganizationDomain("wi.ps.pl");
     QCoreApplication::setApplicationName("Thesis");
     m_pSettings.reset(new QSettings());
     
     m_defaults[SettingsNames::MathLib::scDefaultDiscreteStep] = 0.01;
     m_defaults[SettingsNames::UI::scLastDirectoryOpened] = QDir::homePath() ; 
     m_defaults[SettingsNames::UI::scLastDirectoryScreenshot] = QDir::homePath();
}

void Settings::setValue(const QString& scValName, const QVariant& variant)
{
    LOG( "Setting value " << scValName << " to: " << variant ) ; 
    m_pSettings->setValue(scValName,variant);
}

QVariant Settings::value(const QString& scValName)
{
    QVariant toRet = m_pSettings->value(scValName);
    if ( toRet.isNull() ) 
    {
        toRet = m_defaults[scValName] ; 
        if ( toRet.isNull() ) {
            LOG("There is no settings for" << scValName <<" in settings file nor in default map" ) ; 
        }
    }
    return toRet ; 
}



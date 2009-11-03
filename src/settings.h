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

#ifndef THESIS_SETTINGS_H
#define THESIS_SETTINGS_H


#include <memory>
#include <QString>
#include <QVariant>
class QSettings;
namespace Thesis {

    class Settings
    {
        public:
            static Settings * instance() ; 
            
            void setValue( const QString & scValName, const QVariant & variant ) ; 
            QVariant value ( const QString & scValName ) ; 
        private:
            Settings() ;             
            void init() ;
            bool m_bInit ; 
            std::auto_ptr<QSettings> m_pSettings ;
            QMap<QString,QVariant> m_defaults ; 
    };
    namespace SettingsNames{
        namespace MathLib{
            static const QString scDefaultDiscreteStep = "Math/discreteStep" ; 
        }
        namespace UI{
            static const QString scMaximizedWindow = "UI/maximizedWindow";
            static const QString scLastDirectoryOpened = "UI/lastDirOpened" ; 
            static const QString scLastDirectoryScreenshot="UI/lastDirScreenShot";
        }
    }

}

#endif // THESIS_SETTINGS_H

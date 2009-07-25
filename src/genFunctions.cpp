

#include <cmath>
#include <QDebug>
#include <QFile>
#include <boost/function.hpp>

typedef boost::function<double ( double ) > mathFunction ; 


void generateFunction( const QString & fName,  double start, double stop, double step, mathFunction mathFn ) {
    QString line ; 
    QFile file(fName);
    if ( file.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text ) ){
        for ( double it = start ; it < stop ; it += step ) {
            double val = mathFn(it);
            line = QString("%1 %2").arg(it).arg( val ) ;
            file.write(line.toAscii());
            file.write("\n");
        }
        
        file.close();
    }
}

double myFunction( double x ) {
    return 2*x - 7 ; 
}


int main( int, char ** ) {
    
    /*generateFunction("sin.fnt",-4,3,0.1, mathFunction(&sin));
    generateFunction("cos.fnt",-4,3,0.1, mathFunction(&cos));
    generateFunction("abs.fnt",-4,3,0.1, mathFunction(&abs));
    generateFunction("myFunction.fnt",-4,3,0.1, mathFunction(&myFunction));*/
    return 1; 
}
#include <iostream>
#include <cmath>
#include <QApplication>
#include <vector>
#include <sstream>

#include <Eigen/Core>
#include <Eigen/LU>

#include "kplotwidget.h"
#include "kplotobject.h"
#include "kplotaxis.h"
#include <muParser.h>
#include "polymonialapproximatio.h"


USING_PART_OF_NAMESPACE_EIGEN

using namespace std; 

string approximate( vector<double> & xs, vector<double> & ys, int m ) {
    string ret ; 
    if ( ! ( xs.size() > m+1 ) ) 
        return "" ; 
    // znajdź wartość sum Sk
    // s_k = sum ( i=1, n) { (x_i)^k } 
    const int realM = m + 1; 
    vector<double > Sk ; 
    MatrixXd S( realM,realM ) ; 
    vector<double > tm ; 
    double var =0 ; 
    
    for ( int k = 0 ; k < 2 * realM ; ++k ) {
        for ( int j = 0 ; j < xs.size() ; ++j ) {
            var += pow(xs.at(j),k);
        }
        Sk.push_back(var);
        var = 0 ; 
    }
    for ( int cross = 0 ; cross < realM ; ++cross ) {
        for ( int j = 0 ; j < realM ; ++j ){
            S( j , cross ) = Sk.at(cross+j) ; 
        }
    }
    MatrixXd T(realM,1) ; 
    for ( int k = 0 ; k < realM ; ++k ) {
        for ( int j = 0 ; j < xs.size() ; ++j ) {
            var += pow(xs.at(j),k)*ys.at(j);
        }
        T(k,0) = var ; 
        var = 0 ; 
    }
    //cout << S << endl ; 
    //cout << T << endl ; 
    MatrixXd A(realM,1); 
    MatrixXd invS = S.inverse();
    A = invS * T ;
    //cout << A ;
    stringstream stream ;
    for ( int j = 0 ; j < A.rows() ; ++j ) 
        stream << "a("<< j << ") =" << A(j,0) <<endl ;
    cout << stream.str();
    stringstream result ; 
    for ( int i = 0 ; i < A.rows() ; ++ i ) {
        result << A(i,0)<< "*pow(x," << i <<")";
        if ( i != A.rows() -1 ) 
            result << " + " ;
    }
    cout << result.str() << endl ;
    return result.str();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    vector<double> x ;
    vector<double> y ;
    
    
    
    KPlotWidget * pWid = new KPlotWidget( NULL ) ;
    pWid->setLimits( -0.1, 6.38, -1.1, 1.1 );
    KPlotObject *sineobj = new KPlotObject( Qt::red, KPlotObject::Lines, 2 );
    KPlotObject *sineobj2 = new KPlotObject( Qt::red, KPlotObject::Points, 2 );
    
    
    
    
    for ( float t=0.0; t<=6.28; t+=0.04 ) {
        x.push_back(t);
        y.push_back(sin(t));
        sineobj->addPoint( t, sin(t) );
    }
    
    fl::Function2D::PolymonialApproximation pA ( 4 )  ; 
    string appr= approximate(x,y,9);
    mu::Parser *parser = mu::Parser::proxyFLParser();
    double xVal ; 
    parser->DefineVar("x",&xVal);
    parser->SetExpr(appr);
    
    
    for ( float t=0.0; t<=6.28; t+=0.04 ) {
        xVal = t; 
        sineobj2->addPoint(xVal,parser->Eval());
    }
    
    pWid->addPlotObject( sineobj );
    pWid->addPlotObject( sineobj2 );
    pWid->show();
    pWid->axis( KPlotWidget::BottomAxis )->setLabel( ("Angle in radians") );
    pWid->update();
    
     
    app.exec();
}
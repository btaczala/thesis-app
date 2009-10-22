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
    MatrixXd A(realM,1); 
    MatrixXd invS = S.inverse();
    A = invS * T ;
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


std::list<string> splineInterpolation( vector<double> & xs, vector<double> & ys, int m, double z0) {
	//http://en.wikipedia.org/wiki/Spline_interpolation
	// S_i(x) = y_i + z_i * ( x - x_i ) + ( z_{i+1} - z_i ) / ( 2* ( x_{i+1} - x_i)) * (x - x_i)^2
	list<string> result ; 

	const int mainI = m; 
	vector<double> z,c1,c2; 
	double zVal,c1Val,c2Val ;   
	for ( int i = 0 ; i < m+1 ; ++i ){
		if ( i ==0 )
			z.push_back(z0);
		else{
			double licznik, mianownik ; 
			licznik = ys.at(i) - ys.at(i-1) ; 
			mianownik = xs.at(i)-xs.at(i-1);
			zVal = -1*z.at(i-1) ; 
			zVal += 2 * licznik/mianownik ; 
			z.push_back(zVal);
		}
	}
	for ( int i = 0 ; i < m ; ++i ){
		c1Val = ys.at(i) - z.at(i)*xs.at(i);
		c1.push_back(c1Val);
	}
	list<string> S_ ; 
	for ( int i = 0 ; i < m ; ++i ){
		stringstream res2 ; 
		res2 << ys.at(i) << " + " << z.at(i) << "*( x - " << xs.at(i) << " ) + " << "( " << z.at(i+1) - z.at(i) << ") / " << 2*(xs.at(i+1) - xs.at(i)) << "* ( x - " << xs.at(i) << ")^2";
		S_.push_back(res2.str());



		stringstream res ; 
		c2Val = ( (z.at(i+1) - z.at(i)) / ((double)2 * (xs.at(i+1)- xs.at(i) )));
		c2.push_back(c2Val);
		res << c1.at(i) << " + " << z.at(i)<< " *x + " << c2.at(i)<< "x*x - 2*" << c2.at(i)*xs.at(i)<< " *x + "<< c2.at(i)*xs.at(i)*xs.at(i);
		result.push_back(res.str());
		cout << "F(x), for x in [" << xs.at(i) <<" , "<< xs.at(i+1) << " ] " <<res.str() << endl ; 
		res.clear();
	}
	
	cout << endl << endl ;
	return result ; 
}
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    vector<double> x ;
    vector<double> y ;
    
    
    
   /* KPlotWidget * pWid = new KPlotWidget( NULL ) ;
    pWid->setLimits( -0.1, 10, -1.1, 1.1 );
    KPlotObject *sineobj = new KPlotObject( Qt::red, KPlotObject::Lines, 2 );
    KPlotObject *sineobj2 = new KPlotObject( Qt::red, KPlotObject::Points, 2 );*/
    
    
    
	/*fl::Function2D::FunctionDiscrete::DomainRange range ; */
	x.push_back(0);
	x.push_back(1);
	x.push_back(2);
	x.push_back(3);
	x.push_back(4);
	x.push_back(5);
	x.push_back(6);

	y.push_back(0);
	y.push_back(0.8415);
	y.push_back(0.9093);
	y.push_back(0.1411);
	y.push_back(-0.7568);
	y.push_back(-0.9589);
	y.push_back(-0.2794);
    /*for ( float t=0.0; t<=10; t+=1 ) {
        x.push_back(t);
        y.push_back(sin(t));
        sineobj->addPoint( t, sin(t) );
		range.push_back(make_pair(t,sin(t)));
    }*/

	list<string> l = splineInterpolation(x,y,x.size()-1,-1);
    
    /*fl::Function2D::PolymonialApproximation pA ( 4,range)  ; 
	fl::Function2D::FunctionContinous *pFunc = pA.approximate() ; 
    
    bool bOk ; 
    for ( float t=0.0; t<=10; t+=0.04 ) {
        sineobj2->addPoint(t,pFunc->eval(t,&bOk));
    }
    
    pWid->addPlotObject( sineobj );
    pWid->addPlotObject( sineobj2 );
    pWid->show();
    pWid->axis( KPlotWidget::BottomAxis )->setLabel( ("Angle in radians") );
    pWid->update();
    
     
    app.exec();*/
}
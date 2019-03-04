#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

struct comp
{
    double real  ;
    double img  ;
    double theta ;
    double mag ;
};

comp create_comp(double x, double y) ;
comp** get_w(int n) ;
comp euler(double theta) ;
comp* Multi(double* xn, comp** w, int n) ;
comp mul(double x, comp w) ;

int main(){
    int n ;
    cout<<"Type number of samples of X(n): ";
    cin>>n;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "Incorrect entry. Try again: "<<endl;
        cin>>n;
    }
    //creating and assigning values to twiddle matrix
    comp** tw = new comp*[n];

    for(int i = 0; i < n; i++)
        tw[i] = new comp[n];

    tw = get_w(n) ;
    double *xn= new double[n];
    double userinput;
    for (int i=0; i<n; i++)
    {
        cout<<"X("<<i<<") :";
        cin>>userinput;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Incorrect entry. Try again: "<<endl;
            cin>>userinput;
        }
        xn[i]=userinput;
        //double *xn= new double[n];
    }
     comp* Xk = new comp[n];
     Xk=Multi(xn,(comp **)tw,n);

     cout<< "Magnitudes:"<<endl ;
     for (int RA =0; RA<n; RA++){
        cout<<"Magnitude of Xk["<<RA<<"] is:   "<<Xk[RA].mag<<endl;
     }
     cout<<"Phases:"<<endl;
     for (int RA =0; RA<n; RA++){
        cout<<"Phase of Xk["<<RA<<"] is:   "<<Xk[RA].theta<<endl;
     }


     return 0;
}

//Basic operations on complex variables
comp mul(double x, comp w)
{

    double a = x * w.real ;
    double b = x * w.img ;
    comp z = create_comp(a,b) ;
    return z ;

}

comp add(comp x, comp y)
{

    double a = x.real + y.real ;
    double b = x.img + y.img ;
    comp z = create_comp(a,b) ;
    return z ;

}

//Multiply each row of W with Xn's column
comp* Multi(double* xn, comp** w, int n)
{
    comp* Xn = new comp[n];

    for (int t=0; t<n; t++)
    {
        Xn[t] = create_comp(0,0) ;
        for (int k=0; k<n; k++)
        {

            Xn[t] =  add(Xn[t], mul(xn[k], w[t][k])) ;
        }
        cout<<"X("<<t<<")= "<<"( "<<Xn[t].real<<"  ,J "<<Xn[t].img<<")"<<endl;

    }
    return Xn;
}

//Create a complex variable, deduce its phase and magnitude.
comp create_comp(double x, double y)
{
    comp z ;
    z.real = x;
    z.img = y ;
    double t  = atan( abs(z.img) / abs(z.real)) * 180.0 * 7.0 / 22.0 ;

    if (x >= 0 && y >= 0 ) {z.theta = t ;}
    else if (x < 0  && y > 0 ) {z.theta = 180 - t ;}
    else if (x < 0  && y < 0 ) {z.theta = 180 + t ;}
    else  {z.theta = 360 - t ;}

        //z.theta = t ;
    z.mag = sqrt(pow(x, 2) + pow(y, 2)) ;
    return z ;
}

//Deduce Twiddle Matrix with Euler.
comp** get_w(int n)
{

    comp** w = new comp*[n];


    for(int i = 0; i < n; i++)
        w[i] = new comp[n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            w[i][j] = euler(2.0 * (double)i * (double)j / (double)n) ;

            cout<<"("<< w[i][j].real<<'\t'<<w[i][j].img<<"j"<<")"<<'\t' ;
        }
        cout<< endl ;
    }

    return w ;
}

//calculate each W (complex value) in Twiddle Matrix using theta
 euler(double theta)
{
    comp z ;
    theta = theta * 22.0 / 7.0;
    double x = cos(theta)  ;
    double y = -1.0 * sin(theta)  ;
    z = create_comp(x,y) ;

    return z ;
}

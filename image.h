#ifndef _image_h
#define _image_h  //r* argv,std::vector<int>& j,int& w, int& h,int &t);
#include <string>  
//argv,std::vector<int>& j,int &w, int &h,int &t,int &decm);
#include <iostream>
#include <fstream> //ordata(int argc,char*argv[]);
#include <vector>
#include <string>//can use?
#include <sstream>
#include <cstdlib>
#include <math.h>
#include "image.h"

class MM{
public:
    
    MM()
    : width1(0), height1(0),   avgPix(0) {};
    
    
    
    void pixel(std::vector<int> &s);
    //int checkpixv(std::vector<int>& j,const int &decm,const int &t);

    int checkpixv(std::vector<double>& j,const int &decm,const int &t);
    
    int avgmfun(std::vector<double> & res ,int &w2,int &h2);
   // bool isComment(const std::string& s);
    //why std::?
    //int readPixels(std::ifstream& istr,const int &p,std::vector<int>& j,int decm);

    int readPixels(std::ifstream& istr,const int &p,std::vector<double>& j,int decm);
    
    ///here double
    //int rescale(std::vector<double> res,std::vector<int>& scaled,const int &m,const int &mi);

    int rescale(std::vector<double> &res,std::vector<int>& scaled,const double &m,const double &mi);
    //int MM::getminiandmax(std::vector<double> res,int & n,int & m){

    int getminiandmax(std::vector<double> &res,double & n,double & m);
    //int readPixels2(std::ifstream& istr,int p);
    
    int error(char* arg0, std::string message);
    int ifint(int  c0, std::string jin);
    
    //int m1(char* argv,std::vector<int>& j,int& w, int& h,int &t);
    int m1(char* argv,std::vector<double>& j,int &w, int &h,int &t,int &decm);
    int gettwovectordata(int argc,char*argv[]);
    
    
    
private:
    int width1;
    int height1;
    int maxval1;
    //int nPix1;
    double avgPix;
    std::vector<int> mm;//?why std? what is the name?
    
    
};

#endif

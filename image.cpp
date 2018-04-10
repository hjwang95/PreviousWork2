#include <iostream>
#include <fstream>
#include <vector>
#include <string>//can use?
#include <sstream>
#include <math.h>
#include "image.h"
#include "limits.h"
#include "float.h"
//is this global? can we do global? is it good for vector?just equal
/*int hf ;
 int wf;
 int mf;
 int minf;*/


using namespace std;

int MM::error(char* arg0, string message){  return -1;}

int MM::ifint(int  c0, string jin){
    int jl = jin.length();
    // if(jin.at(0)=="-"){}
    for(int m =0; m < jl; m++){
        char s =jin.at(0);
        
        if(s=='-'){m=m+1;}
        
        char c1 = jin.at(m);
        
        // is it ok?
        
        if(!('0' <= c1&&c1 <= '9')){
            std::cerr<<  " not number"<<endl;
            
            return -1;
            
        }
        
        
    }
    
    return 0;}

/*bool MM::isComment(const string& s){
    
    for (unsigned int i = 0; i < s.length(); i++) {
        if (s[i] == '#') return true;
        
        if ( ! isspace(s[i]) ) return false;}
    
    return true;
}*/
//int MM::readPixels(ifstream& istr, int p,std::vector<int>& j,int decm){const int tot =p*3;
int MM::readPixels(ifstream& istr,const int &p,std::vector<double>& j,int decm){const int tot =p;
    int ct = 0;
    char byteArray[1];
    if(decm <0 || decm>=256){return -1;}
    
    char checkArray[1];
    
    // istr.read(byteArray, tot);
    //if(istr.fail()) {std::cerr<<  " error ba"<<endl;return -1;}
    
    for(int i = 0 ;i< tot;i++){
        istr.read(byteArray, 1);
        
        if(istr.fail()) {std::cerr<<  "readpixel istr fail"<<endl;return -1;}
        int curPix = static_cast<int>(static_cast<unsigned char>(byteArray[0]));
        if (curPix > 255||curPix<0 || curPix > decm) {return -1;}
        j.push_back(curPix);
        ct++;
        
        
    }
    //check ct
    if(istr.read(checkArray, 1)){std::cerr<<  " header1"<<endl;return -1;}
    //byteArray[tot] = '\0';
    //j.push_back('\0');
    
    
    
    //if(istr.read(checkArray, 1)){return -1;}
    
    //byteArray[tot] = '\0';
    /* for(int i = 0; i < tot; i++){
     int curPix = static_cast<int>(static_cast<unsigned char>(byteArray[i]));
     if (curPix > 255||curPix<0 || curPix > decm) {return -1;}
     j.push_back(curPix);
     }*/
    return 0; }
//int MM::checkpixv(std::vector<int>& j,int decm){
int MM::checkpixv(std::vector<double>& j,const int &decm,const int &t){
    // cout << "t"<<t<< endl;
    int s=j.size();
    for(int i=0;i<s;i++){
        double pix = j.at(i);
        if(t==3){if (pix >decm){std::cerr<<  " pixel out of range"<<endl;return -1;}}
        else{if( pix <0||(pix>=256)||pix >decm){std::cerr<<  " pixel out of range"<<endl;return -1;}}
    }
    return 0;
}

//int MM::rescale(std::vector<int> res,std::vector<int>& scaled,int m,int mi){
int MM::rescale(std::vector<double> &res,std::vector<int>& scaled,const double &m,const double &mi){
   // cout<<  "   e" << m<<" "<<mi<<endl;
    if(m==mi){std::cerr<<  " rescale max = min"<<endl;return -1;}
    int vsize=res.size();
    double mi2 = mi;
    double m2 = m;
    //cout<< res[0]<< endl;
    for ( int i = 0; i < vsize; i++) {
        double e=res[i];
        
        
        double f0=((255*(e-mi2))/(m2-mi2));
        
        //double f1 = static_cast<double>(255)*(e-mi2)/(m2-mi2);
        //cout<< e<< " here"<<endl;
        int f = round(f0);
        scaled.push_back(f);
    }
    //cout<< scaled.at(0)<<endl;
    return 0;
}



int MM::getminiandmax(std::vector<double> &res,double & n,double & m){
    int p = res.size();
    double dimax =FLT_MIN;
    double dimin = FLT_MAX;
    // cout<< "//"<<dimin<<endl;
    for(int i=0;i<p;i++){
        double curP = res[i];
        
        if(curP>=dimax){dimax = curP;}
        if(curP<=dimin){dimin = curP;}
        
        
    }
    n = dimin;m = dimax;
    //cout << "min"<<n<<" "<< m<<endl;
    return 0;
}

int MM::avgmfun(std::vector<double> & res ,int &w2,int &h2){
    double average = 0;
    double sum = 0;
    int ressize = res.size();
    for (int i = 0; i< ressize; i++) {
       
        average = average + res[i];

        
    }
    average =average /w2 / h2  ;
  
    
    for (int i = 0; i< ressize; i++) {
        double temp = res[i];
        res[i] = (temp - average);
       
        sum  = sum + (res[i]  )*(res[i]  );

        
    }
    double mag = sqrt(sum);
    if(  mag== 0){std::cerr<<  " mask all same or mag ==0"<<endl;return -1;}
    //if(sec !=2   && mag == 0){back = 9;}//sec should be 1
    for (int i = 0; i< ressize; i++) {
        //cout << average << "ave// "<<average<<  endl;

        res[i] = res[i] /mag;
        
    }
    //cout
    return 0;
}

//????diff when reading? because double and int?attention
int MM::m1(char* argv,std::vector<double>& j,int &w, int &h,int &t,int &decm){
    string fst="";             // The header
    string L1= "aa";        // Just junk clearing the rest of line 1
    string comment;
    string jin;
    string wln;
    string temp;
    string temp2;
    string tem6;
    string space;
    
    int width;
    int heigh;
    //int max;
    int decmax;
    vector<string> rest1;
    vector<string> cm;
    std::vector<double> v;
    
    
    //variables for P5
    stringstream ss5;
    //int countnumberinheader=0;
    
    ifstream istr(argv);
    
    if (istr.fail())  {std::cerr<<  " fail to read file"<<endl; return -1;}
    
    
    //get fst line
    if(!(getline(istr,fst)) ) {std::cerr<<  " cant get 1st line"<<endl; return -1;}
    ss5 << fst;
    //get rid of "P5"
    ss5 >> temp;
    
    
    //start
    if(  ((fst.substr(0,2)).compare("P2")== 0) ||(fst.substr(0,2)).compare("P5")== 0
       || ((fst.substr(0,3)).compare("P2M")== 0) )
    {
        //tell if p2 or p5
        int d =0;int i = 0;
        if((fst.substr(0,2)).compare("P2")== 0|| (fst.substr(0,2)).compare("P5")== 0){
            
            if (fst.substr(0,2).compare("P2") == 0 ) {d = 2;}
            if (fst.substr(0,2).compare("P5") == 0 ) {d = 0;}
            
            
            L1 = fst.substr(2,fst.length());
        }
        
        
        if( ((fst.substr(0,3)).compare("P2M")== 0) ){
            d = 3;
            L1 = fst.substr(3,fst.length());
            
        }
        
        
        //L1 = fst.substr(2,fst.length());
        int len1 = L1.length();
        for (int m = 0; m<len1; m++) {
            
            if (isspace(L1[m])) {
                i++;
            }
        }
        //if p5 has own line or the rest isspace
        if(i==len1){
            
            string os;string rst; string tem; string tem2; string tem3;string rest9;string L2; string L3;
            
            stringstream ss9;
            
            istr >>L2;
            while(L2.compare(0,1,"#") == 0){
                getline(istr,tem);
                if(!(istr >> L2)){
                    std::cerr<<  " error5"<<endl;
                    return -1;}
                
            }
            if(ifint(0,L2)!=0){return -1;}
            stringstream sss9;
            sss9 << L2;
            sss9 >> width;
            //countnumberinheader=1;
            //cout << "wid"<<width<<endl;
            
            
            //512
            if(! ( istr>> tem2)){ return -1; }
            while(tem2.compare(0,1,"#") == 0){
                getline(istr,tem);
                if(!(istr >> tem2)){
                    std::cerr<<  " error5"<<endl;
                    return -1;}
                
            }
            if(ifint(0,tem2)!=0){return -1;}
            stringstream sss10;
            sss10 << tem2;
            sss10 >> heigh;
            //countnumberinheader=2;
            //cout << "heigh"<<heigh<<endl;
            
            
            
            if(! ( istr>> tem6)){ return -1;}
            while(tem6.compare(0,1,"#") == 0){
                getline(istr,tem);
                if(!(istr >> tem6)){
                    std::cerr<<  " error5"<<endl;
                    return -1;}
                
            }
            if(ifint(0,tem6)!=0){return -1;}
            stringstream sss11;
            sss11 << tem6;
            sss11 >> decmax;
            //countnumberinheader=3;
        }
        
        
        
        //at least one number(width)
        //1.P5 24
        //2.P5 24 7
        //3.P5 24 7 255
        
        
        else {
            if (!isspace(L1[0])){ std::cerr<<  " error50"<<endl;return -1;}
            
            if(!(ss5 >> temp)){ std::cerr<<  " error51"<<endl;return -1;};
            
            
            int w=ifint(0,temp);
            if(w!=0){ std::cerr<<  " error52"<<endl;return -1; }
            stringstream ss;
            ss << temp;
            ss >> width;
            // cout <<width<< endl;
            
            //cout <<"wid2"<<width<< endl;
            //countnumberinheader=1;
            
            //1.P5 24
            if(!(ss5 >> temp)){
                
                //check comment
                string rest2;
                
                if(!(istr >> jin)){std::cerr<<  " error1"<<endl; return -1; }
                
                
                while(jin.compare(0,1,"#") == 0){
                    getline(istr,rest2);
                    if(!(istr >> jin)){std::cerr<<  " error5"<<endl;return -1;}
                }
                int t3 = ifint(0,jin);
                if(t3!=0){std::cerr<<  " error53"<<endl;return -1;}
                stringstream ss3;
                ss3 << jin;
                ss3 >> heigh;
                //cout <<"height"<<heigh<< endl;
                //countnumberinheader=2;
                
                
                
                
                //get to 255
                //check comment
                string rest3;
                
                if(!(istr >> jin)){
                    
                    std::cerr<<  " error1"<<endl;
                    
                    return -1;
                    
                }
                while(jin.compare(0,1,"#") == 0){
                    getline(istr,rest3);
                    if(!(istr >> jin)){
                        std::cerr<<  " error5"<<endl;
                        return -1;}
                    
                }
                
                int t6 = ifint(0,jin);
                if(t6!=0){std::cerr<<  " error53"<<endl;return -1;}
                stringstream ss6;
                ss6 << jin;
                ss6 >> decmax;
                // cout <<"decmac"<<decmax<< endl;
                //countnumberinheader=3;
                //getline(istr,space);
            }
            //2.P5 24 7  or  3.P5 24 7 255
            //?? is it ok to use else here?
            else{
                
                
                int t5 =ifint(0,temp);
                if(t5!=0){std::cerr<<  " error53"<<endl;return -1;}
                stringstream ss7;
                ss7 << temp;
                ss7 >> heigh;
                //cout <<"height"<<heigh<< endl;
                //countnumberinheader=2;
                
                
                //2.
                if(!(ss5 >> temp2)){
                    
                    string rest3;
                    
                    if(!(istr >> jin)){
                        
                        std::cerr<<  " error1"<<endl;
                        
                        return -1;
                        
                    }
                    
                    while(jin.compare(0,1,"#") == 0){
                        getline(istr,rest3);
                        if(!(istr >> jin)){
                            std::cerr<<  " error5"<<endl;
                            return -1;}
                        
                    }
                    
                    int t5 =ifint(0,jin);
                    if(t5!=0){
                        std::cerr<<  " error56"<<endl;return -1;
                    }
                    stringstream ss8;
                    ss8 << jin;
                    ss8 >> decmax;
                    
                    //cout <<"decmax"<<decmax<< endl;
                    //countnumberinheader = 3;
                    
                    
                    
                }
                //same??? is it ok to use else here?
                //3.P5 24 7 255
                else{
                    
                    int t4 =ifint(0,temp2);
                    if(t4!=0){
                        std::cerr<<  " error53"<<endl;return -1;
                    }
                    stringstream ss4;
                    ss4 << temp2;
                    ss4 >> decmax;
                    //cout <<"decmax"<<decmax<< endl;
                    //countnumberinheader = 3;
                    
                    
                }
            }
            
            //
            
        }
        
        
        
        int p = width *heigh;
        w=width;
        h=heigh;
        t = d;
        decm=decmax;
        
        //calculate sth else
        if(d==0 ){
            
            char newa;
            istr.get(newa);
            
            if(newa!='\n'){return -1;}
            //istr.ignore();
            
            int checkbin= readPixels( istr,p,v,decmax);
            if(checkbin==-1){std::cerr<<  " checkbin"<<endl;return -1;}
            
            
            //check the pixels!up in read pix?
            
            //check pixels
            if(checkpixv( v,decmax,d)==-1){std::cerr<<  " checkpix"<<endl;return -1;}
            j=v;
        }
        
        else {
            // attention
            if(d!=2 && d !=3){std::cerr<<  " wrong type"<<endl;return -1;}
            int po;int ct;
            char newline  ;
            
            istr.get(newline);
            // cout << "newline"<<newline<<endl;
            if(newline!='\n'){return -1;}
            while(!(istr.eof())){
                if((!(istr >> po)) ){
                    if(istr.eof()){ break; }
                    else {std::cerr<<  " error18"<<endl;return -1; }
                }
                
                //cout << "p"<<po<<endl;
                ct=ct+1;
                
                
                //put into vector
                v.push_back(po);
            }
            if( d==2){
                if(checkpixv( v,decmax,d)==-1){std::cerr<<  " wrong value of pix"<<endl;return -1;}
            }
            //if(checkpixv( v,decmax)==-1){return -1;}
            if(d==3){
                if(checkpixv( v,decmax,d)==-1){std::cerr<<  " wrong value of pix pgmm"<<endl;return -1;}
                
                
            }
            j=v;
            
            
        }
        
        
        return 0;
    }
    
    else { std::cerr<<  " here"<<endl;return -1;}
    
    
    
}
//all double
int MM::gettwovectordata(int argc,char*argv[]){
    //std::vector<int> dif;
    std::vector<double> fstv; std::vector<double> res; std::vector<int> aftrescal;
    std::vector<double> secv; std::vector<double> secv_f;
    //std::vector<int> oprA;std::vector<int> oprB;std::vector<int> oprC;
    
    int w1;int h1; int t1;int dec1;
    int w2;int h2; int t2;int dec2;
    
    
    int fstfile= m1(argv[1],fstv,w1,h1,t1,dec1);
    int secfile= m1(argv[2],secv,w2,h2,t2,dec2);
    if(fstfile==-1){std::cerr<<  " fstfile wrong"<<endl;return -1;}
    if(secfile==-1){std::cerr<<  " secfiel wrong"<<endl;return -1;}
    
    
    //ofstream fout(argv[3]);
    
   // if(!fout.is_open()){ std::cerr<<  " cant write out"<<endl; return -1;}
    int s1=fstv.size();
    
    
    int p0=w1*h1;
    int p01 = w2*h2;
    //int dimax = 0;
    //int avgm = 0;
    
    
    //cout<<fstv.at(0)<<"size"<<fstv.size()<<"/n"<<"wh"<<w1<<" "<<h1<<endl;
    //check rewrite argv[3] here
    //cout <<t2<<"oooooo"<<endl;
    
    //check status
    if(fstfile==-1){std::cerr<<  " fstfile wrong"<<endl;return -1;}
    if(secfile==-1){std::cerr<<  " secfiel wrong"<<endl;return -1;}
    
    
    
    //cout<< s1<<" "<<p0<<" "<<endl;
    if(!(s1==p0)){std::cerr<<  " wrong number of pixel"<<endl;return -1;}
    
    //attention!!!!!!!!!!!!!!!? || w1==2 || h1==2 || w1==1 || h1==1
    if ( p0==0 || p01== 0 ){std::cerr<<  " width or height is 0 or pic size()=0"<<endl;return -1;}
    
    if ( w2>w1 || h2>h1 ){ std::cerr<<  " w2/h2 bigger than w1/h1"<<endl; return -1;}
    
    if(t2!=3){std::cerr<<  " secfile is not p2m"<<endl;return -1;}
    
    
    
    
    int couter = 0;
    //double?here
    //double ih;double iv;   // int countnumberhere;
    
    vector<vector<double> > A2D;
    vector<double> s;
    //make sure?!
    //?
    s.resize(w1);
    //normal mask
    //int back2 = 0;
    secv_f = secv;
    
    //double masksum = 0;
    //int masksize = secv_f.size();
    // for (int i = 0; i< masksize; i++) {
        
    //    masksum = masksum + secv_f[i];
       
        
    // }

    
    // double maskavg = masksum/w2/h2;
    // double secmasksum = 0;

    // for (int i = 0; i< masksize; i++) {
    //     double temp = secv_f[i];
    //     secv_f[i] = (temp - maskavg);
    //     //sum  = sum + (res[i] - average)*(res[i] - average);
    //     secmasksum  = secmasksum + (secv_f[i]  )*(secv_f[i]  );

        
    // }
    
    // double maskmag = sqrt(secmasksum);
    int determ = avgmfun(secv_f ,w2,h2 );
    if(determ == -1){std::cerr<<  " mask same"<<endl;return -1;}
    //if(maskmag == 0){std::cerr<<  " mask same"<<endl;return -1;}

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    ofstream fout(argv[3]);
    
    if(!fout.is_open()){ std::cerr<<  " cant write out"<<endl; return -1;}
    //for (int i=0; i< secv_f.size(); i++) {cout << secv_f[i]<<endl;}
    for (int i=0; i< h1; i++) {A2D.push_back(s);}
    
    for (int m=0; m<h1; m++){
        for (int i=0; i<w1; i++) {
            //A2D[.at(m).at(i)]=fstv.at(couter);
            A2D[m][i]=fstv[couter];
            couter++;
            
        }
    }
    
    
    
    
    
    vector<vector<double> > newP;
    
    vector<double> insideP;
    insideP.resize(w2*h2);
    newP.push_back(insideP);
        //cout << ( w1-w2+1)*( h1-h2+1)<<endl;


    double q=0;
    vector<double> temptofun;
   
    //vector<double> testc;

   // int newpsize = newP.size();
    //cout << newpsize<<endl;

    
    
    
    
    
    vector<vector<double> > A2D2;
    vector<double> s2;
   
    s2.resize(w1);
    
    
    for (int i=0; i< h1; i++) {A2D2.push_back(s2);}
    A2D2[0][0] = A2D[0][0];
    
    for(int i=1; i<h1;i++){A2D2[i][0] = A2D2[i-1][0]+A2D[i][0];}

    for(int i=1; i<w1;i++){A2D2[0][i] = A2D2[0][i-1]+A2D[0][i];}
    

    
    for (int m=1; m<h1; m++){
        for (int n=1; n<w1; n++) {
            A2D2[m][n] = A2D2[m-1][n] + A2D2[m][n-1] - A2D2[m-1][n-1] + A2D[m][n];
        }
    }
   // for (int m=0; m<h1; m++){for (int n=0; n<w1; n++) {cout << " "<<A2D2[m][n];}cout << endl;}
    



    vector<vector<double> > A2D3;
    vector<double> s3;
    s3.resize(w1);
    
    for (int i=0; i< h1; i++) {A2D3.push_back(s3);}
    A2D3[0][0] = A2D[0][0] * A2D[0][0];
    for(int i=1; i<h1;i++){A2D3[i][0] = A2D3[i-1][0]+A2D[i][0] * A2D[i][0];}

    for(int i=1; i<w1;i++){A2D3[0][i] = A2D3[0][i-1]+A2D[0][i] * A2D[0][i];}

    for (int m=1; m<h1; m++){
        for (int n=1; n<w1; n++) {
            A2D3[m][n] = A2D3[m-1][n] + A2D3[m][n-1] - A2D3[m-1][n-1] + A2D[m][n] * A2D[m][n];
        }
    }
    



    
    
    
    


    int R = 0;int R1 = 0;//int R3 = 0;
    res.resize((h1-h2+1)*(w1-w2+1)); int resc = 0;
    for (int s=0; s<h1-h2+1; s++){
        for (int t=0; t<w1-w2+1; t++) {
            //newP.push_back(insideP);
            //newP[R3] = insideP;
            //R3 ++;
            //cout << "s t "<<s<<t<<endl;
            for (int i = 0; i < h2; i++) {
                
                for(int p =0; p < w2;p++){
  //                  avgmfun(res ,w2,h2);
                   // cout << "s"<<s<<"t"<<t<<"i"<<i<<"p"<<p<<endl;
                    newP[R1][R] =A2D[s+i][t+p];
                    //cout << "A2D"<<A2D[s+i][t+p]<< endl;
                    R = R +1;
                    
                }
                
            }
            R = 0;
            //R1++;
          
                temptofun = newP[R1];
                //int back = 0;
            
            
                double a = 0; double b = 0;

                if( s == 0 && t == 0){ a = A2D2[s+h2-1][t+w2-1];b = A2D3[s+h2-1][t+w2-1];}
                else if( s == 0 && t != 0){ a = A2D2[s+h2-1][t+w2-1] - A2D2[s-1+h2][t-1];
                                            b = A2D3[s+h2-1][t+w2-1] - A2D3[s-1+h2][t-1];}
                else if( s != 0 && t == 0){ a = A2D2[s+h2-1][t+w2-1] - A2D2[s-1][t+w2-1];
                                            b = A2D3[s+h2-1][t+w2-1] - A2D3[s-1][t+w2-1];}
                else{
                    a = A2D2[s+h2-1][t+w2-1] - A2D2[s-1+h2][t-1] - A2D2[s-1][t+w2-1] + A2D2[s-1][t-1];
                    b = A2D3[s+h2-1][t+w2-1] - A2D3[s-1+h2][t-1] - A2D3[s-1][t+w2-1] + A2D3[s-1][t-1];
                }
                
                double newavg = a/w2/h2;
                double mag = sqrt(b-a*a/w2/h2);
              
                

            
            
        
            
                //avgmfun(temptofun ,w2,h2,1,back,mag);
               // if(back == 9 ){ q = 0;res.push_back(q);q=0;}
                if(mag == 0 ){ q = 0;res[resc] = q;resc ++;q=0;}

                else{
                  int newPsize =  temptofun.size();
                  for (int y = 0; y< newPsize; y++) { q = q + secv_f[y]*(temptofun[y]-newavg);}
                  q = q/mag;
                  res[resc] = q;resc ++;
                  //R3++;
                  q = 0;
                }
            
        }
    }
    //cout << "R3 "<<R3<<endl;
    //for(int i=0;i<newP.size();i++){for(int o = 0;o< insideP.size(); o++){cout<<newP[i][o]<< " ";}cout <<' '<<endl;}
    
    //for(){}
    //check +1-1!!
    //check 4 for alg!!!!!
    
   // int r = 0;
    
    

    //cout<<res.size()<<endl;
    //cout << ( w1-w2+1)<<"final h"<<( h1-h2+1)<<endl;
   /* if (testn ==0) {
        for (int i=0; i< 9; i++) {
            cout<<  testc[i]<<endl;
        }
    }*/
    //for(int i=0;i<res.size();i++){  cout<< "# "<< i <<res.at(i)<<" "; }cout<<endl;
   //for(int i=0;i<newP.size();i++){for(int o = 0;o< insideP.size(); o++){cout<<newP[i][o]<< " ";}cout <<' '<<endl;}

    
    
    
    
    
    
    
    //check after fst calculate
    
    //for(int i=0;i<secv.size();i++){  cout<<secv.at(i)<<" "; }cout<<endl;
    ///////////////////////////////////////////////////////////////////////////
    double xmin;double xmax;

    getminiandmax(res,xmin,xmax);
    
    // cout << "////"<<res.size()<< endl;
    
    //cout << xmax<<" "<< xmin<<"po"<<p0<< endl;
    
    int check = rescale(res,aftrescal,xmax,xmin);
    // cout << "////"<<res[1]<< endl;
    
    if(check==-1){std::cerr<<  " check rescale"<<endl;return -1;}
    
    //cout << "////"<<res.size()<< endl;
    
    
    if(t1==2){
        fout << "P2\n"<< w1-w2+1 << " "<< h1-h2+1 << "\n";
        fout << "255"<<"\n";
        
        int h0 = aftrescal.size();
        for ( int i = 0; i < h0; i++) {
            int e=aftrescal[i];
            fout << e <<" ";
            
        }
        
        fout.close();
        
    }
    
    
    else{
        
        fout << "P5"<<endl;
        fout << w1-w2+1 << " "<< h1-h2+1 << endl;
        fout << "255"<<endl;

        
        
        int h = aftrescal.size();
        for ( int i = 0; i < h; i++) {
            int e=aftrescal[i];
            
            unsigned char cur = static_cast<unsigned char>((e));
            
            fout << cur ;
        }
        //cout << aftrescal[0]<< endl;
        fout.close();
        
        
    }
    
    
    
    
    
    
    
    return 0;
}
//for(int i=0;i<res.size();i++){  cout<<res.at(i)<<" "; }cout<<endl;



//x+1 guo y+1 x-1 y-1

//cout<< "s "<<s<<"t "<<t<<endl;

//  if(  (temps >h1-1) || (tempt >w1-1) || temps==0 || tempt==0 )

/*if((s+1 >h1-1) || t==0 )      {a=0;}
 if((s+1 >h1-1)  )                 {b=0;}
 if(( s+1 >h1-1) || (t+1 >w1-1) ) {c=0;}
 if( s==0 || t==0            ){d=0;}
 if(s == 0                    ){e=0;}
 if(s==0  || (t+1 >w1-1) ){f=0;}
 if((t+1 >w1-1)  )                 {g=0;}
 if(t==0) {h=0;}*/
//cout<< "j"<<d<<e<<f<<g<<h<<a<<b<<c<<endl;


/* a=A2D[s+1][t-3];
 b=A2D[s+1][t];
 c=A2D[s+1][t+3];
 d=A2D[s-1][t-3];
 e=A2D[s-1][t];
 f=A2D[s-1][t+3];
 g=A2D[s][t+3];//cout<<"t " <<t<<"g"<<g<<endl;
 h=A2D[s][t-3];*/



/*  ih = a+2*b+c-d-2*e-f;
 ih=ih*ih;
 iv = f+2*g+c-d-2*h-a;
 iv=iv*iv;
 double d =ih + iv;
 int newv = round(sqrt(d));
 //cout<<"ih"<<ih<<" "<<"iv"<<iv<<endl;
 res.push_back(newv);
 //cout << "int"<<newv<< endl;
 
 //a=b=c=d=e=f=g=h=1;
 */


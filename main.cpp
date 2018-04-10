#include <iostream>
#include <fstream>
#include <vector>
#include <string>//can use?
#include <sstream>
#include <cstdlib>
#include <math.h>
#include "image.h"




using namespace std;




int main(int argc, char* argv[]){
    
    MM tm;
    
    
    
    if (argc != 4) { std::cerr<<  " error31"<<endl;return -1;}
    
    string name = argv[1]; string name2 = argv[2]; string name3 = argv[3];
    if(name.compare(name3)==0 || name.compare(name2)==0  )
    {  std::cerr<<  " error33"<<endl;return -1;}
    
    
    int b=tm.gettwovectordata(argc,argv);
    
    if(b==-1){
        std::cerr<<  " error329"<<endl;
        return -1;
    }
    
    
    
    
    
    
    
    // cout << w<<"inmain"<<endl;
    
    
    
    
    return 0;
    
}

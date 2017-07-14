//
//  main.cpp
//  LatMRG
//
//  Created by Erwan Bourceret on 18/04/2017.
//  Copyright © 2017 DIRO. All rights reserved.
//


// select pre compiling options
//----------------------------------------------------------------------------------------

#define PRINT_CONSOLE

//----------------------------------------------------------------------------------------

#include <iostream>
#include <map>
#include <fstream>
#include <iterator>
#include <string>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <num.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "latmrg/IntLattice.h"
#include <NTL/tools.h>
#include <NTL/ctools.h>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include "NTL/vec_ZZ.h"
#include "NTL/vec_ZZ_p.h"
#include <NTL/vec_vec_ZZ.h>
#include <NTL/vec_vec_ZZ_p.h>
#include <NTL/mat_ZZ.h>
#include <NTL/matrix.h>
#include <NTL/LLL.h>

#include "latmrg/LatTestAll.h"
#include "latmrg/MRGLattice.h"
#include "latmrg/LatTestAll.h"


#include "latticetester/Types.h"
#include "latticetester/Util.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/progress.hpp>



//#include "SimpleMRG.h"

using namespace std;
using namespace NTL;
using namespace LatticeTester;



int main (int argc, char *argv[])
{
   struct stat buf;    // properties of a file or directory
   LatMRG::LatTestAll testall;
   int status = 0;

   stat("latZZDD_test1", &buf);
   if (0 != S_ISDIR(buf.st_mode))         // directory
      status |= testall.doTestDir ("latZZDD_test1");
   else {
      string dataname("latZZDD_test1");
      dataname.append(".dat");
      stat(dataname.c_str(), &buf);

      status |= testall.doTest ("/Users/Erwan1/projects/github/LatMRG/latZZDD_test3");
   }
   return 0;
}


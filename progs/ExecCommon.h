#ifndef LATMRG_EXECCOMMON_H
#define LATMRG_EXECCOMMON_H

/**
 * This file contains functions, classes and code used in SeekRe. This file is
 * used to remove some of the clutter in SeekRe.cc. This is because some of the
 * functions needed already exist but need to be rewritten.
 * */
#include <ctime>
#include <cstdlib>
#include <list>

#include "latticetester/NormaBestLat.h"
#include "latticetester/Random.h"
#include "latticetester/Const.h"
#include "latticetester/Reducer.h"

#include "latmrg/MWCLattice.h"
#include "latmrg/MMRGLattice.h"
#include "latmrg/ComboLattice.h"
#include "latmrg/Chrono.h"
#include "latmrg/ParamReaderExt.h"
#include "latmrg/Projections.h"
#include "latmrg/FigureOfMerit.h"
#include "latmrg/Const.h"
#include "latmrg/Projections.h"
#include "latmrg/LCGCarryLattice.h"

typedef NTL::ZZ Int;
typedef double Dbl;
typedef NTL::vector<Int> IntVec;
typedef NTL::matrix<Int> IntMat;
typedef NTL::vector<Dbl> DblVec;

#define LATMRG_USE_CONFIG
#define LATMRG_USE_TEST
#include "latmrg/Test.h"

using LatticeTester::IntLattice;
using LatticeTester::Normalizer;

// Variable definitions for executables only
const std::string delim = "\n========================================"
"========================================\n\n";
#ifdef MRGLATTICE_MAIN_EXEC
// These are all the variables the main program might read from configuration files.
// We initialize them all to a default value except a few
LatMRG::GenType gen_type = LatMRG::MRG;
LatticeTester::CriterionType crit_type = LatticeTester::SPECTRAL;
bool dual = true;
LatticeTester::PreReductionType red_type = LatticeTester::FULL;
LatticeTester::NormaType norma_type = LatticeTester::NONE;
double time_limit = 3600.0;
int max_gen = 10;
int detail = 1;
bool period = false;

// Values without default
LatMRG::Projections* proj;
bool proj_set = false;
// insert all possible generator variables.
// m is the modulus. m = p^e+r
Int m, r, p;
int e;
// order of the recurrence
int k;
// Stores the a_j or the info to build them
IntVec coeff;
bool gen_set = false;

// This function resets all the above variables to their default value.
void reset_defaults() {
  gen_type = LatMRG::MRG;
  crit_type = LatticeTester::SPECTRAL;
  dual = true;
  red_type = LatticeTester::FULL;
  norma_type = LatticeTester::NONE;
  time_limit = 3600.0;
  max_gen = 50;
  detail = 1;
  period = false;

  // Values without default
  proj_set = false;
  gen_set = false;
}
#endif


#endif

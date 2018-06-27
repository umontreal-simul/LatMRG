#ifndef SEEK_CONFIG_H
#define SEEK_CONFIG_H

#include <string>
#include <vector>

#include "latticetester/Types.h"
#include "latticetester/Const.h"

#include "latmrg/Modulus.h"
#include "latmrg/Const.h"


namespace LatMRG {

  /** This structure contains the information necessary to search an MRG 
   * component to a multiple MRG.
   * */
  struct Component {
    /// Type of the generator. Either MRG or MWC.
    GenType genType;
    /// The modulus m of this component.
    Modulus<MScal> modulus;
    /// The order of the component.
    int k;
    /** `bool` describing if the component has maximal period. It has to be 
     * `true` if the compenent has maximal period, and `false` otherwise.
     * */
    bool PerMax;
    /// \todo this
    ImplemCond implemCond;
    /// \todo this
    int NumBits;
    /// \todo this
    int HighestBit;
    /// \todo this
    int ncoef;
    /// \todo this
    int *Icoef;
    /// \todo this
    DecompType F1;
    /// \todo this
    std::string file1;
    /// \todo this
    DecompType F2;
    /// \todo this
    std::string file2;
    /// \todo this
    SearchMethod searchMethod;
    /// \todo this
    int numReg, H, Hk;
    /// \todo this
    MVect b, c;
    /// \todo this
    bool ApproxTotGen;
  };

  /**
   * \todo Compléter la description de la classe
   *
   * <strong> À EXAMINER:</strong> il pourrrait y avoir des avantages à inclure
   * une variable `LatConfig` à l’intérieur de `SeekConfig`. Plusieurs
   * variables n’auraient pas à être répétées dans `SeekConfig`, et la
   * recherche appelle les tests avec des paramètres de `LatConfig`, parfois
   * explicitement, ce qui cause des problèmes (cas PALPHA). Cela pourrait
   * simplifier le code.
   *
   */
  class SeekConfig {
    public:
      static const int MAX_WORD_SIZE = 64;
      SeekConfig();
      ~SeekConfig();
      void write();
      MScal* getMs() { return Ms; }
      int* getKs()  { return Ks; }
      int getMaxK();
      int getMaxTd();
      bool readGenFile; // read generator from file
      std::string fileName;  // file name
      int J;            // nombre de generateurs dans la combinason
      std::vector<Component> compon;
      MScal* Ms;
      MVect* As;
      int* Ks;
      int C;
      double* minMerit;
      double* maxMerit; // C values
      int* numGen; // C values
      LatticeTester::CriterionType criter;
      LatticeTester::NormaType normaType;

      /**
       * The number of series of projections (see `td` below). The classical case
       * corresponds to \f$d=1\f$, for which the chosen test is done on all
       * successive dimensions from `td[0] = fromDim`, up to and including `td[1] =
       * toDim`.
       */
      // Criterion <Norm>

      int d;

      /**
       * Array containing the maximal dimensions for the projections in each
       * category. `td[1]` is the maximal dimension for successive
       * 1-dimensional projections, `td[2]` is the maximal dimension for
       * 2-dimensional projections, `td[3]` is the maximal dimension for
       * 3-dimensional projections, and so on. However, the value of `td[0]`
       * is the minimal dimension for the case of successive dimensions.
       */
      int *td;
      int getMaxDim() { return td[1]; }
      LatticeType latType;

      /**
       * If this flag is `true`, the test is to be applied on the dual lattice. If
       * it is `false`, the test is to be applied on the primal lattice.
       */
      bool dualF;

      /**
       * This flag applies specificaly to the spectral test by specifying at
       * what speed (and precision) it should be done. If it is set to `0` the
       * test is done normally without approximations. If it is set to `1`, the
       * test is done without Branch-and-Bound using only BKZ pre-reduction. 
       * Finaly, if it is set to `2` the test is done without Branch-and-Bound
       * using only LLL pre-reduction.
       * */
      int speed;

      /**
       * If `invertF` is `true`, the inverse of the length of the shortest
       * vector will be printed in the results. Otherwise, the length itself
       * will be printed.
       */
      bool invertF;

      /**
       * The value of \f$\alpha\f$ for the \f$P_{\alpha}\f$ test.
       */
      int alpha;
      int lacGroupSize;
      int lacSpacing;
      long maxNodesBB;
      double duration;
      long seed;  // seed of the random number generator
      LatticeTester::OutputType outputType;
  };

}
#endif // SEEK_CONFIG_H

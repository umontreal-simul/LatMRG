#ifndef LatticeTester__KOROBOVLATTICE_H
#define LatticeTester__KOROBOVLATTICE_H
#include "latticetester/Const.h"
#include "latticetester/IntLattice.h"


namespace LatMRG {

  /**
   * This class implements lattice bases built from a Korobov lattice rule. For
   * a given \f$a\f$, a Korobov lattice basis is formed as follows:
   * \f[
   * \mathbf{b_1} = (1, a, a^2, …, a^{d-1}),\quad
   * \mathbf{b_2} = (0, n, 0, …, 0),\quad…,\quad
   * \mathbf{b_d} = (0, …, 0, n).
   * \f]
   *
   * \remark **Pierre:** Reprogrammer \c incDim de façon efficace comme dans
   * \c MRGLattice
   *
   */
  template<typename Int>
    class KorobovLattice: public LatticeTester::IntLattice {
      public:

        /**
         * Constructs a Korobov lattice with \f$n\f$ points, maximal dimension
         * `maxDim` using the norm `norm`.
         */
        KorobovLattice (const Int & n, const Int & a, int maxDim,
            LatticeTester::NormType norm = LatticeTester::L2NORM);

        /**
         * Constructor. Same as above, except the lattice is formed as follow:
         * \f[
         * \mathbf{b_1} = (a^t, a^{t+1}, a^{t+2}, …, a^{t+d-1}),\qquad
         * \mathbf{b_2} = (0, n, 0, …, 0),\qquad…,\qquad
         * \mathbf{b_d} = (0, …, 0, n).
         * \f]
         */
        KorobovLattice (const Int & n, const Int & a, int dim, int t,
            LatticeTester::NormType norm = LatticeTester::L2NORM);

        /**
         * Copy constructor.
         */
        KorobovLattice (const KorobovLattice & Lat);

        /**
         * Assigns `Lat` to this object.
         */
        KorobovLattice & operator= (const KorobovLattice & Lat);

        /**
         * Destructor.
         */
        ~KorobovLattice();

        /**
         * Returns the multiplier \f$a\f$ as a string.
         */
        std::string toStringCoef() const;

        /**
         * Builds the basis in dimension \f$d\f$.
         */
        void buildBasis (int d);

        /**
         * Increments the dimension of the basis by 1.
         */
        void incDim();

        /**
         * Increments the dimension of the basis by 1 by rebuilding the basis
         * from scratch. This is very slow. It can be used for verification of
         * the fast `incDim` method above.
         */
        void incDimSlow();
      protected:

        /**
         * The multiplier of the Korobov lattice rule.
         */
        Int m_a;

        /**
         * The shift applied to the lattice rule.
         */
        int m_shift;

        /**
         * Initialization.
         */
        void init();
    }; // End class declaration

  template<typename Int>
    KorobovLattice<Int>::KorobovLattice (const Int & n, const Int & a,
        int maxDim, LatticeTester::NormType norm) :
      LatticeTester::IntLattice::IntLattice(n, 0, maxDim, norm)
  {
    m_a = a;
    m_shift = 0;
    init();
  }


  //===========================================================================

  template<typename Int>
    KorobovLattice<Int>::KorobovLattice (const Int & n, const Int & a,
        int maxDim, int t, LatticeTester::NormType norm) :
      IntLattice::IntLattice(n, 0, maxDim, norm)
  {
    m_a = a;
    m_shift = t;
    init();
  }


  //===========================================================================

  template<typename Int>
    KorobovLattice<Int>::~KorobovLattice()
    {
    }


  //=========================================================================

  template<typename Int>
    KorobovLattice<Int>::KorobovLattice (const KorobovLattice & lat):
      IntLattice::IntLattice(lat.m_modulo, 0, lat.getDim (), lat.getNorm ())
  {
    m_a = lat.m_a;
    m_shift = lat.m_shift;
  }


  //=========================================================================

  template<typename Int>
    KorobovLattice<Int> & KorobovLattice<Int>::operator= 
    (const KorobovLattice & lat)
    {
      if (this == &lat)
        return *this;
      m_dim = lat.m_dim;
      copyBasis(lat);
      m_order = lat.m_order;
      m_a = lat.m_a;
      m_shift = lat.m_shift;
      return *this;
    }


  //===========================================================================

  template<typename Int>
    void KorobovLattice<Int>::init()
    {
      //Erwan   IntLatticeBasis::init();
      //   double temp;
      //   conv (temp, m_m);
      //   m_lgVolDual2[1] = 2.0 * Lg(temp);

      //Erwan   for (int r = m_order + 1; r <= getMaxDim(); r++)
      //Erwan      m_lgVolDual2[r] = m_lgVolDual2[r - 1];
    }


  //===========================================================================

  template<typename Int>
    std::string KorobovLattice<Int>::toStringCoef () const
    {
      std::ostringstream out;
      out << m_a;
      return out.str ();
    }


  //===========================================================================

  template<typename Int>
    void KorobovLattice<Int>::buildBasis(int d)
    {
      //assert(d <= getMaxDim());
      setDim(d);
      Int tmp;
      conv(tmp, 1);

      for (int i = 0; i < m_shift; i++) {
        tmp *= m_a;
        tmp %= m_modulo;
      }

      for (int j = 1; j <= d; j++) {
        // V[1][j] = tmp % m;
        m_basis (0, j) = tmp;
        tmp *= m_a;
        tmp %= m_modulo;
      }

      for (int i = 2; i <= d; i++) {
        for (int j = 1; j <= d; j++) {
          if (i == j)
            m_basis (i, j) = m_modulo;
          else
            m_basis (i, j) = 0;
        }
      }

      // Build dual basis
      LatticeTester::CalcDual<BMat>(m_basis, m_dualbasis, d, m_modulo);
    }


  //===========================================================================

  template<typename Int>
    void KorobovLattice<Int>::incDimSlow()
    {
      // Temporaire: très lent. Reprogrammer.
      int d = getDim();
      buildBasis(d + 1);
      setNegativeNorm();
      setDualNegativeNorm();
    }


  //===========================================================================

  template<typename Int>
    void KorobovLattice<Int>::incDim()
    {
      Int tmp1, tmp2, tmp3; MVect vectmp1;// working variables
      IntLattice::incDim(); //Increment the dimenson of the lattice by 1
      const int dim = getDim(); //New dimension

      vectmp1.resize(dim);
      for (int i = 1; i < dim-1; i++) {
        conv (tmp2, m_basis (i, dim - 2));
        tmp1 = tmp2 * m_a;
        LatticeTester::Modulo (tmp1, m_modulo, tmp1);
        m_basis (i, dim) = vectmp1(i) =  tmp1; //Erwan m_vSI (0, i) = tmp1;
      }

      matrix_row<BMat> row1(m_basis, dim - 2);
      LatticeTester::SetZero (row1, dim - 2);

      for (int i = 0; i < dim-1; i++)
        m_basis (dim-1, i) = 0;
      m_basis (dim-1, dim-1) = m_modulo;

      for (int i = 0; i < dim-1; i++)
        m_dualbasis (i, dim-1) = 0;
      m_dualbasis (dim-1, dim-1) = 1;

      for (int j = 1; j < dim; j++) {
        clear (tmp1);
        for (int i = 1; i < dim; i++) {
          tmp2 = m_dualbasis (i, j);
          tmp2 *= vectmp1 (i);
          tmp1 -= tmp2;
        }
        LatticeTester::Quotient (tmp1, m_modulo, tmp3);
        m_dualbasis (dim, j) = tmp3;
      }

      setNegativeNorm();
      setDualNegativeNorm();
    }

} // End namespace LatMRG
#endif

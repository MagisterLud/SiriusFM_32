#include "prog.h"

namespace SiriusFM
{
  template<typename Diffusion1D, typename AProvider, typename BProvider, typename AssetClassA, typename AssetClassB>

  inline void MCEngine1D <Diffusion1D,
  AProvider,
  BProvider,
  AssetClassA,
  AssetClassB>::Simulate(time_t a_t0,
      time_t a_T,
      int a_tau_min,
      Diffusion1D const* a_diff,
      AProvider const* a_rateA,
      BProvider const* a_rateB,
      AssetClassA a_A,
      AssetClassB a_B,
      bool a_isRN)
    {}
};

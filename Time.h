#pragma once
#include"MCEngine1D.hpp"

namespace SiriusFM
{
  inline double YearFree(time_t a_t)
  {
    // Avg year in seconds:

    constexpr double SecY = 365.125*86400.0; //Сколько секунд в году
    return 1970.0 + double(a_t)/SecY;
  }
}

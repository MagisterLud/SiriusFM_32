#pragma once
#include"prog.h"
#include"Time.h"
#include<cassert>
#include<random>

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
      double a_s0, //начальная точка
      long a_P, // число путей (половинное)
      Diffusion1D const* a_diff,
      AProvider const* a_rateA,
      BProvider const* a_rateB,
      AssetClassA a_A,
      AssetClassB a_B,
      bool a_isRN)
    {
      // Тут должны быть ассёрты
      assert(a_diff!=nullptr &&
         a_rateA = nullptr &&
         a_rateB = nullptr &&
         a_A=AssetClassA::Undefined &&
         a_t0 <= a_T &&
         a_tau_min >= 0);

         double y0 = YearFree(a_t0);
         double yT = YearFree(a_T);
         double tau = double(a_tau_min)/(365.25+1440.0);
         long L = long (ceil(yT-y0)/tau)+1; // Получили длину пути
         long P = 2*a_P; // Для каждого P создаём два пути: брауновский инкремент и минус брауновский инкремент
         if(L*P > m_MaxL*m_MaxP) std::invalid_argument("...");

         std::normal_distribution<> N01(0.0,1.0);
         std::mt19937_64 U;

         double stau = sqrt(tau);
         double tlast = yT - y0 - double(L -2)*tau;
         double slast = sqrt(tlast);

         //Main simulate loop
         for(long P=0; P<a_P; P++)
         {
           double* path0 = m_paths + 2*P*L;
           double* path1 = path0 + 1;
           path0[0] = a_s0;
           path1[0] = a_s0;
           double y=y0;
           double Sp0=a_s0;
           double Sp1=a_s0;
           for(long l=1; l<L; l++)
           {
             double mu0=0.0;
             double mu1=0.0;
             if(a_isRN)
             {
               double delta_r; // Уточнить!!! Откуда delta_r???
               a_rateB->r(a_B, y);
               a_rateA->r(a_A, y);
               mu0 = delta_r + Sp0;
               mu1 = delta_r + Sp1;
             }
             else
             {
               mu0 = a_diff->mu(Sp0, y);
               mu1 = a_diff->mu(Sp1, y);
             }
             double sigma0 = a_diff->sigma(Sp0,y);
             double sigma1 = a_diff->sigma(Sp1, y);

             double Z = N01(U);
             double Sn0, Sn1;
             if(l==L-1)
             {
               Sn0=Sp0+mu0*tlast+sigma0*Z*slast;
               Sn1=Sp1+mu1*tlast-sigma1*Z*slast;
             }
             else
             {
               Sn0=Sp0+mu0*tau+sigma0*Z*stau;
               Sn1=Sp1+mu1*tau-sigma1*Z*stau;
             }
             path0[l]=Sn0;
             path1[l]=Sn1;
             Sp0=Sn0;
             Sp1=Sn1;
           }
         }

    }
};

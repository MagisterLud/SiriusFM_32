#pragma once
#include<stdio.h>
#include<stdexcept>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#include<ctime>
#include"Time.h"

namespace SiriusFM
{
  class Diffusion_GBM
  {
  private:
    double const m_mu;
    double const m_sigma;
  public:
    double mu(double a_s, double t){return m_mu*a_s;}
    double sigma(double a_s, double t){return (a_s<0) ? 0 : m_sigma*a_s;}
    Diffusion_GBM(double a_mu, double a_sigma)
    :m_mu(a_mu),
    m_sigma(a_sigma)
    {
      if(m_sigma<=0){std::invalid_argument("ERROR!");}
    }

  };

  class Diffusion_CEV
  {
  private:
    double const m_mu;
    double const m_sigma;
    double const m_beta;
  public:
    double mu(double a_s, double t){return m_mu*a_s;}
    double sigma(double a_s, double t){return (a_s<0) ? 0 : m_sigma*pow(a_s, m_beta);}
    Diffusion_CEV(double a_mu, double a_sigma, double a_beta)
    :m_mu(a_mu),
    m_sigma(a_sigma),
    m_beta(a_beta)
    {
      if(m_sigma<=0){std::invalid_argument("ERROR!");}
    }
  };

  class Diffusion_Uhl
  {
  private:
    double const m_kappa;
    double const m_theta;
    double const m_sigma;
  public:
    double mu(double a_s, double t){return m_kappa*(m_theta-a_s);}
    double sigma(double a_s, double t){return (m_sigma<=0) ? 0 : m_sigma;}
    Diffusion_Uhl(double a_kappa, double a_theta, double a_sigma)
    :m_kappa(a_kappa),
    m_theta(a_theta),
    m_sigma(a_sigma)
    {
      if(m_sigma<=0){std::invalid_argument("ERROR!");}
    }
  };

  class Lipton
  {
  private:
    double const m_mu;
    double const m_sigma_0;
    double const m_sigma_1;
    double const m_sigma_2;
  public:
    double mu(double a_s, double t){return m_mu*a_s;}
    double sigma(double a_s, double t){return (a_s<0) ? 0 : (m_sigma_0+m_sigma_1*a_s+m_sigma_2*a_s*a_s);}
    Lipton(double a_mu, double a_sigma_0, double a_sigma_1, double a_sigma_2)
    :m_mu(a_mu),
    m_sigma_0(a_sigma_0),
    m_sigma_1(a_sigma_1),
    m_sigma_2(a_sigma_2)
    {
      if(m_sigma_0<0 || m_sigma_2<0 || m_sigma_1*m_sigma_1-4*m_sigma_0*m_sigma_2>=0){std::invalid_argument("ERROR!");}
    }
  };

  class CIR
  {
  private:
    double const m_kappa;
    double const m_theta;
    double const m_sigma;
  public:
    double mu(double a_s, double t){return m_kappa*(m_theta-a_s);}
    double sigma(double a_s, double t){return (a_s<0) ? 0 : m_sigma*sqrt(a_s);}
    CIR(double a_mu, double a_kappa, double a_theta, double a_sigma)
    :m_kappa(a_kappa),
    m_theta(a_theta),
    m_sigma(a_sigma)
    {
      if(m_sigma<=0){std::invalid_argument("ERROR!");}
    }
  };


enum class CcyE
{
  Undefined=-1,
  USD=0,
  EUR=1,
  GBP=2,
  CHF=3,
  RUB=4,
  N=5
};

inline char const* CcyE2Str(CcyE a_ccy)
{

  switch(a_ccy)
  {
    case CcyE::USD: return "USD";
    case CcyE::RUB: return "RUB";
    default: throw std::invalid_argument("...");
  }
};

inline CcyE Str2CcyE(char const* a_str)
{
  if(strcmp(a_str, "USD")==0) return CcyE::USD;
  else if(strcmp(a_str, "EUR")==0) return CcyE::EUR;
  else if(strcmp(a_str, "GBP")==0) return CcyE::GBP;
  else if(strcmp(a_str, "CHF")==0) return CcyE::CHF;
  else if(strcmp(a_str, "RUB")==0) return CcyE::RUB;
  else
  throw std::invalid_argument("...");
};

enum class IRModeE
{
  Const=0,
  FwdCurve=1,
  Stoch=2
};

template<IRModeE IRM>
class IRProvider;

template<>
class IRProvider<IRModeE::Const>
{
private:
  double m_IRs[(int)(CcyE::N)];
public:
  IRProvider(char const* a_file);
  double r(CcyE a_ccy, double a_t){return m_IRs[(int)(a_ccy)];}

};

template<typename Diffusion1D, typename AProvider, typename BProvider, typename AssetClassA, typename AssetClassB>
class MCEngine1D
{
private:
  long const m_MaxL; //максимальная длина траектории
  long const m_MaxP; //максимальное количество путей
  double* m_paths; //массив путей
  /*
  long m_L; // m_L <= m_MaxL
  long m_P; // m_P <= m_MaxP
  double m_tau; // шаг по времени
  double m_t0; // 2021 чего-то там???

  Diffusion const* m_diff;
  AProvider const* m_rateA;
  BProvider const* m_rateB;
  AssetClassA m_a; // код инструмента B (точнее Asset'а A), например, B=CcyE::RUB В НАШЕМ СЛУЧАЕ AssetClassA будет совпадать с AssetClassB
  AAssetClassB m_b; // код интсрумента A (точнее Asset'а B), например, A=CcyE::USD
  bool m_isRN; // Risk neutral term
  */ //Это вроде не нужно и будет передаваться в методе Simulate

public:
  MCEngine1D(long a_MaxL, long a_MaxP)
  :m_MaxL(a_MaxL),
  m_MaxP(a_MaxP),
  m_paths(new double[m_MaxL*m_MaxP])
  /*
  m_L(0),
  m_P(0),
  m_tau(nan),
  m_diff(nullptr),
  m_rateA(nullptr),
  m_rateB(nullptr),
  m_a(AssetClssA::Undefined),
  m_b(AssetClassB::Undefined),
  */ //Это вроде не нужно и будет передаваться в методе Simulate
  {
    if(m_MaxL <= 0 || m_MaxP <= 0) std::invalid_argument("ERROR!");
  }

  void Simulate(time_t a_t0,
    time_t a_T,
    int a_tau_min,
    double a_s0, //начальная точка
    long a_P, // Число путей
    Diffusion1D const* a_diff,
    AProvider const* a_rateA,
    BProvider const* a_rateB,
    AssetClassA a_A,
    AssetClassB a_B,
    bool a_isRN); // a_T -- время экспирации, a a_t0 -- текущее время

    ~MCEngine1D()
    {
      delete[] m_paths;
    }
};

};

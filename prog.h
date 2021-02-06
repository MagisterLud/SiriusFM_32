#include <stdio.h>
#include <stdexcept>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
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

};

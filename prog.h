#include<stdexcept>
#include<cmath>
namespace SigmaFM
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
}

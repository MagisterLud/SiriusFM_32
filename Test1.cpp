#include"MCEngine1D.hpp"

using namespace SiriusFM;
using namespace std;

int main(int argc, char* argv[])
{
  if(argc!=7)
  {
    return 1;
  }

  double mu = atof(argv[1]);
  double sigma = atof(argv[2]);
  double s0 = atof(argv[3]);
  long T_days = atof(argv[4]);
  int tau_min = atof(argv[5]);
  long P =  atof(argv[6]);
  CcyE ccyA = CcyE::USD;
  IRProvider<IRModeE::Const> irp(nullptr);
  Diffusion_GBM diff(mu, sigma);
  MCEngine1D<decltype(diff),
  decltype(irp),
  decltype(irp), decltype(ccyA), decltype(ccyA)> mce(20'000, 20'000);
  time_t t0=time(NULL);
  time_t T=t0+T_days*86400;
  double Ty = double(T_days)/365.25;

  //Run MC:
  mce.Simulate<false>(t0, T, tau_min, s0, P, &diff, &irp, &irp, ccyA, ccyA);



  //Analyze the relusts:
  auto res = mce.GetPaths();
  long L1 = get<0>(res);
  long P1 = get<1>(res);
  double const* paths=get<2>(res);

  //Compute Expected value of log(s_T):
  double E_sT=0.0;
  double E_sT2=0.0;
  int NVP=0; // NVP -- это количество путей

  for(int P=0; P<P1; P++)
  {
    double const* path = paths + P*L1;
    double sT=path[L1-1];
    //Защита от sT<=0, чтобы взять логарифм
    if(sT<= 0.0) continue;
    NVP++;
    double RT = log(sT/s0);
    E_sT += RT;
    E_sT2 += RT*RT;
  }
  assert(NVP>1);
  E_sT /= double (NVP); // (mu-sigma^2/2)T

  //Находим дисперсию
  double Var_sT = (E_sT2 - double(NVP)*E_sT*E_sT)/double(NVP-1);
  double sigma2E = Var_sT/Ty;
  double muE = (E_sT + Var_sT/2.0)/Ty;

  cout << "mu= " << mu << ", muE= " << muE << endl;
  cout << "sigma2= " << sigma*sigma << ", sigma2E= " << sigma2E << endl;


  //cout << L1 << endl;

  //==============================================================================
  // Graphics 2D
  /*
  FILE *f;

  f = fopen("data.txt", "w");

  for(int i=0; i<L1; i++)
  {
    fprintf(f, "%lf ", double(tau_min*i));
    fprintf(f, "%lf\n", paths[i]);
  }
  */


  //==============================================================================
  // Graphics 3D

  /*
  FILE *f;

  f = fopen("3D.txt", "w");

  for(int i=0; i<L1; i++)
  {
    for(int j=0; j<L1; j++)
    {
      fprintf(f, "%lf ", double(tau_min*i));
      fprintf(f, "%lf ", double(tau_min*j));
      fprintf(f, "%lf\n", paths[i]+paths[L1+j]);
    }

  }
  */





  return 0;
}

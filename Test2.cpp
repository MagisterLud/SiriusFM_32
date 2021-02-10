#include"MCEngine1D.hpp"

using namespace SiriusFM;
using namespace std;

int main(int argc, char* argv[])
{
  if(argc!=9)
  {
    return 1;
  }

  double mu = atof(argv[1]);
  double sigma = atof(argv[2]);
  double s0 = atof(argv[3]);
  char const* OptType = argv[4];
  double const K = atof(argv[5]);
  long T_days = atof(argv[6]);
  int tau_min = atof(argv[7]);
  long P =  atof(argv[8]);
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


Option const* option;
if(strcmp(OptType, "Call") == 0) option = new EurCallOption(K, T_days);
else if(strcmp(OptType, "Put") == 0) option = new EurPutOption(K, T_days);
else throw invalid_argument("..."); //log(sT/s0) нужно заменить на option->payoff(L, nullptr, path)

double sum=0.;

for(int i=0; i<P1; i++)
{
  double const* path = paths + i*L1;
  sum+=option->payoff(L1, nullptr, path);
}


double prix;
prix = sum/P1;

cout << "Prix d'option = " << prix;


return 0;

}

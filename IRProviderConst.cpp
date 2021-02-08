#include "MCEngine1D.hpp"

using namespace SiriusFM;

IRProvider<IRModeE::Const>::IRProvider(char const* a_file)
{
  char buff[64];
  char forex[4];

  FILE* fp;
  double r;


  fp=fopen(a_file, "r");



  for(int i=0; i < int(CcyE::N); i++)
  {
    fgets(forex, 4, fp);
    fgets(buff, 64, fp);
    r=atof(buff);
    if(strcmp(forex, "USD")==0) m_IRs[0]=r;
    else if(strcmp(forex, "EUR")==0) m_IRs[1]=r;
    else if(strcmp(forex, "GBP")==0) m_IRs[2]=r;
    else if(strcmp(forex, "CHF")==0) m_IRs[3]=r;
    else if(strcmp(forex, "RUB")==0) m_IRs[4]=r;
  }




  fclose(fp);

  //std::cout<< r << "\n";
}

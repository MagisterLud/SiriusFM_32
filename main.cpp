#include "MCEngine1D.hpp"

using namespace SiriusFM;

int main(const int argc, const char* argv[])
{
    CcyE c1 = CcyE::USD;
    CcyE c2 = CcyE::EUR;
    CcyE c3 = CcyE::GBP;
    CcyE c4 = CcyE::CHF;
    CcyE c5 = CcyE::RUB;
    //IRMode IRM = IRM::Const;

    IRProvider<IRModeE::Const> irp = IRProvider<IRModeE::Const>(argv[1]);
    printf("USD: %.2f\n", irp.r(c1,0));
    printf("EUR: %.2f\n", irp.r(c2,0));
    printf("GBP: %.2f\n", irp.r(c3,0));
    printf("CHF: %.2f\n", irp.r(c4,0));
    printf("RUB: %.2f\n", irp.r(c5,0));

    return 0;
}

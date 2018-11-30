#define DCA

#include <gtest/gtest.h>
#include "../src/Includes/Models/ABC_H0.hpp"
#include "../src/Includes/Models/HybFMAndTLoc.hpp"

const double delta = 5e-9;

Json BuildJson()
{
    Json tJson = R"(
    {   "NOrb": 1,
        "NKPTS": 100,
        "tParameters": 
            {"00": 
                {"tIntra": 0.0, "tx": -1.120, "ty": -1.120, "tz": 0.0, "tx=y": 0.1560, "tx=-y": 0.156, "tx=z": 0.0, "tx=-z": 0.0, "ty=z": 0.0, "ty=-z": 0.0, "t2x" : 0.23700, "t2y": 0.23700, "t2z": 0.0, "t3": 0.0}
            }
    }
    )"_json;

    return tJson;
}

TEST(HybFMAndTLocTests, Init)
{
    const size_t Nx = 4;
    const size_t Nc = Nx * Nx;

    using h0_t = Models::ABC_H0<Nx, Nx>;
    h0_t h0(BuildJson());

    std::cout << h0.txVec().at(0) << std::endl;
    std::cout << h0.txVec().size() << std::endl;

    Models::HybFMAndTLoc<h0_t>::CalculateHybFMAndTLoc(h0);

    ClusterMatrixCD_t tloc_K;
    tloc_K.load("tloc_K.arma");
    ClusterMatrixCD_t tloc_K_Good(Nc, Nc);
    tloc_K_Good.zeros();

    ClusterMatrixCD_t hybFM_K;
    hybFM_K.load("hybFM_K.arma");
    ClusterMatrixCD_t hybFM_K_Good(Nc, Nc);
    hybFM_K_Good.zeros();

    tloc_K_Good(0, 0) = -2.924106203;
    hybFM_K_Good(0, 0) = 0.0001084068439;

    tloc_K_Good(1, 1) = tloc_K_Good(4, 4) = tloc_K_Good(3, 3) = tloc_K_Good(12, 12) = -2.016708548;
    hybFM_K_Good(1, 1) = hybFM_K_Good(4, 4) = hybFM_K_Good(3, 3) = hybFM_K_Good(12, 12) = 0.5362070678;

    tloc_K_Good(2, 2) = tloc_K_Good(8, 8) = 0.09772019546;
    hybFM_K_Good(2, 2) = hybFM_K_Good(8, 8) = 0.09633184921;

    tloc_K_Good(5, 5) = -0.6035155442;
    hybFM_K_Good(5, 5) = 1.878710931;

    tloc_K_Good(6, 6) = tloc_K_Good(9, 9) = 2.016708548;
    hybFM_K_Good(6, 6) = hybFM_K_Good(9, 9) = 1.565671109;

    tloc_K_Good(7, 7) = tloc_K_Good(13, 13) = -0.6035155442;
    hybFM_K_Good(7, 7) = hybFM_K_Good(13, 13) = 1.878710931;

    tloc_K_Good(10, 10) = 5.142727989;
    hybFM_K_Good(10, 10) = 0.3078137336;

    tloc_K_Good(11, 11) = tloc_K_Good(14, 14) = 2.016708548;
    hybFM_K_Good(11, 11) = hybFM_K_Good(14, 14) = 1.565671109;

    tloc_K_Good(15, 15) = -0.6035155442;
    hybFM_K_Good(15, 15) = 1.878710931;

    tloc_K_Good.print();
    std::cout << "\n\n\n";
    tloc_K.print();

    for (size_t ii = 0; ii < Nc; ii++)
    {
        for (size_t jj = 0; jj < Nc; jj++)
        {
            std::cout << "ii, jj = " << ii << ", " << jj << std::endl;
            if (ii == jj)
            {
                ASSERT_NEAR(tloc_K_Good(ii, jj).real(), tloc_K(ii, jj).real(), delta);
                ASSERT_NEAR(0.0, tloc_K(ii, jj).imag(), delta);

                ASSERT_NEAR(hybFM_K_Good(ii, jj).real(), hybFM_K(ii, jj).real(), delta);
                ASSERT_NEAR(0.0, hybFM_K(ii, jj).imag(), delta);
            }
            else
            {

                ASSERT_NEAR(0.0, tloc_K(ii, jj).real(), delta);
                ASSERT_NEAR(0.0, tloc_K(ii, jj).imag(), delta);

                ASSERT_NEAR(0.0, hybFM_K(ii, jj).real(), delta);
                ASSERT_NEAR(0.0, hybFM_K(ii, jj).imag(), delta);
            }
        }
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

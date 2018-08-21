

#include <gtest/gtest.h>
#include "../src/Includes/Models/UTensor.hpp"

const double DELTA = 1e-11;

TEST(Vertices2DTest, AuxHelper)
{
    Diagrammatic::AuxHelper auxHelper(delta);

    ASSERT_NEAR(auxHelper.delta(), delta, DELTA_SMALL);

    ASSERT_NEAR(auxHelper.auxValue(FermionSpin_t::Up, AuxSpin_t::Up), 1.0 + delta, DELTA_SMALL);
    ASSERT_NEAR(auxHelper.auxValue(FermionSpin_t::Down, AuxSpin_t::Down), 1.0 + delta, DELTA_SMALL);
    ASSERT_NEAR(auxHelper.auxValue(FermionSpin_t::Up, AuxSpin_t::Down), -delta, DELTA_SMALL);
    ASSERT_NEAR(auxHelper.auxValue(FermionSpin_t::Down, AuxSpin_t::Up), -delta, DELTA_SMALL);

    ASSERT_NEAR(auxHelper.FAux(FermionSpin_t::Up, AuxSpin_t::Up), (1.0 + delta) / delta, DELTA_SMALL);
    ASSERT_NEAR(auxHelper.FAux(FermionSpin_t::Down, AuxSpin_t::Down), (1.0 + delta) / delta, DELTA_SMALL);
    ASSERT_NEAR(auxHelper.FAux(FermionSpin_t::Up, AuxSpin_t::Down), (delta) / (1.0 + delta), DELTA_SMALL);
    ASSERT_NEAR(auxHelper.FAux(FermionSpin_t::Down, AuxSpin_t::Up), (delta) / (1.0 + delta), DELTA_SMALL);

    ASSERT_NEAR(auxHelper.gamma(FermionSpin_t::Up, AuxSpin_t::Up, AuxSpin_t::Up), 0.0, DELTA_SMALL);
    ASSERT_NEAR(auxHelper.gamma(FermionSpin_t::Up, AuxSpin_t::Down, AuxSpin_t::Down), 0.0, DELTA_SMALL);

    ASSERT_NEAR(auxHelper.gamma(FermionSpin_t::Up, AuxSpin_t::Up, AuxSpin_t::Down), (auxHelper.FAux(FermionSpin_t::Up, AuxSpin_t::Up) - auxHelper.FAux(FermionSpin_t::Up, AuxSpin_t::Down)) / (auxHelper.FAux(FermionSpin_t::Up, AuxSpin_t::Down)), DELTA_SMALL);
    ASSERT_NEAR(auxHelper.gamma(FermionSpin_t::Up, AuxSpin_t::Down, AuxSpin_t::Up), (auxHelper.FAux(FermionSpin_t::Up, AuxSpin_t::Down) - auxHelper.FAux(FermionSpin_t::Up, AuxSpin_t::Up)) / (auxHelper.FAux(FermionSpin_t::Up, AuxSpin_t::Up)), DELTA_SMALL);
}

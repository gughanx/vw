#include "../Vector.hpp"

#include <gtest/gtest.h>

TEST(VectorTests, Constructor)
{
    EXPECT_NO_THROW({ vw::Math::Vector3d(); });
    EXPECT_NO_THROW({ vw::Math::Vector3d(1, 2, 3); });

    auto v = vw::Math::Vector3d(1, 2, 3);
    std::cout << v << std::endl;
}

TEST(VectorTests, Addition)
{
    auto v1 = vw::Math::Vector3d(1, 2, 3);
    auto v2 = vw::Math::Vector3d(3, 4, 5);
    auto v = v1 + v2;
    std::cout << v << std::endl;
}

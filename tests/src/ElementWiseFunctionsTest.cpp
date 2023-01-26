#include <gtest/gtest.h>
#include <mpParser.h>
#include <mpValReader.h>
#include <vector>

class FunctionsPackageFixture : public ::testing::Test {

protected:
  virtual void TearDown()
  {
  
  }
  
  virtual void SetUp()
  {
    for (size_t i = 0; i < 5; i++) {
      v1_.push_back((double) i + 1);
      v2_.push_back((double) i * 2);
    }
    
    for (size_t i = 0; i < 10; i++) {
      v3_.push_back((double) i * 5);
      v4_.push_back((double) i * i);
    }
    
    v5_ = {1, -1, 0.5, 0.7, -0.5, -0.7};
    v6_ = {0.5, 0.7, -0.5, -0.7, 0.9};
    
    
    dc1_value = new mup::Value(v1_.size(), 0);
    for (int l = 0; l < v1_.size(); ++l) {
      dc1_value->At(l) = v1_[l];
    }
  
    dc2_value = new mup::Value(v2_.size(), 0);
    for (int l = 0; l < v2_.size(); ++l) {
      dc2_value->At(l) = v2_[l];
    }
  
    dc3_value = new mup::Value(v3_.size(), 0);
    for (int l = 0; l < v3_.size(); ++l) {
      dc3_value->At(l) = v3_[l];
    }
  
    dc4_value = new mup::Value(v4_.size(), 0);
    for (int l = 0; l < v4_.size(); ++l) {
      dc4_value->At(l) = v4_[l];
    }
    
    dc5_value = new mup::Value(v5_.size(), 0);
    for (int l = 0; l < v5_.size(); ++l) {
      dc5_value->At(l) = v5_[l];
    }
  
    dc6_value = new mup::Value(v6_.size(), 0);
    for (int l = 0; l < v6_.size(); ++l) {
      dc6_value->At(l) = v6_[l];
    }
  
    parser.DefineVar("dc1", mup::Variable(dc1_value));
    parser.DefineVar("dc2", mup::Variable(dc2_value));
    parser.DefineVar("dc3", mup::Variable(dc3_value));
    parser.DefineVar("dc4", mup::Variable(dc4_value));
    parser.DefineVar("dc5", mup::Variable(dc5_value));
    parser.DefineVar("dc6", mup::Variable(dc6_value));
  }
  
  std::vector<double> v1_, v2_, v3_, v4_, v5_, v6_;
  
  mup::ParserX parser;
  
  mup::Value *dc1_value, *dc2_value, *dc3_value, *dc4_value, *dc5_value, *dc6_value;
  
  FunctionsPackageFixture() : parser(mup::pck_ELEMENT_WISE) { }
};


TEST_F(FunctionsPackageFixture, MuparserxImportedCorrectly)
{
  //Simple library example to make sure it is imported correctly
  mup::ParserX parserX(mup::pckALL_NON_COMPLEX);
  parserX.SetExpr("1 + 2");
  mup::Value result = parserX.Eval();
  EXPECT_EQ(result.GetInteger(), 3);
}

//TEST_F(FunctionsPackageFixture, BasicVectorOperation)
//{
//  parser.SetExpr("dc1 + dc2");
//  mup::Value result = parser.Eval();
//
//  for (int l = 0; l < result.GetRows(); ++l) {
//    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] + v2_[l], 1E-6);
//  }
//}
//

//
// Unary Functions
//---------------------------------------------------------------------------------------------------------------------
TEST_F(FunctionsPackageFixture, SineOperation)
{
  //Sine(vector)
  parser.SetExpr("sin(dc1)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::sin(v1_[l]), 1E-6);
  }
  
  //Sine(-vector)
  parser.SetExpr("sin(-dc1)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::sin(-v1_[l]), 1E-6);
  }

  //Sine(scalar)
  parser.SetExpr("sin(150)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::sin(150), 1E-4);
}

TEST_F(FunctionsPackageFixture, CosineOperation)
{
  //Cosine
  parser.SetExpr("cos(dc1)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::cos(v1_[l]), 1E-6);
  }

  //Array + scalar
  parser.SetExpr("cos(-dc1)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::cos(-v1_[l]), 1E-6);
  }
  
  //Scalar + scalar
  parser.SetExpr("cos(-150)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::cos(-150), 1E-6);
}

TEST_F(FunctionsPackageFixture, TangentOperation)
{
  //Tangent(vector)
  parser.SetExpr("tan(dc1)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::tan(v1_[l]), 1E-6);
  }
  
  parser.SetExpr("tan(-dc1)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::tan(-v1_[l]), 1E-6);
  }
  
  //Scalar + scalar
  parser.SetExpr("tan(150)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), tan(150), 1E-4);
}

TEST_F(FunctionsPackageFixture, ArcSineOperation)
{
  //ArcSine(vector)
  parser.SetExpr("asin(dc5)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::asin(v5_[l]), 1E-6) << "At(i) = " << result.At(l).GetFloat() << "Compare: " << std::asin(v5_[l]);
  }
  
  //ArcSine(-vector)
  parser.SetExpr("asin(-dc5)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::asin(-(v5_[l])), 1E-6);
  }
  
  //ArcSine(scalar)
  parser.SetExpr("asin(1)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::asin(1), 1E-4);
}

TEST_F(FunctionsPackageFixture, ArcCosineOperation)
{
  //ArcCosine(vector)
  parser.SetExpr("acos(dc5)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::acos(v5_[l]), 1E-6);
  }
  
  //ArcCosine(-vector)
  parser.SetExpr("acos(-dc5)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::acos(-v5_[l]), 1E-6);
  }
  
  //ArcCosine(scalar)
  parser.SetExpr("acos(1)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::acos(1), 1E-4);
}

TEST_F(FunctionsPackageFixture, ArcTangentOperation)
{
  //ArcTangent(vector)
  parser.SetExpr("atan(dc1)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::atan(v1_[l]), 1E-6);
  }
  
  //ArcTangent(-vector)
  parser.SetExpr("atan(-dc1)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::atan(-v1_[l]), 1E-6);
  }
  
  //ArcTangent(scalar)
  parser.SetExpr("atan(150)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::atan(150), 1E-4);
}

TEST_F(FunctionsPackageFixture, HyperbolicSineOperation)
{
  //HyperbolicArcSine(vector)
  parser.SetExpr("sinh(dc1)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::sinh(v1_[l]), 1E-6);
  }
  
  //Sine(-vector)
  parser.SetExpr("sinh(-dc1)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::sinh(-v1_[l]), 1E-6);
  }
  
  //Sine(scalar)
  parser.SetExpr("sinh(150)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::sinh(150), 1E-4);
}

TEST_F(FunctionsPackageFixture, HyperbolicCosineOperation)
{
  //ArcCosine(vector)
  parser.SetExpr("cosh(dc1)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::cosh(v1_[l]), 1E-6);
  }
  
  //HyperbolicArcCosine(-vector)
  parser.SetExpr("cosh(-dc1)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::cosh(-v1_[l]), 1E-6);
  }
  
  //HyperbolicArcCosine(scalar)
  parser.SetExpr("cosh(150)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::cosh(150), 1E-4);
}

TEST_F(FunctionsPackageFixture, HyperbolicTangentOperation)
{
  //HyperbolicArcTangent(vector)
  parser.SetExpr("tanh(dc1)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::tanh(v1_[l]), 1E-6);
  }
  
  //HyperbolicArcTangent(-vector)
  parser.SetExpr("tanh(-dc1)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::tanh(-v1_[l]), 1E-6);
  }
  
  //HyperbolicArcTangent(scalar)
  parser.SetExpr("tanh(150)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::tanh(150), 1E-4);
}

TEST_F(FunctionsPackageFixture, HyperbolicArcSineOperation)
{
  //HyperbolicArcSine(vector)
  parser.SetExpr("asinh(dc1)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::asinh(v1_[l]), 1E-6);
  }
  
  //Sine(-vector)
  parser.SetExpr("asinh(-dc1)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::asinh(-v1_[l]), 1E-6);
  }
  
  //Sine(scalar)
  parser.SetExpr("asinh(150)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::asinh(150), 1E-4);
}

TEST_F(FunctionsPackageFixture, HyperbolicArcCosineOperation)
{
  //ArcCosine(vector)
  parser.SetExpr("acosh(dc1)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::acosh(v1_[l]), 1E-6);
  }
  
//  //HyperbolicArcCosine(-vector)
//  parser.SetExpr("acosh(-dc1)");
//  result = parser.Eval();
//  for (int l = 0; l < result.GetRows(); ++l) {
//    EXPECT_NEAR(result.At(l).GetFloat(), std::acosh(-(v1_[l])), 1E-6);
//  }
  
  //HyperbolicArcCosine(scalar)
  parser.SetExpr("acosh(10)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::acosh(10), 1E-4);
}

TEST_F(FunctionsPackageFixture, HyperbolicArcTangentOperation)
{
  //HyperbolicArcTangent(vector)
  parser.SetExpr("atanh(dc6)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::atanh(v6_[l]), 1E-6);
  }
  
  //HyperbolicArcTangent(-vector)
  parser.SetExpr("atanh(-dc6)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::atanh(-v6_[l]), 1E-6);
  }
  
  //HyperbolicArcTangent(scalar)
  parser.SetExpr("atanh(0.8)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::atanh(0.8), 1E-4);
}

TEST_F(FunctionsPackageFixture, NaturalLogarithmOperation)
{
  //NaturalLogarithm(vector)
  parser.SetExpr("log(dc1)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::log10(v1_[l]), 1E-6);
  }
  
//  //NaturalLogarithm(-vector)
//  parser.SetExpr("log(-dc1)");
//  result = parser.Eval();
//  for (int l = 0; l < result.GetRows(); ++l) {
//    EXPECT_NEAR(result.At(l).GetFloat(), std::log(-v1_[l]), 1E-6);
//  }
  
  //NaturalLogarithm(scalar)
  parser.SetExpr("log(150)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::log10(150), 1E-4);
  
  //NaturalLogarithm(vector)
  parser.SetExpr("ln(dc1)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::log(v1_[l]), 1E-6);
  }
  
  //NaturalLogarithm(-vector)
//  parser.SetExpr("ln(-dc1)");
//  result = parser.Eval();
//  for (int l = 0; l < result.GetRows(); ++l) {
//    EXPECT_NEAR(result.At(l).GetFloat(), std::log(-v1_[l]), 1E-6);
//  }
  
  //NaturalLogarithm(scalar)
  parser.SetExpr("ln(150)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::log(150), 1E-4);
}

TEST_F(FunctionsPackageFixture, SquareRootOperation)
{
  //SquareRoot(vector)
  parser.SetExpr("sqrt(dc1)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::sqrt(v1_[l]), 1E-6);
  }
  
  //SquareRoot(scalar)
  parser.SetExpr("sqrt(150)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::sqrt(150), 1E-4);
}

TEST_F(FunctionsPackageFixture, CubicRootOperation)
{
  //CubicRoot(vector)
  parser.SetExpr("cbrt(dc1)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::cbrt(v1_[l]), 1E-6);
  }
  
  //CubicRoot(-vector)
  parser.SetExpr("cbrt(-dc1)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::cbrt(-v1_[l]), 1E-6);
  }
  
  //CubicRoot(scalar)
  parser.SetExpr("cbrt(150)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::cbrt(150), 1E-4);
}

TEST_F(FunctionsPackageFixture, EPowerOperation)
{
  //E to the power (vector)
  parser.SetExpr("exp(dc1)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::exp(v1_[l]), 1E-6);
  }
  
  //E to the power(-vector)
  parser.SetExpr("exp(-dc1)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::exp(-v1_[l]), 1E-6);
  }
  
  //E to the power(scalar)
  parser.SetExpr("exp(3.9)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), 49.402, 1E-2);
}

TEST_F(FunctionsPackageFixture, AbsoluteValueOperation)
{
  //AbsoluteValue(vector)
  parser.SetExpr("abs(dc1)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::abs(v1_[l]), 1E-6);
  }
  
  //AbsoluteValue(-vector)
  parser.SetExpr("abs(-dc1)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::abs(-v1_[l]), 1E-6);
  }
  
  //AbsoluteValue(scalar)
  parser.SetExpr("abs(150)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::abs(150), 1E-4);
}

//
// Binary Functions
//----------------------------------------------------------------------------------------------------------------------

TEST_F(FunctionsPackageFixture, HypotOperation)
{
  //compute the length of the vector x,y
  //Array + array
  parser.SetExpr("hypot(dc1, dc2)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::hypot(v1_[l],v2_[l]), 1E-6);
  }

  //Array + scalar
  parser.SetExpr("hypot(dc1, 50)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::hypot(v1_[l], 50), 1E-6);
  }

  parser.SetExpr("hypot(-dc1, -50)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::hypot(-v1_[l], -50), 1E-6);
  }

  //Scalar + array
  parser.SetExpr("hypot(50, dc2)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::hypot(50, v2_[l]), 1E-6);

  }

  //Scalar + scalar
  parser.SetExpr("hypot(50, 100)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::hypot(50, 100), 1E-4);

  //Array + array different sizes
  parser.SetExpr("hypot(dc1, dc4)");
  result = parser.Eval();
  EXPECT_EQ(result.GetRows(), v1_.size());
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::hypot(v1_[l], v4_[l]), 1E-6);
  }
}

TEST_F(FunctionsPackageFixture, Atan2Operation)
{
  //Arc tangent with quadrant fix
  //Array + array
  parser.SetExpr("atan2(dc1, dc2)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::atan2(v1_[l], v2_[l]), 1E-6);
  }

  //Array + scalar
  parser.SetExpr("atan2(dc1, 1)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), atan2(v1_[l], 1), 1E-6);
  }

  parser.SetExpr("atan2(-dc1, -1)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::atan2(-v1_[l], -1), 1E-6);
  }

  //Scalar + array
  parser.SetExpr("atan2(1, dc2)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::atan2(1, v2_[l]), 1E-6);
  }

  //Scalar + scalar
  parser.SetExpr("atan2(100, 50)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::atan2(100, 50), 1E-4);

  //Array + array different sizes
  parser.SetExpr("atan2(dc1, dc4)");
  result = parser.Eval();
  EXPECT_EQ(result.GetRows(), v1_.size());
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::atan2(v1_[l], v4_[l]), 1E-6);
  }
}

TEST_F(FunctionsPackageFixture, PowerFunctionOperation)
{
  //Array + array
  parser.SetExpr("pow(dc1, dc2)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::pow(v1_[l], v2_[l]), 1E-6);
  }
  
  //Array + scalar
  parser.SetExpr("pow(dc1, 50)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::pow(v1_[l], 50), 1E-6);
  }
  
  parser.SetExpr("pow(-dc1, -50)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::pow(-v1_[l], -50), 1E-6);
  }
  
  //Scalar + array
  parser.SetExpr("pow(50, dc2)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::pow(50, v2_[l]), 1E-6);
  }
  
  //Scalar + scalar
  parser.SetExpr("pow(50, 100)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::pow(50, 100), 1E-4);
  
  //Array + array different sizes
  parser.SetExpr("pow(dc1, dc4)");
  result = parser.Eval();
  EXPECT_EQ(result.GetRows(), v1_.size());
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::pow(v1_[l], v4_[l]), 1E-6);
  }
}

TEST_F(FunctionsPackageFixture, FmodFunctionOperation)
{
  //Floating point remainder of x / y
  //Array + array
  parser.SetExpr("fmod(dc1, dc5)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_EQ(result.At(l).GetFloat(), std::fmod(v1_[l], v5_[l]));
  }
  
  //Array + scalar
  parser.SetExpr("fmod(dc1, 50)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::fmod(v1_[l], 50), 1E-6);
  }
  
  parser.SetExpr("fmod(-dc1, -50)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::fmod(-v1_[l], -50), 1E-6);
  }
  
  //Scalar + array
  parser.SetExpr("fmod(50, dc5)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::fmod(50, v5_[l]), 1E-6);
  }
  
  //Scalar + scalar
  parser.SetExpr("fmod(50, 100)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::fmod(50, 100), 1E-4);
  
  //Array + array different sizes
  parser.SetExpr("fmod(dc1, dc5)");
  result = parser.Eval();
  EXPECT_EQ(result.GetRows(), v1_.size());
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::fmod(v1_[l], v5_[l]), 1E-6);
  }
}

TEST_F(FunctionsPackageFixture, RemainderFunctionOperation)
{
  //remainder(x, y) - IEEE remainder of x / y
  //Array + array
  parser.SetExpr("remainder(dc1, dc5)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_EQ(result.At(l).GetFloat(), std::remainder(v1_[l], v5_[l]));
  }
  
  //Array + scalar
  parser.SetExpr("remainder(dc1, 50)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::remainder(v1_[l], 50), 1E-6);
  }
  
  parser.SetExpr("remainder(-dc1, -50)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::remainder(-v1_[l], -50), 1E-6);
  }
  
  //Scalar + array
  parser.SetExpr("remainder(50, dc6)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::remainder(50, v6_[l]), 1E-6);
  }
  
  //Scalar + scalar
  parser.SetExpr("remainder(50, 100)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::remainder(50, 100), 1E-4);
  
  //Array + array different sizes
  parser.SetExpr("remainder(dc1, dc5)");
  result = parser.Eval();
  EXPECT_EQ(result.GetRows(), v1_.size());
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::remainder(v1_[l], v5_[l]), 1E-6);
  }
}
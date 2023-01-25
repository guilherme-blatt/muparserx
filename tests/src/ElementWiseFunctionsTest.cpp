#include <gtest/gtest.h>
#include <mpParser.h>
#include <mpValReader.h>
#include <vector>

class MathPackageFixture : public ::testing::Test {

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
  
    parser.DefineVar("dc1", mup::Variable(dc1_value));
    parser.DefineVar("dc2", mup::Variable(dc2_value));
    parser.DefineVar("dc3", mup::Variable(dc3_value));
    parser.DefineVar("dc4", mup::Variable(dc4_value));
    
  }
  
  std::vector<double> v1_, v2_, v3_, v4_;
  
  mup::ParserX parser;
  
  mup::Value *dc1_value, *dc2_value, *dc3_value, *dc4_value;
  
  MathPackageFixture() : parser(mup::pck_ELEMENT_WISE) { }
};


TEST_F(MathPackageFixture, MuparserxImportedCorrectly)
{
  //Simple library example to make sure it is imported correctly
  mup::ParserX parserX(mup::pckALL_NON_COMPLEX);
  parserX.SetExpr("1 + 2");
  mup::Value result = parserX.Eval();
  EXPECT_EQ(result.GetInteger(), 3);
}

//TEST_F(MathPackageFixture, BasicVectorOperation)
//{
//  parser.SetExpr("dc1 + dc2");
//  mup::Value result = parser.Eval();
//
//  for (int l = 0; l < result.GetRows(); ++l) {
//    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] + v2_[l], 1E-6);
//  }
//}
//

TEST_F(MathPackageFixture, SinOperation)
{
  //Array + array
  parser.SetExpr("sin");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::sin(v1_[l]), 1E-6);
  }
  
//  //Array + scalar
//  parser.SetExpr("dc1 + 50");
//  result = parser.Eval();
//  for (int l = 0; l < result.GetRows(); ++l) {
//    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] + 50, 1E-6);
//  }
//
//  parser.SetExpr("dc1 + (-50)");
//  result = parser.Eval();
//  for (int l = 0; l < result.GetRows(); ++l) {
//    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] - 50, 1E-6);
//  }
//
//  //Scalar + array
//  parser.SetExpr("50 + dc2");
//  result = parser.Eval();
//  for (int l = 0; l < result.GetRows(); ++l) {
//    EXPECT_NEAR(result.At(l).GetFloat(), v2_[l] + 50, 1E-6);
//  }
  
  //Scalar + scalar
  parser.SetExpr("sin(150)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::sin(150), 1E-4);
  
//  //Array + array different sizes
//  parser.SetExpr("dc1 + dc4");
//  result = parser.Eval();
//  EXPECT_EQ(result.GetRows(), v1_.size());
//  for (int l = 0; l < result.GetRows(); ++l) {
//    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] + v4_[l], 1E-6);
//  }
}

TEST_F(MathPackageFixture, MinusOperation)
{
  //Array + array
  parser.SetExpr("dc1 - dc2");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] - v2_[l], 1E-6);
  }
  
  //Array + scalar
  parser.SetExpr("dc1 - 50");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] - 50, 1E-6);
  }
  
  parser.SetExpr("(-dc1) - (-50)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), -v1_[l] + 50, 1E-6);
  }
  
  //Scalar + array
  parser.SetExpr("50 - dc2");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), 50 - v2_[l], 1E-6);
  }
  
  //Scalar + scalar
  parser.SetExpr("50 - 100");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), -50, 1E-4);
  EXPECT_EQ(result.GetInteger(), -50);
  
  //Array + array different sizes
  parser.SetExpr("dc1 - dc4");
  result = parser.Eval();
  EXPECT_EQ(result.GetRows(), v1_.size());
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] - v4_[l], 1E-6);
  }
}

TEST_F(MathPackageFixture, MultiplicationOperation)
{
  //Array + array
  parser.SetExpr("dc1 * dc2");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] * v2_[l], 1E-6);
  }
  
  //Array + scalar
  parser.SetExpr("dc1 * 50");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] * 50, 1E-6);
  }
  
  parser.SetExpr("(-dc1) * (-50)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), -v1_[l] * -50, 1E-6);
  }
  
  //Scalar + array
  parser.SetExpr("50 * dc2");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), 50 * v2_[l], 1E-6);
  }
  
  //Scalar + scalar
  parser.SetExpr("50 * 100");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), 50*100, 1E-4);
  EXPECT_EQ(result.GetInteger(), 50*100);
  
  //Array + array different sizes
  parser.SetExpr("dc1 * dc4");
  result = parser.Eval();
  EXPECT_EQ(result.GetRows(), v1_.size());
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] * v4_[l], 1E-6);
  }
}

TEST_F(MathPackageFixture, DivisionOperation)
{
  //Array + array
  parser.SetExpr("dc1 / dc2");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    if(v2_[l] == 0)
      EXPECT_TRUE(std::isnan(result.At(l).GetFloat()));
    else
      EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] / v2_[l], 1E-6);
  }
  
  //Array + scalar
  parser.SetExpr("dc1 / 50");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] / 50, 1E-6);
  }
  
  parser.SetExpr("(-dc1) / (-50)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), -v1_[l] / -50, 1E-6);
  }
  
  //Scalar + array
  parser.SetExpr("50 / dc2");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    if(v2_[l] == 0)
      EXPECT_TRUE(std::isnan(result.At(l).GetFloat()));
    else
      EXPECT_NEAR(result.At(l).GetFloat(), 50 / v2_[l], 1E-6);
    
  }
  
  //Scalar + scalar
  parser.SetExpr("50 / 100");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), 0.5, 1E-4);
  
  //Array + array different sizes
  parser.SetExpr("dc1 / dc4");
  result = parser.Eval();
  EXPECT_EQ(result.GetRows(), v1_.size());
  for (int l = 0; l < result.GetRows(); ++l) {
    if(v4_[l] == 0)
      EXPECT_TRUE(std::isnan(result.At(l).GetFloat()));
    else
      EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] / v4_[l], 1E-6);
  }
}

TEST_F(MathPackageFixture, PowerOperation)
{
  //Array + array
  parser.SetExpr("dc1 ^ dc2");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::pow(v1_[l], v2_[l]), 1E-6);
  }
  
  //Array + scalar
  parser.SetExpr("dc1 ^ 50");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] * 50, 1E-6);
  }
  
  parser.SetExpr("(-dc1) ^ (-50)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::pow(-v1_[l], -50), 1E-6);
  }
  
  //Scalar + array
  parser.SetExpr("50 ^ dc2");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::pow(50, v2_[l]), 1E-6);
  }
  
  //Scalar + scalar
  parser.SetExpr("50 ^ 100");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), std::pow(50, 100), 1E-4);
  EXPECT_EQ(result.GetInteger(), std::pow(50, 100));
  
  //Array + array different sizes
  parser.SetExpr("dc1 ^ dc4");
  result = parser.Eval();
  EXPECT_EQ(result.GetRows(), v1_.size());
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::pow(v1_[l], v4_[l]), 1E-6);
  }
}
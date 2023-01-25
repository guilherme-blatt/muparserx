#include <gtest/gtest.h>
#include <mpParser.h>
#include <mpValReader.h>
#include <vector>
#include <bitset>

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
    
//    b1_ = 0b011011;
//    b2_ = 0b111111;
//    b3_ = 0b100;
//    b4_ = 0b011;
  
    b1_ = {0,1,1,0,1,1};
    b2_ = {1,1,1,1,1,1};
    b3_ = {1,0,0};
    b4_ = {0,1,1};

    bin1_value = new mup::Value(6, 0);
    for (int l = 0; l < 6; ++l) {
      bin1_value->At(l) = b1_[l];
    }
  
    bin2_value = new mup::Value(6, 0);
    for (int l = 0; l < 6; ++l) {
      bin2_value->At(l) = b2_[l];
    }
  
    bin3_value = new mup::Value(3, 0);
    for (int l = 0; l < 3; ++l) {
      bin3_value->At(l) = b3_[l];
    }
  
    bin4_value = new mup::Value(3, 0);
    for (int l = 0; l < 3; ++l) {
      bin4_value->At(l) = b4_[l];
    }
    
    
    parser.DefineVar("dc1", mup::Variable(dc1_value));
    parser.DefineVar("dc2", mup::Variable(dc2_value));
    parser.DefineVar("dc3", mup::Variable(dc3_value));
    parser.DefineVar("dc4", mup::Variable(dc4_value));
  
    parser.DefineVar("bin1", mup::Variable(bin1_value));
    parser.DefineVar("bin2", mup::Variable(bin2_value));
    parser.DefineVar("bin3", mup::Variable(bin3_value));
    parser.DefineVar("bin4", mup::Variable(bin4_value));
    
  }
  
  std::vector<double> v1_, v2_, v3_, v4_;
  
//  std::bitset<6> b1_, b2_;
//  std::bitset<6> b3_, b4_;
  
  std::vector<double> b1_, b2_;
  std::vector<double> b3_, b4_;
  
  mup::ParserX parser;
  
  mup::Value *dc1_value, *dc2_value, *dc3_value, *dc4_value;
  
  mup::Value *bin1_value, *bin2_value, *bin3_value, *bin4_value;
  
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

TEST_F(MathPackageFixture, BasicVectorOperation)
{
  parser.SetExpr("dc1 + dc2");
  mup::Value result = parser.Eval();
  
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] + v2_[l], 1E-6);
  }
}


TEST_F(MathPackageFixture, SumOperation)
{
  //Array + array
  parser.SetExpr("dc1 + dc2");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] + v2_[l], 1E-6);
  }
  
  //Array + scalar
  parser.SetExpr("dc1 + 50");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] + 50, 1E-6);
  }
  
  parser.SetExpr("dc1 + (-50)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] - 50, 1E-6);
  }
  
  //Scalar + array
  parser.SetExpr("50 + dc2");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), v2_[l] + 50, 1E-6);
  }
  
  //Scalar + scalar
  parser.SetExpr("50 + 100");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), 150, 1E-4);
  EXPECT_EQ(result.GetInteger(), 150);
  
  //Array + array different sizes
  parser.SetExpr("dc1 + dc4");
  result = parser.Eval();
  EXPECT_EQ(result.GetRows(), v1_.size());
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), v1_[l] + v4_[l], 1E-6);
  }
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
    EXPECT_NEAR(result.At(l).GetFloat(), std::pow(v1_[l], v2_[l]), 1E-6) << "v1_[l] = " << v1_[l] << " v2_[l] = " << v2_[l];
    
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

TEST_F(MathPackageFixture, OrOperation)
{
  //Array + array
  parser.SetExpr("bin1 || bin2");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_EQ(result.At(l).GetFloat(), (mup::float_type) (b1_[l] || b2_[l]));
  }
  
  //Array + scalar
  parser.SetExpr("bin1 || 0");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_EQ(result.At(l).GetFloat(), (mup::float_type) (b1_[l] || 0));
  }
  
  //Scalar + array
  parser.SetExpr("0 || bin2");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_EQ(result.At(l).GetFloat(), (mup::float_type)(0 || b2_[l]));
  }
  
  //Scalar + scalar
  parser.SetExpr("10 || 100");
  result = parser.Eval();
  //EXPECT_NEAR(result.GetFloat(), 10 || 100, 1E-4);
  EXPECT_EQ(result.GetInteger(), (mup::float_type)(10 || 100));
  
  //Array + array different sizes
  parser.SetExpr("bin1 || bin4");
  result = parser.Eval();
  EXPECT_EQ(result.GetRows(), b1_.size());
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_EQ(result.At(l).GetFloat(),(mup::float_type) (b1_[l] * b4_[l]));
  }
}
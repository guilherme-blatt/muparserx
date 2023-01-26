#include <gtest/gtest.h>
#include <mpParser.h>
#include <mpValReader.h>
#include <vector>

class LogicalOperatorPackageFixture : public ::testing::Test {

protected:
  virtual void TearDown()
  {
  
  }
  
  virtual void SetUp()
  {
    
    v1_ = {0,1,1,0,1,0};
    v2_ = {1,1,1,1,1,1};
    v3_ = {0,1,1};
    v4_ = {1,1,1};
    
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
  
  LogicalOperatorPackageFixture() : parser(mup::pck_ELEMENT_WISE) { }
};

TEST_F(LogicalOperatorPackageFixture, OrOperation)
{
  //Array + array
  parser.SetExpr("dc1 || dc2");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_EQ(result.At(l).GetFloat(), (mup::float_type) (v1_[l] || v2_[l]));
  }

  //Array + scalar
  parser.SetExpr("dc1 || 0");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_EQ(result.At(l).GetFloat(), (mup::float_type) (v1_[l] || 0));
  }

  //Scalar + array
  parser.SetExpr("0 || dc2");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_EQ(result.At(l).GetFloat(), (mup::float_type)(0 || v2_[l]));
  }

  //Scalar + scalar
  parser.SetExpr("10 || 0");
  result = parser.Eval();
  //EXPECT_NEAR(result.GetFloat(), 10 || 100, 1E-4);
  EXPECT_EQ(result.GetInteger(), 1);

  //Array + array different sizes
  parser.SetExpr("dc1 || dc4");
  result = parser.Eval();
  EXPECT_EQ(result.GetRows(), v4_.size());
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_EQ(result.At(l).GetFloat(), (mup::float_type) v1_[l] || v4_[l]);
  }
}

TEST_F(LogicalOperatorPackageFixture, AndOperation)
{
  //Array + array
  parser.SetExpr("dc1 && dc2");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_EQ(result.At(l).GetFloat(), (mup::float_type) (v1_[l] && v2_[l]));
  }

  //Array + scalar
  parser.SetExpr("dc1 && 0");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_EQ(result.At(l).GetFloat(), (mup::float_type) (v1_[l] && 0));
  }

  //Scalar + array
  parser.SetExpr("0 && dc2");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_EQ(result.At(l).GetFloat(), (mup::float_type)(0 && v2_[l]));
  }

  //Scalar + scalar
  parser.SetExpr("10 && 0");
  result = parser.Eval();
  //EXPECT_NEAR(result.GetFloat(), 10 || 100, 1E-4);
  EXPECT_EQ(result.GetInteger(), 0);
  
  //Array + array different sizes
  parser.SetExpr("dc1 && dc4");
  result = parser.Eval();
  EXPECT_EQ(result.GetRows(), v4_.size());
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_EQ(result.At(l).GetFloat(), (mup::float_type) v1_[l] && v4_[l]);
  }
}


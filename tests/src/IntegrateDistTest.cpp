#include <gtest/gtest.h>
#include <mpParser.h>
#include <mpValReader.h>
#include <vector>
#include <motec/MotecDefinition.h>

class IntegrateDistPackageFixture : public ::testing::Test {

protected:
  virtual void TearDown()
  {
  
  }
  
  virtual void SetUp()
  {

    v1_ = {187.95, 188.07, 188.19, 188.32, 188.45, 188.57, 188.68, 188.78, 188.87,
           188.98, 189.08, 189.18, 189.28, 189.40, 189.52, 189.65};
    v2_ = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    v3_ = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//    v3_ = {6586.6, 6591.9, 6597.2, 6608.9, 6620.6, 6615.6, 6610.5, 6612.9, 6615.3,
//           6621.3, 6627.3, 6629.9, 6632.5, 6631.2, 6629.9, 6636.2};
//    v4_ = {0, 1, 2, 1, 3, 4, 5, 6, 7, 5, 6, 7, 0, 10, 0, 11};
    v4_ = {0, 0.52, 1.05, 1.57, 2.09, 2.62, 3.14, 3.67, 4.19, 4.72, 5.24, 5.77, 6.29, 6.82, 7.34, 7.87};
    
    v5_ = {0, 1.88, 3.76, 5.64, 7.52, 9.41, 11.29, 13.18, 15.07, 16.95, 18.84, 20.73, 22.62, 24.52, 26.41, 28.31};
    

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
  
    dc5_value = new mup::Value(v4_.size(), 0);
    for (int l = 0; l < v5_.size(); ++l) {
      dc5_value->At(l) = v5_[l];
    }
    
    parser.DefineVar("speed_channel", mup::Variable(dc1_value));
    parser.DefineVar("dc2", mup::Variable(dc2_value));
    parser.DefineVar("dc3", mup::Variable(dc3_value));
    parser.DefineVar("dc4", mup::Variable(dc4_value));
    parser.DefineVar("dc5", mup::Variable(dc5_value));
  
    mup::motecDefinition::add_motec_functions(&parser, 100);
  }
  
  std::vector<double> v1_, v2_, v3_, v4_, v5_;
  
  mup::ParserX parser;
  
  mup::Value *dc1_value, *dc2_value, *dc3_value, *dc4_value, *dc5_value;
  mup::Value result;
  
  
  IntegrateDistPackageFixture() :parser(mup::pck_ELEMENT_WISE) { }
};


TEST_F(IntegrateDistPackageFixture, MuparserxImportedCorrectly)
{
  //Simple library example to make sure it is imported correctly
  mup::ParserX parserX(mup::pckALL_NON_COMPLEX);
  parserX.SetExpr("1 + 2");
  mup::Value result = parserX.Eval();
  EXPECT_EQ(result.GetInteger(), 3);
}

TEST_F(IntegrateDistPackageFixture, IntegrateDistFunction)
{
  
//  parser.SetExpr("integrate_dist(dc2,dc3,dc2,dc4)");
//  result = parser.Eval();
//  for (int l=0; l < v1_.size(); l++){
//    EXPECT_NEAR(result.At(l).GetFloat(), v4_[l], 1E-1);
//  }
  
  parser.SetExpr("integrate_dist(speed_channel,dc3,dc2,dc4)");
  result = parser.Eval();
  for (int l=0; l < v1_.size(); l++){
    EXPECT_NEAR(result.At(l).GetFloat(), v5_[l], 1E-1);
  }
  
  
}

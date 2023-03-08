#include <gtest/gtest.h>
#include <mpParser.h>
#include <mpValReader.h>
#include <vector>
#include <motec/MotecDefinition.h>

class SmoothPackageFixture : public ::testing::Test {

protected:
  virtual void TearDown()
  {
  
  }
  
  virtual void SetUp()
  {
//    for (size_t i = 0; i < 5; i++) {
//      v1_.push_back((double) i + 1);
//      v2_.push_back((double) i * 2);
//    }
    
//    for (size_t i = 0; i < 10; i++) {
//      v3_.push_back((double) i * 5);
//      v4_.push_back((double) i * i);
//    }
    v1_ = {1,1,1,0,0,1};
    v2_ = {1, 1, 0.66, 0.33, 0.33, 0.5};
    v3_ = {1, 0.75, 0.6, 0.6, 0.5, 0.33};
    v4_ = {0.75, 0.6, 0.66, 0.66, 0.6, 0.5};
//    v5_ = {0.6, 0.66, 0.66, 0.66, 0.66, 0.6};
    v5_ = {1, 1, 0.75, 0.5, 0.25, 0};
    
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
  
    mup::motecDefinition::add_motec_functions(&parser, 100);
  }
  
  std::vector<double> v1_, v2_, v3_, v4_, v5_;
  
  mup::ParserX parser;
  
  mup::Value *dc1_value, *dc2_value, *dc3_value, *dc4_value;
  mup::Value result;
  
  
  SmoothPackageFixture() :parser(mup::pck_ELEMENT_WISE) { }
};


TEST_F(SmoothPackageFixture, MuparserxImportedCorrectly)
{
  //Simple library example to make sure it is imported correctly
  mup::ParserX parserX(mup::pckALL_NON_COMPLEX);
  parserX.SetExpr("1 + 2");
  mup::Value result = parserX.Eval();
  EXPECT_EQ(result.GetInteger(), 3);
}

TEST_F(SmoothPackageFixture, SmoothFunction)
{

  parser.SetExpr("smooth(dc1, 1)");
  result = parser.Eval();
  for (int l = 0; l < v1_.size(); l++) {
    //std::cout << "Resultado: " << result.At(l).GetFloat() << std::endl;
    EXPECT_EQ(result.At(l).GetFloat(), v1_[l]);
  }

//  parser.SetExpr("smooth(dc1, 3)");
//  result = parser.Eval();
//  for (int l = 0; l < v1_.size(); l++) {
//    //std::cout << "Resultado: " << result.At(l).GetFloat() << std::endl;
//    EXPECT_NEAR(result.At(l).GetFloat(), v2_[l], 1E-2);
//  }

//  parser.SetExpr("smooth(dc1, 5)");
//  result = parser.Eval();
//  for (int l = 0; l < v1_.size(); l++) {
//    //std::cout << "Resultado: " << result.At(l).GetFloat() << std::endl;
//    EXPECT_NEAR(result.At(l).GetFloat(), v3_[l], 1E-2);
//  }
//
//  parser.SetExpr("smooth(dc1, 7)");
//  result = parser.Eval();
//  for (int l = 0; l < v1_.size(); l++) {
//    //std::cout << "Resultado: " << result.At(l).GetFloat() << std::endl;
//    EXPECT_NEAR(result.At(l).GetFloat(), v4_[l], 1E-2);
//  }

//  parser.SetExpr("smooth(dc1, 0.04)");
//  result = parser.Eval();
//  for (int l = 0; l < v1_.size(); l++) {
//    //std::cout << "Resultado: " << result.At(l).GetFloat() << std::endl;
//    EXPECT_NEAR(result.At(l).GetFloat(), v5_[l], 1E-2);
//  }
  
}

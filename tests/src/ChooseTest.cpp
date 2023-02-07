#include <gtest/gtest.h>
#include <mpParser.h>
#include <mpValReader.h>
#include <vector>
#include <motec/MotecDefinition.h>

class ChoosePackageFixture : public ::testing::Test {

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
  
    mup::motecDefinition::add_motec_functions(&parser, 100);
  }
  
  std::vector<double> v1_, v2_, v3_, v4_;
  
  mup::ParserX parser;
  
  mup::Value *dc1_value, *dc2_value, *dc3_value, *dc4_value;
  
  ChoosePackageFixture() :parser(mup::pck_ELEMENT_WISE) { }
};


TEST_F(ChoosePackageFixture, MuparserxImportedCorrectly)
{
  //Simple library example to make sure it is imported correctly
  mup::ParserX parserX(mup::pckALL_NON_COMPLEX);
  parserX.SetExpr("1 + 2");
  mup::Value result = parserX.Eval();
  EXPECT_EQ(result.GetInteger(), 3);
}

TEST_F(ChoosePackageFixture, ChooseFunction)
{
    mup::Value result;

  //Arg1 scalar, Arg2 vector, Arg3 scalar
  parser.SetExpr("choose(1 OR 0, dc1, 3)");
  result = parser.Eval();
  for (int l = 0; l < v1_.size(); l++) {
    EXPECT_EQ(result.At(l).GetFloat(), v1_[l]);
  }
 
  //Arg1 scalar, Arg2 vector, Arg3 vector
  parser.SetExpr("choose(1 && 0, dc1, dc2)");
  result = parser.Eval();
  for (int l = 0; l < v2_.size(); l++) {
    EXPECT_EQ(result.At(l).GetFloat(), v2_[l]);
  }

  //Arg1 vector, Arg2 vector, Arg3 vector
  parser.SetExpr("choose(dc1 >= 0, dc2, dc3)");
  result = parser.Eval();
  for (int l = 0; l < v2_.size(); l++) {
    EXPECT_EQ(result.At(l).GetFloat(), v2_[l]);
  }
  
  parser.SetExpr("choose(dc1 >= 0, invalid(), dc3)");
  result = parser.Eval();
  for (int l = 0; l < v2_.size(); l++) {
    EXPECT_TRUE(std::isnan(result.At(l).GetFloat()));
  }
}

#include <gtest/gtest.h>
#include <mpParser.h>
#include <mpValReader.h>
#include <vector>
#include <motec/MotecDefinition.h>

class MotecFunctions1Fixture : public ::testing::Test {

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
  
  MotecFunctions1Fixture() : parser(mup::pck_ELEMENT_WISE) { }
};


TEST_F(MotecFunctions1Fixture, RandomVal)
{
  //Simple library example to make sure it is imported correctly
  mup::ParserX parserX(mup::pck_ELEMENT_WISE);
  
  mup::motecDefinition::add_motec_functions(&parserX, 100);
  
  parserX.SetExpr("rand_val()");
  
  double random_results[5];
  
  for (int i = 0; i < 5; ++i) {
    mup::Value result = parserX.Eval();
    random_results[i] = result.GetFloat();
    EXPECT_LE(random_results[i], 1);
    EXPECT_GE(random_results[i], 0);
  }
  //TEST IF ALL ARRAY VALUES ARE DIFFERENT FROM EACH OTHER
}

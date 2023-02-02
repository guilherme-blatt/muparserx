#include <gtest/gtest.h>
#include <mpParser.h>
#include <mpValReader.h>
#include <vector>
#include <motec/MotecDefinition.h>

class MotecBasicFunctionsFixture : public ::testing::Test {

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
    
    v5_ = {1.2, -1.3, 2.5, 3.7, -4.5, -5.7};
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
    
    inf = new mup::Value(INFINITY);
    nan = new mup::Value(NAN);
  
    parser.DefineVar("dc1", mup::Variable(dc1_value));
    parser.DefineVar("dc2", mup::Variable(dc2_value));
    parser.DefineVar("dc3", mup::Variable(dc3_value));
    parser.DefineVar("dc4", mup::Variable(dc4_value));
    parser.DefineVar("dc5", mup::Variable(dc5_value));
    parser.DefineVar("dc6", mup::Variable(dc6_value));
    parser.DefineVar("inf", mup::Variable(inf));
    parser.DefineVar("nan", mup::Variable(nan));
    
    mup::motecDefinition::add_motec_functions(&parser, 100);
  }
  
  std::vector<double> v1_, v2_, v3_, v4_, v5_, v6_;
  
  mup::ParserX parser;
  
  mup::Value *dc1_value, *dc2_value, *dc3_value, *dc4_value, *dc5_value, *dc6_value, *inf, *nan;
  
  MotecBasicFunctionsFixture() :parser(mup::pck_ELEMENT_WISE) { }
};

TEST_F(MotecBasicFunctionsFixture, MuparserxImportedCorrectly)
{
  //Simple library example to make sure it is imported correctly
  mup::ParserX parserX(mup::pck_ELEMENT_WISE);
  parserX.SetExpr("1 + 2");
  mup::Value result = parserX.Eval();
  EXPECT_EQ(result.GetInteger(), 3);
}

TEST_F(MotecBasicFunctionsFixture, RandomVal)
{
  parser.SetExpr("rand_val()");
  
  double random_results[5];
  
  for (int i = 0; i < 5; ++i) {
    mup::Value result = parser.Eval();
    random_results[i] = result.GetFloat();
    std::cout<<"Result " << i << ": "<< random_results[i] << std::endl;
    EXPECT_LE(random_results[i], 1);
    EXPECT_GE(random_results[i], 0);
  }
  //TEST IF ALL ARRAY VALUES ARE DIFFERENT FROM EACH OTHER
}

TEST_F(MotecBasicFunctionsFixture, Frac)
{
  //Frac(vector)
  parser.SetExpr("frac(dc5)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
      EXPECT_NEAR(result.At(l).GetFloat(), v5_[l] - trunc(v5_[l]), 1E-6);
  }
  
  //Frac(-vector)
  parser.SetExpr("frac(-dc5)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), -(v5_[l]) - trunc(-(v5_[l])), 1E-6);
  }
  
  //Frac(scalar)
  parser.SetExpr("frac(2.6)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), 0.6, 1E-2);
  
  //Frac(-scalar)
  parser.SetExpr("frac(-2.45)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), -0.45, 1E-2);
}

TEST_F(MotecBasicFunctionsFixture, Int)
{
  //Frac(scalar)
  parser.SetExpr("integer(2.6)");
  mup::Value result = parser.Eval();
  std::cout << "Result: " << result << std::endl;
  EXPECT_NEAR(result.GetFloat(), 2, 1E-2);
}

TEST_F(MotecBasicFunctionsFixture, IsFinite)
{
  //IsFinite(vector)
  parser.SetExpr("is_finite(dc5)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_TRUE(result.At(l).GetFloat());
  }
  
  //IsFinite(-vector)
  parser.SetExpr("is_finite(-dc5)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_TRUE(result.At(l).GetFloat());
  }
  
  //IsFinite(infinity)
  parser.SetExpr("is_finite(inf)");
  result = parser.Eval();
  EXPECT_FALSE(result.GetFloat());
  
  //IsFinite(not a number)
  parser.SetExpr("is_finite(nan)");
  result = parser.Eval();
  EXPECT_FALSE(result.GetFloat());
}

TEST_F(MotecBasicFunctionsFixture, sqr)
{
  //sqr(vector)
  parser.SetExpr("sqr(dc5)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), pow(v5_[l], 2), 1E-2);
  }
  
  //sqr(-vector)
  parser.SetExpr("sqr(-dc5)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), pow(-(v5_[l]), 2), 1E-2);
  }
  
  //sqr(scalar)
  parser.SetExpr("sqr(2.3)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), 5.29, 1E-2);
  
  //sqr(-scalar)
  parser.SetExpr("sqr(-5.8)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), 33.64, 1E-2);
}

TEST_F(MotecBasicFunctionsFixture, max)
{
  //max(vector, vector)
  parser.SetExpr("max(dc5, dc6)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::max(v5_[l], v6_[l]), 1E-2);
  }

  //max(-vector, vector)
  parser.SetExpr("max(-dc5, dc6)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::max(-(v5_[l]), v6_[l]), 1E-2);
  }
  
  //max(scalar, scalar)
  parser.SetExpr("max(2.3, 5.29)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), 5.29, 1E-2);
  
  //max(-scalar, -scalar)
  parser.SetExpr("max(-5.8, -3.1)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), -3.1, 1E-2);
}

TEST_F(MotecBasicFunctionsFixture, min)
{
  //min(vector, vector)
  parser.SetExpr("min(dc5, dc6)");
  mup::Value result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::min(v5_[l], v6_[l]), 1E-2);
  }

  //min(-vector, vector)
  parser.SetExpr("min(-dc5, dc6)");
  result = parser.Eval();
  for (int l = 0; l < result.GetRows(); ++l) {
    EXPECT_NEAR(result.At(l).GetFloat(), std::min(-(v5_[l]), v6_[l]), 1E-2);
  }
  
  //min(scalar, scalar)
  parser.SetExpr("min(2.3,5.29)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), 2.3, 1E-2);

  //min(-scalar, -scalar)
  parser.SetExpr("min(-5.8, -3.1)");
  result = parser.Eval();
  EXPECT_NEAR(result.GetFloat(), -5.8, 1E-2);
}

TEST_F(MotecBasicFunctionsFixture, toDouble)
{
  //to_double(scalar, scalar)
  parser.SetExpr("to_double(-1)");
  mup::Value result = parser.Eval();

  std::cout << "Input Type: " << typeid(-1).name() << std::endl;
  std::cout << "Output Type: " << typeid(result.GetFloat()).name() << std::endl;
  std::cout << "Output Value: " << result.GetFloat() << std::endl;
  
  EXPECT_EQ(typeid(result.GetFloat()), typeid((double) -1));
}


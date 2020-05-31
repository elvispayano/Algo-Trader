#include "activation.h"
#include <gtest/gtest.h>

class ActivationTest :
	public ::testing::Test,
	public Activation {
protected:
	void SetUp(void) override {
		in_pos.Resize(1, 1, 10);
		in_neg.Resize(1, 1,-10);
		in_zer.Resize(1, 1,  0);

		out.Resize(1, 1, 0.0);
	}

public:
	dMatrix in_pos;
	dMatrix in_neg;
	dMatrix in_zer;

	dMatrix out;
};

TEST_F(ActivationTest, None) {
	setTF(ActivationTypes::NONE);

	out = perform(in_pos);
	EXPECT_DOUBLE_EQ(out(0, 0), 10);

	out = perform(in_neg);
	EXPECT_DOUBLE_EQ(out(0, 0), -10);

	out = perform(in_zer);
	EXPECT_DOUBLE_EQ(out(0, 0), 0);
};


TEST_F(ActivationTest, Binary) {
	setTF(ActivationTypes::BINARY);

	out = perform(in_pos);
	EXPECT_DOUBLE_EQ(out(0, 0), 1);

	out = perform(in_neg);
	EXPECT_DOUBLE_EQ(out(0, 0), 0);

	out = perform(in_zer);
	EXPECT_DOUBLE_EQ(out(0, 0), 1);
};

TEST_F(ActivationTest, Relu) {
	setTF(ActivationTypes::RELU);

	out = perform(in_pos);
	EXPECT_DOUBLE_EQ(out(0, 0), 10);

	out = perform(in_neg);
	EXPECT_DOUBLE_EQ(out(0, 0), 0);

	out = perform(in_zer);
	EXPECT_DOUBLE_EQ(out(0, 0), 0);
};

TEST_F(ActivationTest, Sigmoid) {
	setTF(ActivationTypes::SIGMOID);

	out = perform(in_pos);
	EXPECT_GT(out(0, 0), 0.999);

	out = perform(in_neg);
	EXPECT_LT(out(0, 0), 0.001);

	out = perform(in_zer);
	EXPECT_DOUBLE_EQ(out(0, 0), 0.5);
};

TEST_F(ActivationTest, TanH) {
	setTF(ActivationTypes::TANH);

	out = perform(in_pos);
	EXPECT_GT(out(0, 0), 0.999);

	out = perform(in_neg);
	EXPECT_LT(out(0, 0),-0.999);

	out = perform(in_zer);
	EXPECT_DOUBLE_EQ(out(0, 0), 0);
};
#include "lern.h"

typedef float threeFloats[3];

typedef struct{
    float or_w1;
    float or_w2;
    float or_b;

    float and_w1;
    float and_w2;
    float and_b;

    float nand_w1;
    float nand_w2;
    float nand_b;
} XOR;

//OR_GATE

threeFloats trainOr[] = {
	{0, 0, 0},
	{1, 0, 1},
	{0, 1, 1},
	{1, 1, 1}
};
#define trainOr_count sizeof(trainOr) / sizeof(trainOr[0])

//AND_GATE

threeFloats trainAnd[] = {
	{0, 0, 0},
	{1, 0, 0},
	{0, 1, 0},
	{1, 1, 1}
};
#define trainAnd_count sizeof(trainAnd) / sizeof(trainAnd[0])

//NAND_GATE

threeFloats trainNand[] = {
	{0, 0, 1},
	{1, 0, 0},
	{0, 1, 0},
	{1, 1, 0}
};
#define trainNand_count sizeof(trainNand) / sizeof(trainNand[0])

//NOR_GATE

threeFloats trainNor[] = {
	{0, 0, 1},
	{1, 0, 0},
	{0, 1, 0},
	{1, 1, 0}
};
#define trainNor_count sizeof(trainNor) / sizeof(trainNor[0])

// XOR_GATE

threeFloats trainXor[] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0}
};

// NOT-XOR_GATE

threeFloats trainNotXor[] = {
    {0, 0, 1},
    {1, 0, 0},
    {0, 1, 0},
    {1, 1, 1}
};

threeFloats *train = trainXor;
#define train_count trainNand_count

float sigmoidf(float x){
	return 1.0 / (1.0 + expf(-x));
}

float rand_float(){
	return (float)rand() / (float)RAND_MAX;
}

float forward_propagation(XOR m, float x, float y)
{
    float or_y_hat = sigmoidf(x * m.or_w1 + y * m.or_w2 + m.or_b);
    float nand_y_hat = sigmoidf(x * m.nand_w1 + y * m.nand_w2 + m.nand_b);
    float y_hat = sigmoidf(or_y_hat * m.and_w1 + nand_y_hat * m.and_w2 + m.and_b);
    return y_hat;
}

float model_cost(XOR m){
	float result = 0.0;
	for (size_t i = 0; i < train_count; i++){
		float x1 = train[i][0];
		float x2 = train[i][1];
		float y_hat = forward_propagation(m, x1, x2);
		float delta = y_hat - train[i][2];
		result += delta * delta;
	}
	result /= train_count;
	return result;
}

XOR randXor ()
{
    XOR m;
    m.or_w1 = rand_float();
    m.or_w2 = rand_float();
    m.or_b = rand_float();
    m.and_w1 = rand_float();
    m.and_w2 = rand_float();
    m.and_b = rand_float();
    m.nand_w1 = rand_float();
    m.nand_w2 = rand_float();
    m.nand_b = rand_float();
    return m;
}

void printXor(XOR m)
{
    printf("OR: w1: %f, w2: %f, b: %f\n", m.or_w1, m.or_w2, m.or_b);
    printf("NAND: w1: %f, w2: %f, b: %f\n", m.nand_w1, m.nand_w2, m.nand_b);
    printf("AND: w1: %f, w2: %f, b: %f\n", m.and_w1, m.and_w2, m.and_b);
}

XOR finiteDiff(XOR m)
{
    XOR g;
    float save_me;
    float cost = model_cost(m);
    float eps = 0.1;

    save_me = m.or_w1;
    m.or_w1 += eps;
    g.or_w1 = (model_cost(m) - cost) / eps;
    m.or_w1 = save_me;

    save_me = m.or_w2;
    m.or_w2 += eps;
    g.or_w2 = (model_cost(m) - cost) / eps;
    m.or_w2 = save_me;

    save_me = m.or_b;
    m.or_b += eps;
    g.or_b = (model_cost(m) - cost) / eps;
    m.or_b = save_me;

    save_me = m.and_w1;
    m.and_w1 += eps;
    g.and_w1 = (model_cost(m) - cost) / eps;
    m.and_w1 = save_me;

    save_me = m.and_w2;
    m.and_w2 += eps;
    g.and_w2 = (model_cost(m) - cost) / eps;
    m.and_w2 = save_me;

    save_me = m.and_b;
    m.and_b += eps;
    g.and_b = (model_cost(m) - cost) / eps;
    m.and_b = save_me;

    save_me = m.nand_w1;
    m.nand_w1 += eps;
    g.nand_w1 = (model_cost(m) - cost) / eps;
    m.nand_w1 = save_me;

    save_me = m.nand_w2;
    m.nand_w2 += eps;
    g.nand_w2 = (model_cost(m) - cost) / eps;
    m.nand_w2 = save_me;

    save_me = m.nand_b;
    m.nand_b += eps;
    g.nand_b = (model_cost(m) - cost) / eps;
    m.nand_b = save_me;
    return g;
}

XOR learn(XOR m, XOR g, float rate){
    m.or_w1 -= rate * g.or_w1;
    m.or_w2 -= rate * g.or_w2;
    m.or_b -= rate * g.or_b;
    m.and_w1 -= rate * g.and_w1;
    m.and_w2 -= rate * g.and_w2;
    m.and_b -= rate * g.and_b;
    m.nand_w1 -= rate * g.nand_w1;
    m.nand_w2 -= rate * g.nand_w2;
    m.nand_b -= rate * g.nand_b;
    return m;
}

int main(){
    srand(time(NULL));
	printf("Mom, I Need More BrainCells!!!\n");
	sleep(1);
	XOR m = randXor();
    XOR g;
    printXor(m);
    printf("----------------\n");
    while (model_cost(m) >= 0.000013){
        g = finiteDiff(m);
        m = learn(m, g, 0.1);
        printf("cost: %f\n", model_cost(m));
    }
    printXor(m);
    printf("cost: %f\n", model_cost(m));
    for (size_t i = 0; i < 2; i++){
        for (size_t j = 0; j < 2; j++){
            float x1 = i;
            float x2 = j;
            float y_hat = forward_propagation(m, x1, x2);
            printf("x1: %f, x2: %f, y_hat: %f\n", x1, x2, y_hat);
        }
    }
}
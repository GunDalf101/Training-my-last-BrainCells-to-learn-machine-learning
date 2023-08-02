#include "lern.h"

typedef float threeFloats[3];

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
	{1, 0, 1},
	{0, 1, 1},
	{1, 1, 0}
};
#define trainNand_count sizeof(trainNand) / sizeof(trainNand[0])

threeFloats *train = trainAnd;
#define train_count trainNand_count

float sigmoidf(float x){
	return 1.0 / (1.0 + expf(-x));
}

float rand_float(){
	return (float)rand() / (float)RAND_MAX;
}

float model_cost(float w1, float w2, float b){
	float result = 0.0;
	for (size_t i = 0; i < train_count; i++){
		float x1 = train[i][0];
		float x2 = train[i][1];
		float y_hat = sigmoidf(x1 * w1 + x2 * w2 + b);
		float delta = y_hat - train[i][2];
		result += delta * delta;
	}
	result /= train_count;
	return result;
}

int main(){
	srand(time(NULL));
	printf("training my last brain cell to do Logic...\n");
	sleep(1);
	float w1 = rand_float();
	float w2 = rand_float();
	float b = -0.5;
	int k = 0;
	while (model_cost(w1, w2, b) >= 0.0002){
		float dw1 = (model_cost(w1 + 0.0001, w2, b) - model_cost(w1, w2, b)) / 0.00001;
		float dw2 = (model_cost(w1, w2 + 0.0001, b) - model_cost(w1, w2, b)) / 0.00001;
		float db = (model_cost(w1, w2, b + 0.0001) - model_cost(w1, w2, b)) / 0.00001;
		w1 -= 0.001 * dw1;
		w2 -= 0.001 * dw2;
		b -= 0.001 * db;
		printf("w1: %f, w2: %f, bias: %f,cost: %f\n", w1, w2, b,model_cost(w1, w2, b));
	}
	printf("w1: %f, w2: %f, cost: %f\n", w1, w2, model_cost(w1, w2, b));
	for (size_t i = 0; i < 2; i++){
		for (size_t j = 0; j < 2; j++){
			float x1 = i;
			float x2 = j;
			float y_hat = sigmoidf(x1 * w1 + x2 * w2 + b);
			printf("x1: %f, x2: %f, y_hat: %f\n", x1, x2, y_hat);
		}
	}
}
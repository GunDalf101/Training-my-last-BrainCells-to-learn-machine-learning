#include "lern.h"

float trainOr[][3] = {
	{0, 0, 0},
	{1, 0, 1},
	{0, 1, 1},
	{1, 1, 1}
};
#define trainOr_count sizeof(trainOr) / sizeof(trainOr[0])
// float trainAnd[][2] = {
// 	{0, 0, 0},
// 	{1, 0, 0},
// 	{0, 1, 0},
// 	{1, 1, 1}
// };
// #define trainAnd_count sizeof(trainAnd) / sizeof(trainAnd[0])

float sigmoidf(float x){
	return 1.0 / (1.0 + expf(-x));
}

float rand_float(){
	srand(time(NULL));
	return (float)rand() / (float)RAND_MAX;
}

float model_cost(float w1, float w2){
	float result = 0.0;
	for (size_t i = 0; i < trainOr_count; i++){
		float x1 = trainOr[i][0];
		float x2 = trainOr[i][1];
		float y_hat = sigmoidf(x1 * w1 + x2 * w2);
		float delta = y_hat - trainOr[i][2];
		result += delta * delta;
	}
	result /= trainOr_count;
	return result;
}

int main(){
	printf("training my last brain cell to do Logic...\n");
	sleep(1);
	float w1 = rand_float();
	float w2 = rand_float();

	while (model_cost(w1, w2) > 0.1){
		float dw1 = (model_cost(w1 + 0.00001, w2) - model_cost(w1, w2)) / 0.00001;
		float dw2 = (model_cost(w1, w2 + 0.00001) - model_cost(w1, w2)) / 0.00001;
		w1 -= 0.1 * dw1;
		w2 -= 0.1 * dw2;
		printf("w1: %f, w2: %f, cost: %f\n", w1, w2, model_cost(w1, w2));
	}
	printf("w1: %f, w2: %f, cost: %f\n", w1, w2, model_cost(w1, w2));
}
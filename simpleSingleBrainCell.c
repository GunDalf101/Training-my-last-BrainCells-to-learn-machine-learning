#include "lern.h"

float train[][2] = {
	{0, 0},
	{1, 1},
	{2, 2},
	{3, 3},
	{4, 4}
};
#define train_count sizeof(train) / sizeof(train[0])
float rand_float(){
	return (float)rand() / (float)RAND_MAX;
}

float model_cost(float w, float b){
	float result = 0.0;
	for (size_t i = 0; i < train_count; i++){
		float x = train[i][0];
		float y_hat = w * x + b;
		float error = y_hat - train[i][1];
		result += error * error;
	}
	result /= train_count;
	return result;
}

int main(){
	srand(time(NULL));
	printf("training my last brain cell to do math...\n");
	sleep(1);
	float w = rand_float() * 10;
	float b = rand_float() * 5;
	printf("rand: %f\n", w);
	while (model_cost(w, b) > 0.00001){
		float gradient = 0.0;
		float bGradient = 0.0;
		for (size_t i = 0; i < train_count; i++){
			float x = train[i][0];
			float y_hat = w * x + b;
			float error = y_hat - train[i][1];
			gradient += error * x;
			bGradient += error;
		}
		gradient /= train_count;
		w -= 0.001 * gradient;
		b -= 0.001 * bGradient;
		printf("w: %f, b: %f, cost: %f\n", w, b, model_cost(w, b));
	}
	printf("----------------\n");
	printf("w: %f, b: %f, cost: %f\n", w, b, model_cost(w, b));

	return 0;
}
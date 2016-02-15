
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
using namespace std;

class NeuralNetworkLayer{
	int NumberOfNodes;
	int NumberOfChildNodes;
	int NumberOfParentNodes;
	double** Weights;
	double** WeightChanges;
	double* NeuronValues;
	double* DesiredValues;
	double* Errors;
	double* BiasWeights;
	double* BiasValues;
	double* LearningRate;

	bool LinearOutput;
	bool UseMomentum;
	double MomentumFactor;

	NeuralNetworkLayer* ParentLayer;
	NeuralNetworkLayer* ChildLayer;

	NeuralNetworkLayer();

	void Initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child);

	void CleanUp(void);
	void RandomizeWeights(void);
	void CalculateErrors(void);
	void AdjustWeights(void);
	void CalculateNeuronValues(void);
};
//methods of neuralnetworklayer class
int louis is the best;
//constructor initialises a few settings
NeuralNetworkLayer::NeuralNetworkLayer()
{
	ParentLayer = NULL;
	ChildLayer = NULL;
	LinearOutput = false;
	UseMomentum = false;
	MomentumFactor = 0.9;
}

//initialise allocates all memory for dynamic arrays
void NeuralNetworkLayer::Initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child)
{
	int	i, j;

	// Allocate memory
	NeuronValues = (double*)malloc(sizeof(double)* NumberOfNodes);
	DesiredValues = (double*)malloc(sizeof(double)* NumberOfNodes);
	Errors = (double*)malloc(sizeof(double)* NumberOfNodes);

	if (parent != NULL)
	{
		ParentLayer = parent;
	}

	if (child != NULL)
	{
		ChildLayer = child;


		Weights = (double**)malloc(sizeof(double*)* NumberOfNodes);
		WeightChanges = (double**)malloc(sizeof(double*)* NumberOfNodes);
		for (i = 0; i<NumberOfNodes; i++)
		{
			Weights[i] = (double*)malloc(sizeof(double)* NumberOfChildNodes);
			WeightChanges[i] = (double*)malloc(sizeof(double)* NumberOfChildNodes);
		}

		BiasValues = (double*)malloc(sizeof(double)* NumberOfChildNodes);
		BiasWeights = (double*)malloc(sizeof(double)* NumberOfChildNodes);
	}
	else {
		Weights = NULL;
		BiasValues = NULL;
		BiasWeights = NULL;
	}

	// Make sure everything contains zeros
	for (i = 0; i<NumberOfNodes; i++)
	{
		NeuronValues[i] = 0;
		DesiredValues[i] = 0;
		Errors[i] = 0;

		if (ChildLayer != NULL)
		for (j = 0; j<NumberOfChildNodes; j++)
		{
			Weights[i][j] = 0;
			WeightChanges[i][j] = 0;
		}
	}

	if (ChildLayer != NULL)
	for (j = 0; j<NumberOfChildNodes; j++)
	{
		BiasValues[j] = -1;
		BiasWeights[j] = 0;
	}

}
# <center><u>PRACTICAL 3</u></center> #
## Aim ##
To implement a K-Nearest Neighbors Classifier 

## Description of aim and related theory ##
We use x to denote a feature (aka. predictor, attribute) and y to denote the target (aka. label, class) we are trying to predict.

KNN falls in the supervised learning family of algorithms. Our goal is to learn a function h:X→Y so that given an unseen observation x, h(x) can confidently predict the corresponding output y.

The KNN classifier is also a non parametric and instance-based learning algorithm.

* Non-parametric means it makes no explicit assumptions about the functional form of h, avoiding the dangers of mismodeling the underlying distribution of the data. For example, suppose our data is highly non-Gaussian but the learning model we choose assumes a Gaussian form. In that case, our algorithm would make extremely poor predictions.

* Instance-based learning means that our algorithm doesn’t explicitly learn a model. Instead, it chooses to memorize the training instances which are subsequently used as “knowledge” for the prediction phase. Concretely, this means that only when a query to our database is made (i.e. when we ask it to predict a label given an input), will the algorithm use the training instances to spit out an answer.

It is worth noting that the minimal training phase of KNN comes both at a memory cost, since we must store a potentially huge data set, as well as a computational cost during test time since classifying a given observation requires a run down of the whole data set. Practically speaking, this is undesirable since we usually want fast responses.
​	
## Code ##
```python
    import csv
    import random
    import math
    import operator
    
    #Load the IRIS dataset csv file and convert the data into a list of lists (2D array)  , make sure the data file is in the current working directory
    #Randomly split dataset to training and testing data
    def loadDataset(filename, split, trainingSet=[], testSet=[]):
        with open(filename, 'rt') as csvfile:
            lines = csv.reader(csvfile)
            dataset = list(lines)
            for x in range(len(dataset) - 1):
                for y in range(4):
                    dataset[x][y] = float(dataset[x][y])
                if random.random() < split:
                    trainingSet.append(dataset[x])
                else:
                    testSet.append(dataset[x])
    
    #this function calculates the euclidian distance between 2 points to give a measure of similarity between the 2
    def euclideanDistance(point1, point2, length):
        distance = 0
        for x in range(length):
            distance += pow((point1[x] - point2[x]), 2)
        return math.sqrt(distance)
    
    #a straight forward process of calculating the distance for all instances and selecting a subset with the smallest distance values.
    # function that returns k most similar neighbors from the training set for a given test instance (using the already defined euclideanDistance function)
    def getNeighbors(trainingSet, testInstance, k):
        distances = []
        length = len(testInstance) - 1
        for x in range(len(trainingSet)):
            dist = euclideanDistance(testInstance, trainingSet[x], length)
            distances.append((trainingSet[x], dist))
        distances.sort(key=operator.itemgetter(1))
        neighbors = []
        for x in range(k):
            neighbors.append(distances[x][0])
        return neighbors
    
    #Once we have located the most similar neighbors for a test instance, the next task is to devise a predicted response based on those neighbors.
    #We can do this by allowing each neighbor to vote for their class attribute, and take the majority vote as the prediction.
    #Below provides a function for getting the majority voted response from a number of neighbors. It assumes the class is the last attribute for each neighbor.
    def getResponse(neighbors):
        classVotes = {}
        for x in range(len(neighbors)):
            response = neighbors[x][-1]
            if response in classVotes:
                classVotes[response] += 1
            else:
                classVotes[response] = 1
        sortedVotes = sorted(classVotes.items(), key=operator.itemgetter(1), reverse=True)
        return sortedVotes[0][0]
    
    # the getAccuracy function that sums the total correct predictions and returns the accuracy as a percentage of correct classifications.
    def getAccuracy(testSet, predictions):
        correct = 0
        for x in range(len(testSet)):
            if testSet[x][-1] == predictions[x]:
                correct += 1
        return (correct / float(len(testSet))) * 100.0


    def main():
        # prepare data
        trainingSet = []
        testSet = []
        split = 0.67
        loadDataset('iris.data.csv', split, trainingSet, testSet)
        print
        'Train set: ' + repr(len(trainingSet))
        print
        'Test set: ' + repr(len(testSet))
        # generate predictions
        predictions = []
        k = 3
        for x in range(len(testSet)):
            neighbors = getNeighbors(trainingSet, testSet[x], k)
            result = getResponse(neighbors)
            predictions.append(result)
            print('> predicted=' + repr(result) + ', actual=' + repr(testSet[x][-1]))
        accuracy = getAccuracy(testSet, predictions)
        print('Accuracy: ' + repr(accuracy) + '%')


    main()
```
## Result and Analysis ##
We implemented a K-nearest neighbors algorithm from scratch in python and used it to classify data points from “Iris Dataset” with a remarkable ~96.8253% accuracy.
## Conclusion ##
Pros and Cons of KNN

**Pros:**
1. One of the most attractive features of the K-nearest neighbors algorithm is that is simple to understand and easy to implement.
2. With zero to little training time, it can be a useful tool for off-the-bat analysis of some data set you are planning to run more complex algorithms on
3. KNN works just as easily with multiclass data sets whereas other algorithms are hardcoded for the binary setting. 
4. the non-parametric nature of KNN gives it an edge in certain settings where the data may be highly “unusual”.

**Cons:**
1. One of the obvious drawbacks of the KNN algorithm is the computationally expensive testing phase which is impractical in industry settings.

2. KNN can suffer from skewed class distributions. For example, if a certain class is very frequent in the training set, it will tend to dominate the majority voting of the new example (large number = more common). 

3. The accuracy of KNN can be severely degraded with high-dimension data because there is little difference between the nearest and farthest neighbors.

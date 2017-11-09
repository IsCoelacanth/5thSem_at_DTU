# <center><u>PRACTICAL 2</u></center> 
## Aim 
To Implement a Gaussian Naïve Bayes Classifier.

## Description of aim and related theory
+ It is a classification technique based on Bayes Theorem.

+ Due to the assumption of independence among predictors it is known as ‘Naive’. In simple terms, a Naive Bayes classifier assumes that the presence of a particular feature in a class is unrelated to the presence of any other feature. 

+ For example, a fruit may be considered to be an apple if it is red, round, and about 3 inches in diameter. Even if these features depend on each other or upon the existence of the other features, all of these properties independently contribute to the probability that this fruit is an apple and that is why it is known as ‘Naive’.

+ Naive Bayes model is easy to build and particularly useful for very large data sets. Along with simplicity, 
  ​
## Code ##

```python
import csv
import random
import math

#load the data from a csv file and convert it into a list of lists so that they are easy to use
#make sure you pass the full address in filepath or the data file is in same directory as this python file
def loadCsv(filename):
    lines = csv.reader(open(filename, "rt"))
    dataset = list(lines)
    for i in range(len(dataset)):
        dataset[i] = [float(x) for x in dataset[i]]
    return dataset

#this function is used to split the given data into training and testing sets
def splitDataset(dataset, splitRatio):
    trainSize = int(len(dataset) * splitRatio)
    trainSet = []
    copy = list(dataset)
    while len(trainSet) < trainSize:
        index = random.randrange(len(copy))
        trainSet.append(copy.pop(index))
    return [trainSet, copy]

#The first task is to separate the training dataset instances by class value so that we can calculate statistics for each class.
# We can do that by creating a map of each class value to a list of instances that belong to that class and sort the entire dataset of instances into the appropriate lists.
#-1 index is used to refer to the last elemnt of the list ie the class
def separateByClass(dataset):
    separated = {}
    for i in range(len(dataset)):
        vector = dataset[i]
        if (vector[-1] not in separated):
            separated[vector[-1]] = []
        separated[vector[-1]].append(vector)
    return separated

#calculate the mean of each attribute for a class value
def mean(numbers):
    return sum(numbers) / float(len(numbers))

#to calculate the standard deviation from variance of each attribute for a class value
def stdev(numbers):
    avg = mean(numbers)
    variance = sum([pow(x - avg, 2) for x in numbers]) / float(len(numbers) - 1)
    return math.sqrt(variance)

#For a given list of instances
# (for a class value) we can calculate the mean and the standard deviation
# for each attribute.
#The zip function
# groups the values for each attribute across our data instances into their own lists
# so that we can compute the mean and standard deviation values for the attribute.
def summarize(dataset):
    summaries = [(mean(attribute), stdev(attribute)) for attribute in zip(*dataset)]
    del summaries[-1]
    return summaries

#we first separate our training data set into instances grouped by class.
#Then calculate the summaries for each attribute.
def summarizeByClass(dataset):
    separated = separateByClass(dataset)
    summaries = {}
    for classValue, instances in separated.items():
        summaries[classValue] = summarize(instances)
    return summaries

#We can use a Gaussian function to estimate the probability of a given attribute value,
# given the known mean and standard deviation
# for the attribute estimated from the training data.
def calculateProbability(x, mean, stdev):
    exponent = math.exp(-(math.pow(x - mean, 2) / (2 * math.pow(stdev, 2))))
    return (1 / (math.sqrt(2 * math.pi) * stdev)) * exponent

#Now that we can calculate the probability
# of an attribute belonging to a class,
# we can combine the probabilities
# of all of the attribute values for a data instance and come up4
# with a probability of the entire data instance belonging to the class.
def calculateClassProbabilities(summaries, inputVector):
    probabilities = {}
    for classValue, classSummaries in summaries.items():
        probabilities[classValue] = 1
        for i in range(len(classSummaries)):
            mean, stdev = classSummaries[i]
            x = inputVector[i]
            probabilities[classValue] *= calculateProbability(x, mean, stdev)
    return probabilities

#Now that can calculate the probability of a data instance belonging to each class value,
#  we can look for the largest probability and return the associated class.
def predict(summaries, inputVector):
    probabilities = calculateClassProbabilities(summaries, inputVector)
    bestLabel, bestProb = None, -1
    for classValue, probability in probabilities.items():
        if bestLabel is None or probability > bestProb:
            bestProb = probability
            bestLabel = classValue
    return bestLabel

#Finally, we can estimate the accuracy of the model by making predictions
# for each data instance in our test dataset.
# The getPredictions() will do this and
# return a list of predictions for each test instance.
def getPredictions(summaries, testSet):
    predictions = []
    for i in range(len(testSet)):
        result = predict(summaries, testSet[i])
        predictions.append(result)
    return predictions

#The predictions can be compared to the class values in the test dataset
# and a classification accuracy can be calculated as an accuracy ratio
# between 0& and 100%.
# The getAccuracy() will calculate this accuracy ratio.
def getAccuracy(testSet, predictions):
   correct = 0
   for x in range(len(testSet)):
      if testSet[x][-1] == predictions[x]:
         correct += 1
   return (correct/float(len(testSet))) * 100.0

def getAccuracy(testSet, predictions):
    correct = 0
    for i in range(len(testSet)):
        if testSet[i][-1] == predictions[i]:
            correct += 1
    return (correct / float(len(testSet))) * 100.0

def main():
    filename = "pima-indians-diabetes.data.csv"
    splitRatio = 0.67
    dataset = loadCsv(filename)
    trainingSet, testSet = splitDataset(dataset, splitRatio)
    print('Split',len(dataset),'rows into train',len(trainingSet), 'test',len(testSet))
    # prepare model
    summaries = summarizeByClass(trainingSet)
    # test model
    predictions = getPredictions(summaries, testSet)
    accuracy = getAccuracy(testSet, predictions)
    print('Accuracy:is ',accuracy)

#call the main function
main()
```

## Result and Analysis ##
We performed Naïve Bayes classification on the given dataset to classify test data into one of the 2 classes representing “Diabetic” or “Non-Diabetic” with appreciable (approximately 75.509%) accuracy.
## Conclusion ##
Naive Bayes is known to outperform even highly sophisticated classification methods.

**Pros:**
* It is easy and fast to predict class of test data set. It also perform well in multi class prediction
* When assumption of independence holds, a Naive Bayes classifier performs better compare to other models like logistic regression and you need less training data.
* It performs well in case of categorical input variables compared to numerical variable(s). For numerical variable, normal distribution is assumed (bell curve, which is a strong assumption).

**Cons:**
* If categorical variable has a category (in test data set), which was not observed in training data set, then model will assign a 0 (zero) probability and will be unable to make a prediction. This is often known as “Zero Frequency”. 
* Another limitation of Naive Bayes is the assumption of independent predictors. In real life, it is almost impossible that we get a set of predictors which are completely independent.


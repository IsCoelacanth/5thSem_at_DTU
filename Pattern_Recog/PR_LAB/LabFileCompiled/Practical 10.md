# <center>PRACTICAL 10</center> #
## Aim ##
To use MLP to implement various gates

## Description of aim and related theory ##
A multilayer perceptron (MLP) is a class of  feedforward artificial neural network . An MLP
consists of at least three layers of nodes. Except for the input nodes, each node is a neuron that
uses a nonlinear  activation function . MLP utilizes a  supervised learning technique called
backpropagation for training. Its multiple layers and non-linear activation distinguish MLP from a
linear perceptron . It can distinguish data that is not linearly separable.

Multilayer perceptrons are sometimes colloquially referred to as "vanilla" neural networks,
especially when they have a single hidden layer.

## Code ##
```python
import numpy as np 

def sigmoid(x): 
  return 1 / (1 + np.exp(-x)) 

def AND(x1, x2): 
  x = np.array([x1, x2]) 
  w = np.array([[10], [10]]) 
  b = np.array([-15]) 
  z = np.dot(x, w) + b 
  y = sigmoid(z) 
  return y 

def OR(x1, x2): 
  x = np.array([x1, x2]) 
  w = np.array([[10], [10]]) 
  b = np.array([-5]) 
  z = np.dot(x, w) + b 
  y = sigmoid(z) 
  return y 

def XOR(x1, x2): 
  x = np.array([x1,x2]) 
  w1= np.array([[10,-10],[-10,10]]) 
  b1= np.array([-5,-5]) 
  w2= np.array([[10],[10]]) 
  b2= np.array([-5]) 
  z1= np.dot(x,w1)+ b1 
  h1= sigmoid(z1) 
  z2= np.dot(h1,w2)+ b2 
  y = sigmoid(z2) 
  return y 


for i in range(2): 
  for j in range(2): 
      print("%d and %d = %f" % (i, j, AND(i, j))) 
print() 

for i in range(2): 
  for j in range(2): 
      print("%d or %d = %f" % (i, j, OR(i, j))) 
print() 

for i in range(2): 
  for j in range(2): 
      print("%d xor %d = %f" % (i, j, XOR(i, j))) 
print() 
```
## Result and Analysis ##
| L1   | boolean | L2   | result    |
| ---- | ------- | ---- | --------- |
| 0    | AND     | 0    | 0.000000  |
| 0    | AND     | 1    | 0.006696  |
| 1    | AND     | 0    | 0.006696  |
| 1    | AND     | 1    | 0.993307  |
| ---  | ----    | ---- | ----      |
| 0    | OR      | 0    | 0.0006696 |
| 0    | OR      | 1    | 0.993307  |
| 1    | OR      | 0    | 0.993307  |
| 1    | OR      | 1    | 1.000000  |
| ---  | ----    | ---- | ----      |
| 0    | XOR     | 0    | 0.007644  |
| 0    | XOR     | 1    | 0.992847  |
| 1    | XOR     | 0    | 0.992847  |
| 1    | XOR     | 1    | 0.007644  |

​We  implemented  basic  logic  gates  using  MLP. 
## Conclusion ##
A​ ​ very​ ​ simple​ ​ multiple​ ​ layer​ ​ perceptron​ ​ can​ ​ be​ ​ used​ ​ to​ ​ implement​ ​ basic 
logic​ ​ gates. 
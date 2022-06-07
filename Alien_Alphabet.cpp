
/*
 * Title: main_hw10_2.cpp
 * Abstract: Find the alphabetical order of a language given a number of dictionary inputs (that are in order)
 * ID: 0000
 * Name: Luke Richard Avra
 * Date: 04/21/2022
 */

#include <iostream>
#include <set>
#include <queue>
using namespace std;
// Extremely similar to 10_1, create the same answerQueues and very similar arrays (using an extra char array for comparison against the inDegree array) and cin all the user input
int main()
{
  queue<char> answerQueue;
  queue<char> answerQueueFinal;
  int inputs, edgeLocation = 0;
  cin >> inputs;
  string userArray[inputs];
  int charArr[26][26];
  for(int i = 0; i < 26; i++){
    for(int j = 0; j < 26; j++){
      charArr[i][j] = 0;
    }
  }
  //Establish edge graph with the # symbol so there won't be any confusion the the letters
  char edges[100][2];
  for(int i = 0; i < 100; i++){
    edges[i][0] = '#';
    edges[i][1] = '#';
  }
  //Create a set of all input values, eliminating duplicates and put them into the inDegree character array called userArray (continued on line 55)
  set<char> val;

  for(int i = 0; i < inputs; i++){
    cin >> userArray[i];
  }

  // run through the dictionary terms, checking the first nonmatching letters between subsequent terms to add to the edges graph (aaa, aab would result in an a->b edge as the first two a's in both terms are ignored for being equivalent)
  for(int i = 0; i < inputs - 1; i++){
    int j = 0; 
    while(j < userArray[i].size() && userArray[i][j] == userArray[i+1][j]){
      j++;
    }
    if(userArray[i][j] != userArray[i+1][j]){
      edges[edgeLocation][0] = userArray[i][j];
      edges[edgeLocation][1] = userArray[i + 1][j];
      edgeLocation++;
    }
  }

  // Insert edges into set to get all characters used in the dictionary terms
  for(int i = 0; i < 100; i++){
    if(edges[i][0] != '#' && edges[i][1] != '#'){
      val.insert(edges[i][0]);
      val.insert(edges[i][1]);
    }
  }

  // Check for duplicates within the edges, removing any extraneous values by converting them back to the # symbol
  for(int i = 0; i < 100; i++){
    for(int j = 0; j < 100; j++){
      if(edges[i][0] == edges[j][0] && i != j){
        if(edges[i][1] == edges[j][1]){
          edges[j][0] = '#';
          edges[j][1] = '#';
        }
      }
    }
  }

  // Count the values in the set, create the charArray and place the values in so we have a corresponding charArray and inDegree array to play with (same indexes)
  set<char>::iterator itr;
  int count = 0;
  for (itr = val.begin(); itr != val.end(); itr++) {
    count++;
  }

  char charArray[count];
  int inDegree[count];
  count = 0;
  for (itr = val.begin(); itr != val.end(); itr++) {
    charArray[count] = *itr;
    count++;
  }

  // Tun through the edges array and charArray to create the graph of edges
  for(int i = 0; i < 100; i++){
    if(edges[i][0] != '#' && edges[i][1] != '#'){
      for(int k = 0; k < count; k++){
        if(edges[i][0] == charArray[k]){
          for(int j = 0; j < count; j++){
            if(edges[i][1] == charArray[j]){
              charArr[k][j] = 1;
            }
          }
        }
      }
    }
  }

  // Run through the graph, counting the number of incoming edges for each value and place them into the inDegree array
  int sum = 0;
  for(int i = 0; i < count; i++){
    sum = 0;
    for(int j = 0; j < count; j++){
      sum += charArr[j][i];
    }
    inDegree[i] = sum;
  }

  // Perform the final operation of running through the inDegree array, pushing the corresponding character into the answerQueue when it's corresponding index in inDegree pulls a value of 0. Then using the front of that queue to run through the inDegree array, removing a single incoming edge from each vertice the answerQueue.front() touches, then popping the front off and into the final answer queue for cout. Repeat until all vertices are accounted for (when arrayCounter = count)
  int arrayCounter = 0;
  while(arrayCounter < count){
    for(int i = 0; i < count; i++){
      if(inDegree[i] == 0){
        answerQueue.push(charArray[i]);
        arrayCounter += 1;
        inDegree[i] = -5;
      }
    }
  
    for(int i = 0; i < 100; i++){
      if(edges[i][0] != '#' && edges[i][1] != '#'){
        if(edges[i][0] == answerQueue.front()){
          for(int j = 0; j < count; j++){
            if(charArray[j] == edges[i][1]){
              inDegree[j] -= 1;
            }
          }
        }
      }
    }
    answerQueueFinal.push(answerQueue.front());
    answerQueue.pop();
  }

  // cout using the syntax required in the unit tests.
  cout << answerQueueFinal.front();
  answerQueueFinal.pop();
      
  while(!answerQueueFinal.empty()){
    cout << "->" << answerQueueFinal.front();
    answerQueueFinal.pop();
  }
  cout << endl;
  return 0;
}


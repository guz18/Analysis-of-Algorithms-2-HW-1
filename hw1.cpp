// GÖKSU GÜZ - 150180715
// I compile my code with:
// g++ -std=c++11 main.cpp -o main

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <string.h>
#include <chrono>
#include <bits/stdc++.h>
#include <stdlib.h>  
#include <list>
#include <time.h>
#include <cmath>
using namespace std;


vector <char> letters;
vector <int> correspondingNumbers;
vector <string> wordsOfPuzzle;

class Graph
{
public:
	int numberOfVisitedNodes = 0;
	int maxNumberNodeMemory = 0;
	int resultOfAll = 0;
    int size = 0;
    bool found = false;

    map<int, bool> visited;
    map<int, list<int>> aNode;
    vector<int>min;
    vector<int>max; 

    void addARelation(int v, int w);
    void DFS(int v, string words[]);
    void BFS(int s, string words[]);
    int check(int v, string words[]);
    int dI(char s);
    int checkForBranch(int v, string words[]);
    int numberCreator(int v[]);
};

int Graph::numberCreator(int v[]){
	int result = 0;
	for (int i=0; i < size; i++)
	{
	  result = result*10 + v[i];
	}	
	resultOfAll = result;
	return result;
}

int Graph::dI(char s){
    int i = 0;
    for(; i < size; i++){
        if(tolower(s) == tolower(letters[i]))
            return i;
    }
    return i;
}

int Graph::checkForBranch(int v, string words[]){
    if(v == 0)
    return 2;

    int i = 0;
    for(; i < size + 1; i++){
        if(v <= max[i] && v >= min[i])
            break;
    }

    int x = v - min[i];

    int array[size];
    
    int ptr = x;
    for(int j = i; j > 0 ; j--){
        int temp = pow(10,j-1);
        array[i-j] = ptr / temp;
        ptr -= (ptr/temp)*temp;
    }
    for(int j = i; j < size; j++)
        array[j] = -1;

        for(int m = 0; m < size; m++){ // letter can not be the same
        for(int j = m+1; j < size; j++)
        {
            if(array[j] == array[m] && array[j] != -1)
                return -1;
        }
    }
    if(words[2].length() > words[1].length() && words[2].length() > words[0].length()){
        if(array[dI(words[2][0])] != 1 && array[dI(words[2][0])] != -1) // the result's first letter must be 1
            return -1;
    }
    if(array[dI(words[0][0])] == 0 || array[dI(words[1][0])] == 0) // the first letter of the words being added can not be 0 
    return -1;

    if(words[0].length() == words[1].length() && words[1].length() < words[2].length()){
        if((array[dI(words[0][0])] + array[dI(words[1][0])] < 10) && array[dI(words[1][0])] != -1 && array[dI(words[0][0])] != -1){// if you add two same length word and the result is in larger length 
            return -1;
        }
    }

    if(array[size-1] == -1) // if any of the letters is -1 don't try to calculate
        return 2;

    return 2;
}


int Graph::check(int v, string words[]){
    if(v == 0)
        return 2;

    int i = 0;
    for(; i < size + 1; i++){
        if(v <= max[i] && v >= min[i])
            break;
    }

    int x = v - min[i];

    int array[size];
    
    int ptr = x;
    for(int j = i; j > 0 ; j--){
        int temp = pow(10,j-1);
        array[i-j] = ptr / temp;
        ptr -= (ptr/temp)*temp;
    }
    for(int j = i; j < size; j++)
        array[j] = -1;

            for(int m = 0; m < size; m++){ // letter can not be the same
        for(int j = m+1; j < size; j++)
        {
            if(array[j] == array[m] && array[j] != -1)
                return -1;
        }
    }

    if(words[2].length() > words[1].length() && words[2].length() > words[0].length()){
    if(array[dI(words[2][0])] != 1 && array[dI(words[2][0])] != -1) // the result's first letter must be 1
        return -1;
    }

    if(array[dI(words[0][0])] == 0 || array[dI(words[1][0])] == 0) // the first letter of the words being added can not be 0 
    return -1;

    if(words[0].length() == words[1].length() && words[1].length() < words[2].length()){
        if((array[dI(words[0][0])] + array[dI(words[1][0])] < 10) && array[dI(words[1][0])] != -1 && array[dI(words[0][0])] != -1){// if you add two same length word and the result is in larger length 
            return -1;
        }
    }

    if(array[size-1] == -1) // if any of the letters is -1 don't try to calculate
        return 2;

    if(words[0].length() == 3 && words[1].length() == 3){
        int mul = 1;
        int count = 0;
        for(int j = 2; j >= 0 ; j--){
            int x = dI(words[0][j]);
            int y = dI(words[1][j]);
            count += (array[x] + array[y]) * mul;
            mul *= 10;
        }
        if(words[2].length() == 3){
            if(count == array[dI(words[2][0])]*100 + array[dI(words[2][1])]*10 + array[dI(words[2][2])])
                return numberCreator(array);
            else
                return 2;
        }
        else if(words[2].length() == 4){
            if(count == array[dI(words[2][0])]*1000 + array[dI(words[2][1])]*100 + array[dI(words[2][2])]*10 + array[dI(words[2][3])]){
            return numberCreator(array);
        }
            else
                return 2;
        }
    }
    
    else if(words[0].length() == 4 && words[1].length() == 3){
        int mul = 1;
        int count = 0;
        for(int j = 2; j >= 0 ; j--){
            int x = dI(words[0][j]);
            int y = dI(words[1][j]);
            count += (array[x]*10*mul + mul*array[y]) ;
            mul *= 10;
        }
        if(words[2].length() == 4){
            count += array[dI(words[0][3])];
            if(count == array[dI(words[2][0])]*1000 + array[dI(words[2][1])]*100 + array[dI(words[2][2])]*10 + array[dI(words[2][3])])
                return numberCreator(array);
            else
                return 2;
        }
        else if(words[2].length() == 5){
            count += array[dI(words[0][3])];
            if(count == array[dI(words[2][0])]*10000 + array[dI(words[2][1])]*1000 + array[dI(words[2][2])]*100 + array[dI(words[2][3])]*10 + array[dI(words[2][4])])
                return numberCreator(array);
            else
                return 2;
        }
    }

    else if(words[0].length() == 3 && words[1].length() == 4){
        int mul = 1;
        int count = 0;
        for(int j = 2; j >= 0 ; j--){
            int x = dI(words[1][j]);
            int y = dI(words[0][j]);
            count += (array[x]*10*mul + mul*array[y]) ;
            mul *= 10;
        }
        if(words[2].length() == 4){
            count += array[dI(words[1][3])];
            if(count == array[dI(words[2][0])]*1000 + array[dI(words[2][1])]*100 + array[dI(words[2][2])]*10 + array[dI(words[2][3])])
                return numberCreator(array);
            else
                return 2;
        }
        else if(words[2].length() == 5){
            count += array[dI(words[1][3])];
            if(count == array[dI(words[2][0])]*10000 + array[dI(words[2][1])]*1000 + array[dI(words[2][2])]*100 + array[dI(words[2][3])]*10 + array[dI(words[2][4])])
                return numberCreator(array);
            else
                return 2;
        }
    }

    else if(words[0].length() == 4 && words[1].length() == 4){
        int mul = 1;
        int count = 0;
        for(int j = 3; j >= 0 ; j--){
            int x = dI(words[0][j]);
            int y = dI(words[1][j]);
            count += (array[x] + array[y]) * mul;
            mul *= 10;
        }
        if(words[2].length() == 4){
            if(count == array[dI(words[2][0])]*1000 + array[dI(words[2][1])]*100 + array[dI(words[2][2])]*10 + array[dI(words[2][3])])
                return numberCreator(array);
            else
                return 2;
        }
        else if(words[2].length() == 5){
            if(count == array[dI(words[2][0])]*10000 + array[dI(words[2][1])]*1000 + array[dI(words[2][2])]*100 + array[dI(words[2][3])]*10 + array[dI(words[2][4])]){
                return numberCreator(array);
            }
            else
                return 2;
        }
    }
    return 2;
}


void Graph::addARelation(int v, int w)
{
    aNode[v].push_back(w); // Add w to  list.
}
 
void Graph::BFS(int s, string words[])
{
    if(found == false){
        list<int> liste;

        visited[s] = true;
        liste.push_back(s);
        list<int>::iterator node;
    
        while(!liste.empty())
        {
            s = liste.front();
            liste.pop_front();
    
            for (node = aNode[s].begin(); node != aNode[s].end(); ++node)
            {
                if (!visited[*node])
                {
                    int a = check(*node, words);
                    if(a == 2){
                    	numberOfVisitedNodes++;
                        visited[*node] = true;
                        liste.push_back(*node);
                    }
                    else if(a == -1);
                    else{
                        found = true;
                        return;
                    }
                }
            }
        }
    }
}


void Graph::DFS(int v, string words[]){
    if(found == false){
        visited[v] = true;
        list<int>::iterator node;
        for (node = aNode[v].begin(); node != aNode[v].end(); ++node){
            if (!visited[*node]){
                int a = check(*node, words);
                if(a == 2){
                	numberOfVisitedNodes++;
                    DFS(*node, words);
                }
                else if(a == -1);
                else{
                    found = true;
                    return;
                }
            }
        }
    }
}

int main(int argc, char **argv){

    clock_t start, end;

    start = clock();
    
    Graph g;

    ifstream file;

    string method = argv[1];
    string words[3];
    words[0] = argv[2];
    words[1] = argv[3];
    words[2] = argv[4];

   bool ptr1 = true;
   for(int i = 0; i < 3; i++){
       for (auto x : words[i]) {
           ptr1 = true;
           int ctr = letters.size();
           for(int j = 0; j < ctr; j++){
                if(letters[j] == x){
                    ptr1 = false;
                    break;
                }
            }
            if(ptr1 == true)
                letters.push_back(x);
        }
    }
    int sizeofVecLetters = letters.size();

    int min = 0;
    int max = 0;
    int mul = 1;

    for(int i=0; i < sizeofVecLetters+1; i++){
        g.min.push_back(min);
        g.max.push_back(max);
        mul *= 10;
        min = max + 1;
        max = min+mul -1;
    }   
    g.size = sizeofVecLetters;

    // I created the tree below
    int a = 1;
    int b = 1;
    int r = 1;

    for(int i = 1; i < sizeofVecLetters; i++){
        a *= 10;
        b += a;
    }
    int x = 1;
    int t = 0;
    int numberIAmAt = 1;

    for(int i = 0; i < sizeofVecLetters; i++){
        for(; t < x; t++){ 
            if(g.checkForBranch(t, words) == -1);
            else{         
                for(int j = numberIAmAt; j < numberIAmAt + 10; j++){
                	g.maxNumberNodeMemory++;
                    g.addARelation(t, j); // add to the graph
            }
            }
            numberIAmAt+=10;
        }
        t = x;
        r *= 10;
        x = r + x;
    }


    if(method == "DFS" || method == "dfs"){
        g.DFS(0, words);
    }
    else if(method == "BFS" || method == "bfs"){
        g.BFS(0, words);
    }

    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

    int wordsOfArray1[g.size];

    int multiply = 10;
    int hold = g.resultOfAll;
    for(int i = g.size - 1; i >= 0; i--){
        wordsOfArray1[i] = hold % multiply;
        hold = hold - hold % multiply;
        hold = hold / 10;
    }   


    ofstream myfile;
    string a1 = argv[5];
    string a2 = ".txt";
    string fileNm = a1 + a2;
    myfile.open(fileNm, std::fstream::in|std::ios::out | std::ios::trunc);
        myfile << "\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\n";
    for(int i = 0 ; i < g.size; i++){
        myfile << letters[i];
        for(int j = 0; j < 10; j++){
            if(j == wordsOfArray1[i])
                myfile << "\t1";
            else
                myfile << "\t.";
        }
        myfile << "\n";
    }
    myfile.close();

    cout << "Algorithm: " << method << endl;
    cout << "Number of the visited nodes: " << g.numberOfVisitedNodes << endl;
    cout << "Maximum number of nodes kept in the memory: "<< g.maxNumberNodeMemory << endl;
    cout << "Running time: " << fixed << time_taken << setprecision(5) << " seconds" << endl;
    cout << "Solution: ";
    for(int i = 0; i < g.size ; i++){
        cout << letters[i] << ": " << wordsOfArray1[i];
        if(i != g.size - 1)
            cout << ", ";
        else 
        	cout << endl;
    }
    
}

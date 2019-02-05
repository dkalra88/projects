#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <tuple>
#include <functional>
#include <bits/stdc++.h>

using namespace std;
typedef vector<tuple<int, int, int>> my_tuple;
///call as: pkgs/gcc/7.2.0/bin/g++ -std=c++17 game_of_life_exp_1.cpp
template<size_t N, size_t M>
void print_array(array<array<int,N>,M> const & c){
  for_each(c.begin(), c.end(), [] (array<int,N> a) {for_each(a.begin(), a.end(), [] (int i) {
    if(i==1){
      cout<<"*"<<" ";
    }
    else
      cout<<"."<<" ";
   }); cout<<endl;});
}

template<size_t N, size_t M>
void convert_array_to_vector(array<array<int, N>, M> const & input, my_tuple & v){
  for_each(input.begin()+1,input.end()-1,[&](array<int,N> a1) {
    for_each(a1.begin()+1,a1.end()-1,[&](int elem){
      v.push_back(make_tuple((v.size()/(N-2))+1,(v.size()%(N-2))+1,elem));
    });
  });
}

template<size_t N, size_t M>
array<array<int, N>, M> gol(array<array<int, N>, M> const & input){
  array<array<int, N>, M> future = {0};
  my_tuple v;
  convert_array_to_vector(input, v);
  vector<pair<int,int>> neighbors = {{-1,-1}, {0,-1}, {1,-1}, {-1,0}, {1,0}, {-1,1}, {0,1}, {1,1}};
  for_each(v.begin(), v.end(), [&] (tuple<int, int, int> t){
    size_t aliveNeighbours = 0;
    for_each(neighbors.begin(),neighbors.end(), [&](pair<int,int> neighbor){
      aliveNeighbours += input[(get<0>(t)+neighbor.first)][(get<1>(t)+neighbor.second)];
    });
    if ((get<2>(t) == 1) && (aliveNeighbours < 2)){
      future[get<0>(t)][get<1>(t)] = 0;
    }
    else if ((get<2>(t) == 1) && (aliveNeighbours > 3)){
      future[get<0>(t)][get<1>(t)] = 0;
    }
    else if ((get<2>(t) == 0) && (aliveNeighbours == 3)){
      future[get<0>(t)][get<1>(t)] = 1;
    }
    else
      future[get<0>(t)][get<1>(t)] = input[get<0>(t)][get<1>(t)]; 
  });
  cout<<"next generation:"<<endl;
  print_array(future); 
  return future;
}

int main(void){
  array<array<int, 5>, 6> a = {
     0, 0, 0, 0, 0,
     0, 0, 0, 1, 0,
     0, 1, 0, 0, 0,
     0, 0, 1, 1, 0,
     0, 1, 1, 0, 0,
     0, 0, 0, 0, 0
  };
  do {
    system("clear");
    print_array(a); 
    this_thread::sleep_for(chrono::seconds(1));
    a = gol(a);
  }while(true);

  return 0;
}

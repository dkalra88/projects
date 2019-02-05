#include <iostream>
#include <thread>
#include <future>
#include <algorithm>
#include <random>
#include <vector>
#include <array>
#include <string>
//// call as: pkgs/gcc/4.9.3/bin/g++ -Wall -Werror -std=c++0x -Isrc -pthread -O2 -o dna multi_threading_dna.cpp
using namespace std;
typedef std::vector<char> Sequence;

struct LocationAndLength
{
  size_t length;
  size_t locationA;
  size_t locationB;

  LocationAndLength() :
    length(0),
    locationA(0),
    locationB(0)
  {}
};


const char nucleotides[4] = {'A', 'C', 'G', 'T' };


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void findLongestMatchingSequence(LocationAndLength *result,std::vector<char>::const_iterator beginA,std::vector<char>::const_iterator endA, std::vector<char>::const_iterator beginB, std::vector<char>::const_iterator endB){
  LocationAndLength a;
  LocationAndLength tmp;

  for(auto it1 = beginA; it1!=endA; ++it1)
  {
    auto itr1 = it1;
    tmp.length = 0;
    for(auto it2=beginB; it2!=endB; ++it2)
    {
      auto itr2 = it2;
      if(*it1 == *it2)
      {
        if(it2 == endB-1){
          endB++;
        }
        tmp.length +=1;
        ++it1;
        tmp.locationA = std::distance(beginA, it1);
        tmp.locationB = std::distance(beginB, it2);
        if(tmp.length > a.length)
        {
          a.length = tmp.length;
          a.locationA = tmp.locationA - tmp.length;
          a.locationB = tmp.locationB - tmp.length+1;
        }
      }else
      {
       it1 = itr1;
       it2 = itr2 - tmp.length;
       tmp.length = 0;
      }
    }
    it1 = itr1;
  }
  *result = a;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


void initializeDataSet(Sequence& dataSet, size_t numEntries, unsigned seed)
{
  std::cout << "Generating data set of " << numEntries << " entries" << std::endl;
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<unsigned> rangeDistribution(0, 3);
  dataSet.reserve(numEntries);

  while (dataSet.size() < numEntries)
  {
    dataSet.push_back(nucleotides[rangeDistribution(generator)]);
  }
}

LocationAndLength parallel(std::vector<char>::const_iterator beginA,std::vector<char>::const_iterator endA, std::vector<char>::const_iterator beginB, std::vector<char>::const_iterator endB, size_t numThreads)
{
  std::vector<std::thread*> threads;
  std::vector<std::vector<LocationAndLength>> partitionResults;
  partitionResults.resize(numThreads);
  for(size_t i = 0; i<numThreads; ++i) partitionResults[i].resize(numThreads);
  
  const size_t elementsPerPartitionA = std::distance(beginA, endA) / numThreads;
  const size_t elementsPerPartitionB = std::distance(beginB, endB) / numThreads;
  const size_t remainderA = std::distance(beginA, endA) % numThreads;
  const size_t remainderB = std::distance(beginB, endB) % numThreads;

  std::vector<char>::const_iterator partitionBeginA = beginA;
  std::vector<char>::const_iterator partitionEndA = beginA + elementsPerPartitionA;
  for (size_t i = 0; i < numThreads; ++i)
  {
    std::vector<char>::const_iterator partitionBeginB = beginB;
    std::vector<char>::const_iterator partitionEndB = beginB + elementsPerPartitionB;
    for (size_t j = 0; j < numThreads; ++j)
    {
      threads.push_back(new std::thread(findLongestMatchingSequence, &partitionResults[i][j], partitionBeginA, partitionEndA, partitionBeginB, partitionEndB ));
      partitionBeginB = partitionEndB;
      partitionEndB += elementsPerPartitionB;
      if(j == (numThreads -2))
      {
        partitionEndB += remainderB;
      }
    }
    partitionBeginA = partitionEndA;
    partitionEndA += elementsPerPartitionA;
    if(i == (numThreads -2))
    {
      partitionEndA += remainderA;
    }
  }
  
// Wait for the threads to complete (main thread will block)
  //size_t total = 0;
  LocationAndLength res;
  res.length = 0;
  for (size_t i = 0; i < numThreads*numThreads; ++i) threads[i]->join();

  for (size_t i = 0; i < numThreads; ++i)
  {
    for (size_t j = 0; j < numThreads; ++j)
    {
      if(partitionResults[i][j].length > res.length)
      {
        res.length = partitionResults[i][j].length;
        res.locationA = (i*elementsPerPartitionA)+ partitionResults[i][j].locationA;
        res.locationB = (j*elementsPerPartitionB)+ partitionResults[i][j].locationB;
      }
    } 
  }
  return res;
}

int main(int argc, char* argv[])
{
  std::cout << std::endl;
  std::cout << " -- Machine has " << std::thread::hardware_concurrency() << " CPU cores --" << std::endl;
  std::cout << std::endl;

  Sequence strandA, strandB;
  initializeDataSet(strandA, 100000, 1);
  initializeDataSet(strandB, 100000, 2);
  //strandA = {'A','A','C','G','B','C','T','D'};
  //strandB = {'D','C','G','B','C','T','D','A'};

  const auto startTime = std::chrono::high_resolution_clock::now();
///////////serial
  //LocationAndLength result;
  //findLongestMatchingSequence(&result ,strandA.begin(), strandA.end(), strandB.begin(), strandB.end());
//////Parallel
  size_t numThreads = 4;
  cout<<"computing with "<<numThreads<<" threads"<<endl;
  LocationAndLength result = parallel(strandA.begin(), strandA.end(), strandB.begin(), strandB.end(), numThreads);


  const auto endTime = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<double> elapsed = endTime - startTime;

  std::cout << "Sequence was " << result.length << " entries long starting at location A=" << result.locationA << " B=" << result.locationB << std::endl;
  std::cout << "Calculation took " << elapsed.count() << " seconds" << std::endl;
  for (size_t i = 0; i < result.length; ++i)
  {
    if (strandA[result.locationA + i] != strandB[result.locationB + i])
    {
      std::cout << "*** ERROR ***" << std::endl;
      return 1;
    }
    std::cout << strandA[result.locationA + i];
  }
  std::cout << std::endl;

  return 0;
}

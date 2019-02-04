#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>


#define RANDOM_SEED     234587
#define MAX_RANGE_DELTA  10000
#define MAX_NUM_TYPES       32


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


long getMemory() {
  pid_t pid = getpid();
  std::stringstream temp;
  temp << "/proc/" << pid << "/status";
  const std::string statusFileName = temp.str();
  std::ifstream statusFile(statusFileName.c_str());
  std::string word;
  static const std::string VmSize = "VmSize:";
  static const std::string kB = "kB";
  bool found = false;
  while (statusFile.good()) {
    statusFile >> word;
    if (word == VmSize) {
      long long memorySizeInKB;
      if (statusFile >> memorySizeInKB) {
        statusFile >> word;
        if (word == kB) {
          long memory = memorySizeInKB * 1024;
          //std::cout << "returning memory: " << memory << std::endl;
          return memory;
        }
      }
      break;
    }
  }
  //std::cout << "getMemory failed..." << std::endl;
  return 0;
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


double getCpuTime() {
  timespec timeSpec;
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &timeSpec);
  static double absoluteStartCpuTime_ = -1;
  if (absoluteStartCpuTime_ == -1) {
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &timeSpec);
    absoluteStartCpuTime_ = (double)timeSpec.tv_sec + (double)timeSpec.tv_nsec / (double)1000000000.0;
  }
  const double highResulutionCpuTime = ((double)timeSpec.tv_sec + (double)timeSpec.tv_nsec / (double)1000000000.0) - absoluteStartCpuTime_;
  return highResulutionCpuTime;
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


int getNumIterationsForDataSetIndex(const int dataSetIndex) {
  //int multiplier = 10;
  int multiplier = 1;
  if (dataSetIndex == 1) {
    return 100000 * multiplier;
  } else if (dataSetIndex == 2) {
    return 10 * multiplier;
  } else {
    return 1 * multiplier;
  }
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


template <class T>
void generateDataSet(const int dataSetIndex, T& storage) {
  int low, high;
  short type;
  int numRanges = 0;
  if (dataSetIndex == 1) {
    numRanges = 100;
  } else if (dataSetIndex == 2) {
    numRanges = 100000;
  } else {
    numRanges = 10000000;
  }
  for (int i = 0; i < numRanges; ++i) {
    low  = rand();
    high = (rand() % MAX_RANGE_DELTA) + low;
    type = (rand() % MAX_NUM_TYPES);
    if (low > high) continue;
    storage.addRange(low, high, type);
  }

  /*storage.addRange(2, 5, 0);
  storage.addRange(4, 8, 0);
  storage.addRange(6, 14, 0);
  storage.addRange(30, 34, 0);
  storage.addRange(20, 26, 1);
  storage.addRange(12, 22, 1);*/
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


inline long verifyRange(const int low, const int high) {
  return (long)low + (long)high;
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


#endif


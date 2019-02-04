#include <homework.h>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

////call as:  /pkgs/gcc/4.8.1/bin/g++ -std=c++11 -I. -lrt -O3 -o range range_matching_data_models.cpp
class Range {
  int l;
  int h;
  short t;
  
public:
  Range(const int low, const int high, const short type){
    l = low;
    h = high;
    t = type;
  }
  
  bool operator < (const Range& rs) const {
    if(this->l < rs.l){
      return 1;
    }else{
      return 0;
    }
  }
  
  int getLow() const {
    return l;
  }
  
  int getHigh() const {
    return h;
  }
  
  int getDelta() const { getHigh() - getLow(); }
  
  short getType() const {
    return t;
  }
  
  bool isTouching(const Range& rs) const {
    if(this->l <= rs.h && rs.l <= this->h){
      return 1;
    }else{
      return 0;
    }
  } 
};


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


class Storage {
  
  // TODO: Fill in the member variable details of the storage class
  vector<Range> ranges_;
  
public:
  Storage() {}
  ~Storage() {}
  
  void clear() {
    ranges_.clear();
  }
  
  void addRange(const int low, const int high, const short type) {
    Range r1(low, high, type);
    ranges_.push_back(r1);
  }
  
  void calculateTouchingSameTypeRangePairs(std::vector<std::pair<Range, Range> >& ranges);
  void calculateTouchingDifferentTypeRangePairs(std::vector<std::pair<Range, Range> >& ranges);
};


void Storage::calculateTouchingSameTypeRangePairs(std::vector<std::pair<Range, Range> >& ranges) {
  sort(ranges_.begin(), ranges_.end());
  for(int i = 0; i < ranges_.size(); ++i){
    for(int j = i+1; j<ranges_.size(); ++j){
      if(ranges_[i].getType() == ranges_[j].getType()){
        if(ranges_[i].isTouching(ranges_[j])){
          ranges.push_back(make_pair(ranges_[i], ranges_[j]));
          ranges.push_back(make_pair(ranges_[j], ranges_[i]));
        }
        else{
          break;
        } 
      }
    }
  }
}

void Storage::calculateTouchingDifferentTypeRangePairs(std::vector<std::pair<Range, Range> >& ranges) {
  sort(ranges_.begin(), ranges_.end());
   for(int i = 0; i < ranges_.size(); ++i){
    for(int j = i+1; j<ranges_.size(); ++j){
      if(ranges_[i].getType() != ranges_[j].getType()){
        if(ranges_[i].isTouching(ranges_[j])){
          ranges.push_back(make_pair(ranges_[i], ranges_[j]));
          ranges.push_back(make_pair(ranges_[j], ranges_[i]));
        }
        else if(!(ranges_[i].isTouching(ranges_[j]))){
          break;
        } 
      }
    }
  }
}



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
//
// Do not change anything below this point!!!
//
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


long runDataSet(int dataSetIndex, Storage& storage) {
  
  long answer = 0;
  
  const int numIterations = getNumIterationsForDataSetIndex(dataSetIndex);
  std::vector<std::pair<Range, Range> > rangePairs;
  double startTime = 0;
  for (int iterationNumber = 0; iterationNumber < numIterations; ++iterationNumber) {
    if (dataSetIndex == 2) {
      startTime = getCpuTime();
      //std::cout << "  Starting iteration: " << iterationNumber << " at totalCpuTime: " << getCpuTime() << std::endl;
    }
    
    storage.clear();
    generateDataSet(dataSetIndex, storage);
    
    rangePairs.clear();
    storage.calculateTouchingSameTypeRangePairs(rangePairs);
    for (size_t i = 0; i < rangePairs.size(); ++i) {
      //std::cout << "  Found range pair " << i << " : " << rangePairs[i].first.getLow() << ":" << rangePairs[i].first.getHigh() << ", " << rangePairs[i].second.getLow() << ":" << rangePairs[i].second.getHigh() << " same" << std::endl;
      answer += verifyRange(rangePairs[i].first.getLow(), rangePairs[i].first.getHigh());
      answer += verifyRange(rangePairs[i].second.getLow(), rangePairs[i].second.getHigh());
    }
    
    rangePairs.clear();
    storage.calculateTouchingDifferentTypeRangePairs(rangePairs);
    for (size_t i = 0; i < rangePairs.size(); ++i) {
      //std::cout << "  Found range pair " << i << " : " << rangePairs[i].first.getLow() << ":" << rangePairs[i].first.getHigh() << ", " << rangePairs[i].second.getLow() << ":" << rangePairs[i].second.getHigh() << " different" << std::endl;
      answer += verifyRange(rangePairs[i].first.getLow(), rangePairs[i].first.getHigh());
      answer += verifyRange(rangePairs[i].second.getLow(), rangePairs[i].second.getHigh());
    }
    
    if (dataSetIndex == 2) {
      double iterationTime = getCpuTime() - startTime;
      //std::cout << "  Finished iteration: " << iterationNumber << " took: " << iterationTime << " seconds with totalCpuTime: " << getCpuTime() << std::endl;
    }
  }
  
  return answer;
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


int main (int argc, char* argv[]) {
  std::cout << "Starting homework..." << std::endl;
  const double absoluteStartTime   = getCpuTime();
  const long   absoluteStartMemory = getMemory();
  long maxMemory = 0;
  
  srand(RANDOM_SEED);
  //const int maxDataSetNumber = 1;
  //const int maxDataSetNumber = 2;
  const int maxDataSetNumber = 3;
  for (int i = 1; i <= maxDataSetNumber; ++i) {
    std::cout << "  Starting data set #" << i << std::endl;
    const double startTime   = getCpuTime();
    const double startMemory = getMemory();
    
    Storage storage;
    const long answer = runDataSet(i, storage);
    
    const double time = getCpuTime() - startTime;
    const long memory = getMemory() - startMemory;
    maxMemory = std::max(maxMemory, memory);
    std::cout << "  Finished data set #" << i << " with answer: " << answer << " took: " << time << " seconds and " << memory << " bytes" << std::endl;
  }
  
  const double totalTime   = getCpuTime() - absoluteStartTime;
  const long   totalMemory = maxMemory - absoluteStartMemory;
  std::cout << "Finished homework took: " << totalTime << " seconds and added " << totalMemory << " bytes" << std::endl;
  return 0;
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

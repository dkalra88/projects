#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include <math.h>
#include <utility>

using namespace std;

static float total_distance_travelled = 0;

size_t const BBOX_SIZE  = 1000;
size_t const N = 6; // try 4 teams, 10 teams, 100 teams
int M = N; 

float calc_dist_btw_teams(pair<int,int> const & A, pair<int,int> const & B) { 
float	dist = sqrt(pow((A.first-B.first),2) + pow((A.second-B.second),2));
//		cout<<dist<<endl;
		return dist;
}

void rotate_teams(array<pair<size_t,size_t>, N> & a){ //function to rotate the array of teams
	pair<size_t,size_t> temp = a[N-1];
	int i;
  for (i = N-1; i > 1; --i){
		a[i] = a[i-1];
  }
  a[1] = temp;
}

void print_teams(array<pair<size_t,size_t>, N> & teams_pos){
	for(size_t i =0; i<N; ++i){
		cout<<teams_pos[i].first<<","<<teams_pos[i].second<<endl;
	}
}

void schedule_game(array<pair<size_t,size_t>, N> & a, int M,	array<pair<int,int>, N> const & location ){ //function to schedule game such that each team plays with each other team
	for (int j=0; j<M-1; ++j){
		cout<<"Day"<<j<<":"<<endl;
		cout<<a[0].first<<","<<a[0].second<<" AND "<<a[1].first<<","<<a[1].second<<endl;
		total_distance_travelled += calc_dist_btw_teams(location[a[1].second], location[a[0].second]);
    a[1].second = a[0].second;
			for(int i=2; i<=M/2;++i){
				cout<<a[i].first<<","<<a[i].second<<" AND "<<a[M-(i-1)].first<<","<<a[M-(i-1)].second<<endl;
        if(a[i].second != a[i].first){
           total_distance_travelled += calc_dist_btw_teams(location[a[i].second], location[a[i].first]);
           a[i].second = a[i].first;
        }
			total_distance_travelled += calc_dist_btw_teams(location[a[M-(i-1)].second], location[a[i].second]);
        a[M-(i-1)].second = a[i].second;
			}
			rotate_teams(a);
	}
//  cout<<"finally teams are:"<<endl;
//  print_teams(a);
  for(int i =1; i<N; ++i){
if(a[i].second != a[i].first){
           total_distance_travelled += calc_dist_btw_teams(location[a[i].second], location[a[i].first]);
           a[i].second = a[i].first;
        }
  }
// cout<<"after update teams are:"<<endl;
//  print_teams(a);

}

int main(void)
{
	srand(13);
	array<pair<int,int>, N> location;
	for(size_t i =0; i<N; ++i){
		location[i]= make_pair((rand()%BBOX_SIZE),(rand()%BBOX_SIZE));
//		cout<<location[i].first<<","<<location[i].second<<endl;
	}

  array<pair<size_t,size_t>, N> teams_pos;
	for(size_t i =0; i<N; ++i){
		teams_pos[i]= make_pair(i,i);
//		cout<<teams_pos[i].first<<","<<teams_pos[i].second<<endl;
	}

  schedule_game(teams_pos, M, location);
cout<<total_distance_travelled<<endl;

	return 0;
}

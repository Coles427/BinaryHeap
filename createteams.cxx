#include <iostream>
#include <cmath>
#include <vector>

#include "teamdata.h"
#include "json.hpp"

std::pair<int, int> findBestTeam(TeamData teams){
    double ideal = 50.00;
    double best = 100.00;
    std::pair<int, int>team;

    for (auto &winPercentage : teams.winPercentages_) {
        if(std::abs(ideal - winPercentage.second.begin()->second) < std::abs(ideal - best)){
            best = winPercentage.second.begin()->second;
            std::pair<int,  int> tempP = std::make_pair(winPercentage.first, winPercentage.second.begin()->first);
            team.swap(tempP);
        }
    }

    for(auto itr = teams.winPercentages_.begin(); itr != teams.winPercentages_.end(); ++itr){
        if((itr->first == team.first || itr->first == team.second)|| (itr->second.begin()->first == team.first || itr->second.begin()->first == team.second))
        teams.winPercentages_.erase(itr);
    }

    return team;
};

int main(int argc, char** argv) {


    TeamData teams(argv[1]);
    nlohmann::json lineUps;
    int numTeams = 0;
    while ( numTeams < teams.numPlayers()/2){
        
    }


    //std::cout<<"Team one is: player "<<team1.first<<" and player "<<team1.second<< " with a win % of "<<best;
}

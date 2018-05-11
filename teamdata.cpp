#include <fstream>
#include "teamdata.h"
#include "json.hpp"

TeamData::TeamData(std::string file_name) {
    std::fstream file;
    file.open(file_name);
    nlohmann::json teamJson;

    if(file.is_open()){
       file>>teamJson;
    }
    file.close();

    numPlayers_ = teamJson["metadata"]["numPlayers"];

    for(auto itr = teamJson["teamStats"].begin(); itr!= teamJson["teamStats"].end(); ++itr){
        int playerOne = itr.value()["playerOne"];
        int playerTwo = itr.value()["playerTwo"];
        double winPercentage = itr.value()["winPercentage"];
        winPercentages_[playerOne][playerTwo] = winPercentage;
    }
}

int TeamData::numPlayers() const {
    return numPlayers_;
}

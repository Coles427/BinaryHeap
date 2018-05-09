#include "json.hpp"
#include <fstream>
#include <iostream>
#include "priorityqueue.h"

void doOp(Key key, std::string operation, PriorityQueue &queue){
    if (operation == "insert"){
        queue.insert(key);
    }
    else if (operation == "min"){
        queue.min();
    }
    else if (operation == "removeMin"){
        queue.removeMin();
    }
    else if (operation == "isEmpty"){
        queue.isEmpty();
    }
    else if (operation == "size"){
        queue.size();
    }
}

void printQueue(PriorityQueue queue, size_t maxSize,int numOps ) {
    nlohmann::json jsonQueue;

    for (size_t i = 1 ; i < queue.size(); i++){
        jsonQueue[std::to_string(i)]["key"] = queue.getKey(i);
        if(i != 1){jsonQueue[std::to_string(i)]["parent"] = i/2;}
        if (i*2 <= queue.size()) {
            jsonQueue[std::to_string(i)]["leftChild"] = i * 2;
        }
        if (i*2 + 1 <= queue.size()) {
            jsonQueue[std::to_string(i)]["rightChild"] = i * 2 + 1;
        }
        jsonQueue[std::to_string(i)]["value"] = queue.getValue(i);
    }

    jsonQueue["metadata"]["maxHeapSize"] = maxSize;

    std::cout<< jsonQueue.dump(2);
}

int main(int argc, char** argv) {
    nlohmann::json heapBuild;


    std::fstream file;
    file.open(argv[1]);
    if(file.is_open()){
        file>>heapBuild;
    }
    file.close();
    size_t maxSize =heapBuild["metadata"]["maxHeapSize"];
    PriorityQueue queue(maxSize);

    for(auto itr = heapBuild.begin(); itr != heapBuild.end(); ++itr){
        Key key;
        if (itr.key() != "metadata") {

            auto isKey = itr.value().find("key");
            if (isKey != itr.value().end()) {
                key = itr.value()["key"];
            }
            std::string operation = itr.value()["operation"];
            doOp(key, operation, queue);

        }
    }
    int numOps = heapBuild["metadata"]["numOperations"];
    printQueue(queue, maxSize, numOps);

}

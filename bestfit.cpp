#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include<list>
#include <sstream>
#include <iostream>
#include <string>

struct allocation {
    size_t fixedSize; //rounded size (32,64,128,256,512)
    size_t inputSize; //input size given by user
    void *space;
};
void* alloc(size_t chunk_size);
void dealloc(void* chunk);
std::list<allocation> allocatedList;
std::list<allocation> freeList;

int main(int argc, char *argv[]){
    if(argc == 2){
        std::string fileName = argv[1];
        std::ifstream inFS;
        inFS.open(fileName);
        if(!inFS.is_open()){
            std::cout << "Sorry could not open file, try in this format ./bestfit <filename>" <<std::endl;
            return 0;
        }
        std::string input;
        while(std::getline(inFS,input)){
            std::istringstream inSS(input);
            std::string command;
            int size;
            inSS >> command;
            inSS >> size;
            if(command == "alloc:"){
                alloc(size);
            }
            else if(command == "dealloc"){
                if(allocatedList.empty()){
                    std::cout << "Sorry, allocated list is empty, allocate before deallocating" <<std::endl;
                    return 0;
                }
                else{
                    void* lastAllocated = allocatedList.back().space;
                    dealloc(lastAllocated);
                }
            }
        }
        inFS.close();
    }
    else{
        std::cout << "Invalid input" <<std::endl;
        return 0;
    }
    std::cout << "Allocated List: " <<std::endl;
    for(allocation &item: allocatedList){
        std::cout << "Address: "<< item.space << " total size: " << item.fixedSize << " used size: " << item.inputSize << std::endl;
    }
    std::cout << "Free List: "<<std::endl;
    for(allocation &item: freeList){
        std::cout << "Address: "<< item.space << " total size: " << item.fixedSize << std::endl;
    }
    return 0;
}


void* alloc(size_t chunk_size){

    size_t roundedSize;
    if(chunk_size<=32){
        roundedSize = 32;
    }
    else if(chunk_size <=64){
        roundedSize = 64;
    }
    else if(chunk_size <= 128){
        roundedSize = 128;
    }
    else if(chunk_size<= 256){
        roundedSize = 256;
    }
    else if(chunk_size <= 512){
        roundedSize = 512;
    }
    else{
        return nullptr;
    }
    auto current = freeList.end();  
    for (auto it = freeList.begin(); it != freeList.end(); ++it) {
        if (it->fixedSize >= roundedSize) {
            if (current == freeList.end() || it->fixedSize < current->fixedSize) {
                current = it;  
            }
        }
    }

    if (current != freeList.end()) {
       
        void* ptr = current->space;
        allocatedList.push_back({current->fixedSize, chunk_size, ptr});
        freeList.erase(current);  
        return ptr;
    }


    void* ptr = sbrk(roundedSize);
    if (ptr == (void*) -1) {
        std::cout << "Issue accessing the os memory" << std::endl;
        return nullptr;
    }
    allocatedList.push_back({roundedSize,chunk_size,ptr});
    return ptr;
}

void dealloc(void* chunk){
    for(auto it = allocatedList.begin(); it != allocatedList.end(); ++it){
        if(it->space == chunk){
            it->inputSize = 0;
            freeList.push_back(*it);
            allocatedList.erase(it);
            return;
        }
    }
}
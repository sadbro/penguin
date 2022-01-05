
#ifndef __UTIL_H
#define __UTIL_H

std::map<std::string, vector> default_kinetics(){

    std::map<std::string, vector> k = { {"position", vector()},
                                   {"velocity", vector()},
                                   {"acceleration", vector()} };

    return k;
}

void printMap(std::map<std::string, vector> m){

        for (auto &item : m) {
            std::cout << item.first << ": ";
            item.second.print();
    }
}

#endif

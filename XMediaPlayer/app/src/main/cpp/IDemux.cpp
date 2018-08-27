//
// Created by developer on 2018/8/27.
//

#include "IDemux.h"

void IDemux::main() {
    while (!isExit){
        AVData data = readMediaData();
        if(data.size>0){
            notifyObserver(data);
        }
    }
}
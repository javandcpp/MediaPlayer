//
// Created by developer on 2018/8/27.
//

#include "IObserver.h"
using namespace std;

void IObserver::addObserver(IObserver *observers) {
    std::lock_guard<std::mutex> lock(mutex);
    observerlist.push_back(observers);

}

void IObserver::notifyObserver(AVData data) {
    std::lock_guard<std::mutex> lock(mutex);
    for (int i = 0; i < observerlist.size(); ++i) {
        observerlist[i]->notifyObserver(data);
    }
}

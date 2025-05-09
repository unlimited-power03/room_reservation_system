#include "session_manager.h"

int session_manager::id=-1;

int session_manager::getIdOfCurrentlyLoggedUser(){
    return id;
}

void session_manager::setIdOfCurrentlyLoggedUser(const int index){
    id=index;
}

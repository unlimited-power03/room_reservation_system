#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

class session_manager
{
    static int id;
public:
    int getIdOfCurrentlyLoggedUser();
    void setIdOfCurrentlyLoggedUser(const int index);
};

#endif // SESSION_MANAGER_H

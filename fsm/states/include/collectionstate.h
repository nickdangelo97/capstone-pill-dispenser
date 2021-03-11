#ifndef COLLECTIONSTATE_H
#define COLLECTIONSTATE_H

#include "state.h"

class CollectionState : public State
{
    
public:
    CollectionState();
    ~CollectionState();

protected:
    void run(void *argument) override;

};

#endif /* COLLECTIONSTATE_H */

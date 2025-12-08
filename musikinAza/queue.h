#ifndef queue_h
#define queue_h

#include "song.h"

typedef struct elmQueue* addressQueue;

struct elmQueue {
    Song info;
    addressQueue next;
};

struct PlayQueue {
    addressQueue head;
    addressQueue tail;
};

void createQueue(PlayQueue &Q);
void enqueueSong(PlayQueue &Q, Song s);
void dequeueSong(PlayQueue &Q, Song &s);
void showQueue(PlayQueue Q);
bool isQueueEmpty(PlayQueue Q);

#endif

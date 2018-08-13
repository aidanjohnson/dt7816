/*
 * RingBuf.h - Library for implementing a simple Ring Buffer on Arduino boards.
 * Created by D. Aaron Wisner (daw268@cornell.edu)
 * January 17, 2015.
 * Released into the public domain.
 * 
 * Modifications made from original
 * Aidan Johnson (johnsj96@uw.edu)
 * 29 June 2018
 * 
*/

#ifndef RingBuf_h
#define RingBuf_h

#include <stdint.h>

#ifndef __cplusplus
#ifndef bool
    #define bool uint8_t
#endif
#endif

#define RB_ATOMIC_START {
#define RB_ATOMIC_END }
#warning "Operations on the buffer in ISRs are not safe!"
#warning "Impliment RB_ATOMIC_START and RB_ATOMIC_END macros for safe ISR operation!"


typedef struct RingBuf RingBuf;

typedef struct RingBuf
{
  // Invariant: end and start is always in bounds
  unsigned char *buf;
  unsigned int len, size, start, end, elements;

  // Private:
  int (*next_end_index) (RingBuf*);
  int (*incr_end_index) (RingBuf*);

  int (*incr_start_index) (RingBuf*);

  //public:
  // Returns true if full
  bool (*isFull) (RingBuf*);
  // Returns true if empty
  bool (*isEmpty) (RingBuf*);
  // Returns number of elemnts in buffer
  unsigned int (*numElements)(RingBuf*);
  // Add Event, Returns index where added in buffer, -1 on full buffer
  int (*add) (RingBuf*, const void*);
  // Returns pointer to nth element, NULL when nth element is empty
  void *(*peek) (RingBuf*, unsigned int);
  // Removes element and copies it to location pointed to by void *
  // Returns pointer passed in, NULL on empty buffer
  void *(*pull) (RingBuf*, void *);

} RingBuf;

#ifdef __cplusplus
extern "C" {
#endif

RingBuf *RingBuf_new(int size, int len);
int RingBuf_init(RingBuf *self, int size, int len);
int RingBuf_delete(RingBuf *self);

int RingBufNextEndIndex(RingBuf *self);
int RingBufIncrEnd(RingBuf *self);
int RingBufIncrStart(RingBuf *self);
int RingBufAdd(RingBuf *self, const void *object);
void *RingBufPeek(RingBuf *self, unsigned int num);
void *RingBufPull(RingBuf *self, void *object);
bool RingBufIsFull(RingBuf *self);
bool RingBufIsEmpty(RingBuf *self);
unsigned int RingBufNumElements(RingBuf *self);

#ifdef __cplusplus
}
#endif

#endif

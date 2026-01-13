#pragma once

typedef bool (*fsm_event_quadrant)(void);

typedef enum {
  IDLE,
  QUADRANT_1,
  QUADRANT_2,
  QUADRANT_3,
  QUADRANT_4
} fsm_state_quadrant_t;

typedef struct {
  fsm_state_quadrant_t next_state,
  fsm_event_quadrant event
} fsm_event_transition_t;

bool isQuadrant1(void);
bool isQuadrant2(void);
bool isQuadrant3(void);
bool isQuadrant4(void);


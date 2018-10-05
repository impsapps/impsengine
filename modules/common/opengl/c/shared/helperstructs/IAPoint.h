#ifndef IAPoint_h
#define IAPoint_h

typedef struct{
    float x;
    float y;
} IAPoint;

static const IAPoint IAPoint_zero = {.x = 0.0f, .y = 0.0f};
static const IAPoint IAPoint_one = {.x = 1.0f, .y = 1.0f};

IAPoint IAPoint_make(float x, float y);

bool IAPoint_isEqual(IAPoint p1, IAPoint p2);

#endif

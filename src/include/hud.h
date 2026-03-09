#include <raylib.h>

/* Work in Progress, don't worry about this */

typedef enum {
    DIALOGUE,
    EQUIPPED,
    HEALTH,
    /* One enum entry for each hud unit */
    /* Currency, Other resource bars, etc. */
} HudType;

typedef struct {
    HudType type;
} HudUnit;

void hud_draw_unit(HudUnit *unit);

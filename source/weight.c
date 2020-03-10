
#include "weight.h"

unsigned long packing = 0;
unsigned long weight = 0;

void read_pack()
{
    packing = hx711_transform() / RATIO;
}

void read_weight()
{
    display_string(1, 5, "Weighting");
    display_string(2, 4, "Now");
    display_string(2, 13, "G");

    weight = hx711_transform() / RATIO;

    weight = weight - packing;
    weight = weight - weight * CORRECT;
    
    if (weight > 8200) {
        weight = 0;
        read_pack();
    }
    display_value(2, 8, "%d", weight);     
}

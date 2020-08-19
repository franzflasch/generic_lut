#include <stdio.h>
#include <stdint.h>

#define ARRAY_LENGTH(array) (sizeof((array))/sizeof((array)[0]))

typedef struct lut_struct
{
        int16_t x;
        int16_t y;

} lut_td;

lut_td height_sensor_curve_lut[] = {
        { -45, -2000 },
        { -35, -2000 },
        { -20,     0 },
        {   0,  1000 },
        {  20,  1800 },
        {  35,  2000 },
        {  45,  2000 },
};

int16_t lut_lookup(lut_td* lut, int16_t input, int16_t *result, int16_t len)
{
    int16_t ret_val = 0;
    int16_t i;

    for (i = 0; i < len; i++)
    {
        /* check if input is less than lowest value in lut */
        if(input < lut[0].x)
        {
            *result = lut[0].y;
            break;
        }
        
        /* check if input higher than highest value in lut */
        if(input > lut[len-1].x)
        {
            *result = lut[len-1].y;
            break;
        }

        /* check if input is exact value in lut - no interpolation needed */
        if(input == lut[i].x)
        {
            *result = lut[i].y;
            break;
        }
        /* check if input is inbetween two values and interpolate */
        else if((input < lut[i+1].x) && (input > lut[i].x))
        {
            int16_t diffx = input - lut[i].x;
            int16_t diffn = lut[i].x - lut[i+1].x;
            *result = (lut[i].y + (lut[i].y - lut[i+1].y) * diffx / diffn);
            break;
        }
    }
    if(i >= len)
        ret_val = -1;
    
    return ret_val;
}

int main()
{
    int16_t lut_res = 0;
    lut_lookup(height_sensor_curve_lut, 25, &lut_res, ARRAY_LENGTH(height_sensor_curve_lut));
    printf("Hello World %d", lut_res);

    return 0;
}

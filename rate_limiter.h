/*
 * rate_limiter.h
 *
 * Created: 2/11/2018 9:47:40 AM
 *  Author: arin
 */ 


#ifndef RATE_LIMITER_H_
#define RATE_LIMITER_H_


#include <stdint.h>


/******************************************************************************
* Defines
******************************************************************************/
typedef struct
{
	float up_limit_slope;
	float dn_limit_slope;
	
	float last_output;
	uint32_t last_time_tick;
} rate_limiter_inst_t;


/******************************************************************************
* Prototypes
******************************************************************************/
float rate_lim(rate_limiter_inst_t *inst, uint32_t current_time_tick, float input);
void rate_lim_calc_slope(rate_limiter_inst_t *inst, float max, float min, uint32_t up_time, uint32_t dn_time);


#endif /* RATE_LIMITER_H_ */
/*
 * rate_limiter.h
 *
 * Created: 2/11/2018 9:47:40 AM
 *  Author: arin
 */ 


#ifndef RATE_LIMITER_H_
#define RATE_LIMITER_H_


#include <stdint.h>


/**************************************************************************************************
*                                             DEFINES
*************************************************^************************************************/
typedef struct rate_limiter_inst_t
{
	float up_limit_slope;
	float dn_limit_slope;
	
	float last_output;
	uint32_t last_time_tick;
} rate_limiter_inst_t;


/**************************************************************************************************
*                                            PROTOTYPES
*************************************************^************************************************/
float rate_lim           (rate_limiter_inst_t * const inst, const uint32_t current_time_tick, const float input);
void  rate_lim_calc_slope(rate_limiter_inst_t * const inst, const float max, const float min, const uint32_t up_time, const uint32_t dn_time);
void  rate_lim_reset     (rate_limiter_inst_t * const inst, const uint32_t current_time_tick, const float input);


#endif /* RATE_LIMITER_H_ */

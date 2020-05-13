/*
 * rate_limiter.c
 *
 * Created: 2/11/2018 9:47:54 AM
 *  Author: arin
 */ 


#include "rate_limiter.h"


/**************************************************************************************************
*                                            FUNCTIONS
*************************************************^************************************************/
/******************************************************************************
*  \brief Rate limit
*
*  \note https://www.mathworks.com/help/simulink/slref/ratelimiter.html
******************************************************************************/
float rate_lim(rate_limiter_inst_t * const inst, const uint32_t current_time_tick, const float input)
{
	float err;
	float slope;
	float output;
	float dt;
	
	/*Get dt*/
	dt = (float)current_time_tick - (float)inst->last_time_tick;
	
	/*Record timestamp*/
	inst->last_time_tick = current_time_tick;
	
	/*dt of zero uses the last output*/
	if(dt == 0)
	{
		output = inst->last_output;
	}
	
	/*Calculate rate limited output*/
	else
	{
		err = input - inst->last_output;

		slope = err / dt;

		//up rate limit
		if((slope > inst->up_limit_slope) && (inst->up_limit_slope != 0))
		{
			output = dt * inst->up_limit_slope + inst->last_output;
		}
		//down rate limit
		else if((slope < inst->dn_limit_slope) && (inst->dn_limit_slope != 0))
		{
			output = dt * inst->dn_limit_slope + inst->last_output;
		}
		//within limits
		else
		{
			output = input;
		}
	}
	
		inst->last_output = output;

	return output;
}

/******************************************************************************
*  \brief Calculate slope
*
*  \note run this any time max, min, up_time or dn_time changes.
*
*        This function calculates the slope up and down if these values are
*        zero then slew_rate_limit will consider that to be no slope.
******************************************************************************/
void rate_lim_calc_slope(rate_limiter_inst_t * const inst, const float max, const float min, const uint32_t up_time, const uint32_t dn_time)
{
	float rise;
	
	rise = max - min;
	
	/****UP****/
	if(up_time != 0)
	{
		inst->up_limit_slope = rise / (float)up_time;
	}
	else
	{
		/*if ramp time zero then slope is zero which means no ramping*/
		inst->up_limit_slope = 0;
	}
	
	/****DN****/
	if(dn_time != 0)
	{
		inst->dn_limit_slope = -rise / (float)dn_time;
	}
	else
	{
		/*if ramp time zero then slope is zero which means no ramping*/
		inst->dn_limit_slope = 0;
	}
	
	/*Verify last output is within max and min*/
	if(inst->last_output < min)
		inst->last_output = min;
		
	if(inst->last_output > max)
		inst->last_output = max;
}

/******************************************************************************
*  \brief Reset ramp
*
*  \note run this to force the ramp to a specified value.
******************************************************************************/
void rate_lim_reset(rate_limiter_inst_t * const inst, const uint32_t current_time_tick, const float input)
{
	/*Record timestamp*/
	inst->last_time_tick = current_time_tick;
	
	/*Set last output to input*/
	inst->last_output = input;
}

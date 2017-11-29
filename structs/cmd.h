/*
 * GENERATED AUTOMATICALLY DO NOT FIX
 * 2017-11-29 16:45:19
 */

#ifndef CMD_H
#define CMD_H


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#include "cbor.h"

#include "types.h"

#include "common.h"
#include "debug.h"
#include "cmd_data_debug.h"
#include "cmd_data_rnd.h"
#include "cmd_data_packer.h"
#include "cmd_handler.h"
#include "cmd_data.h"
#include "cmd.h"

#define UNDEFINED_SIZE 2
#define STREAM_DATA_SIZE (1024*32)

#define PGAS_CMD_MAX 36
#define SKGP_CMD_MAX 13
#define PU_CMD_MAX 15
extern cmd_t pgas_cmd[];
extern cmd_t skgp_cmd[];
extern cmd_t pu_cmd[];

#endif


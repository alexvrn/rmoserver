/*
 * GENERATED AUTOMATICALLY DO NOT FIX
 * 2017-11-29 16:45:19
 */

#ifndef CMD_DATA_PACKER_H
#define CMD_DATA_PACKER_H


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
#include "cmd_handler.h"
#include "cmd_data.h"
#include "cmd.h"

#define UNDEFINED_SIZE 2
#define STREAM_DATA_SIZE (1024*32)

 /*int cmd_data0_pack(cbor_stream_t* stream, cmd_data0_t* cmd_data);
 int cmd_data0_unpack(cbor_stream_t* stream, size_t* offset, cmd_data0_t* cmd_data);
 int cmd_data2_pack(cbor_stream_t* stream, cmd_data2_t* cmd_data);
 int cmd_data2_unpack(cbor_stream_t* stream, size_t* offset, cmd_data2_t* cmd_data);
 int cmd_data5_pack(cbor_stream_t* stream, cmd_data5_t* cmd_data);
 int cmd_data5_unpack(cbor_stream_t* stream, size_t* offset, cmd_data5_t* cmd_data);
 int cmd_data8_pack(cbor_stream_t* stream, cmd_data8_t* cmd_data);
 int cmd_data8_unpack(cbor_stream_t* stream, size_t* offset, cmd_data8_t* cmd_data);
 int cmd_data10_pack(cbor_stream_t* stream, cmd_data10_t* cmd_data);
 int cmd_data10_unpack(cbor_stream_t* stream, size_t* offset, cmd_data10_t* cmd_data);
 int cmd_data12_pack(cbor_stream_t* stream, cmd_data12_t* cmd_data);
 int cmd_data12_unpack(cbor_stream_t* stream, size_t* offset, cmd_data12_t* cmd_data);
 int cmd_data16_pack(cbor_stream_t* stream, cmd_data16_t* cmd_data);
 int cmd_data16_unpack(cbor_stream_t* stream, size_t* offset, cmd_data16_t* cmd_data);
 int cmd_data19_pack(cbor_stream_t* stream, cmd_data19_t* cmd_data);
 int cmd_data19_unpack(cbor_stream_t* stream, size_t* offset, cmd_data19_t* cmd_data);
 int cmd_data21_pack(cbor_stream_t* stream, cmd_data21_t* cmd_data);
 int cmd_data21_unpack(cbor_stream_t* stream, size_t* offset, cmd_data21_t* cmd_data);
 int cmd_data24_pack(cbor_stream_t* stream, cmd_data24_t* cmd_data);
 int cmd_data24_unpack(cbor_stream_t* stream, size_t* offset, cmd_data24_t* cmd_data);
 int cmd_data28_pack(cbor_stream_t* stream, cmd_data28_t* cmd_data);
 int cmd_data28_unpack(cbor_stream_t* stream, size_t* offset, cmd_data28_t* cmd_data);
 int cmd_data30_pack(cbor_stream_t* stream, cmd_data30_t* cmd_data);
 int cmd_data30_unpack(cbor_stream_t* stream, size_t* offset, cmd_data30_t* cmd_data);
 int cmd_data31_pack(cbor_stream_t* stream, cmd_data31_t* cmd_data);
 int cmd_data31_unpack(cbor_stream_t* stream, size_t* offset, cmd_data31_t* cmd_data);
 int cmd_data32_pack(cbor_stream_t* stream, cmd_data32_t* cmd_data);
 int cmd_data32_unpack(cbor_stream_t* stream, size_t* offset, cmd_data32_t* cmd_data);
 int cmd_data36_pack(cbor_stream_t* stream, cmd_data36_t* cmd_data);
 int cmd_data36_unpack(cbor_stream_t* stream, size_t* offset, cmd_data36_t* cmd_data);
 int cmd_data38_pack(cbor_stream_t* stream, cmd_data38_t* cmd_data);
 int cmd_data38_unpack(cbor_stream_t* stream, size_t* offset, cmd_data38_t* cmd_data);
 int cmd_data39_pack(cbor_stream_t* stream, cmd_data39_t* cmd_data);
 int cmd_data39_unpack(cbor_stream_t* stream, size_t* offset, cmd_data39_t* cmd_data);
 int cmd_data40_pack(cbor_stream_t* stream, cmd_data40_t* cmd_data);
 int cmd_data40_unpack(cbor_stream_t* stream, size_t* offset, cmd_data40_t* cmd_data);
 int cmd_data43_pack(cbor_stream_t* stream, cmd_data43_t* cmd_data);
 int cmd_data43_unpack(cbor_stream_t* stream, size_t* offset, cmd_data43_t* cmd_data);
 int cmd_data47_pack(cbor_stream_t* stream, cmd_data47_t* cmd_data);
 int cmd_data47_unpack(cbor_stream_t* stream, size_t* offset, cmd_data47_t* cmd_data);
 int cmd_data49_pack(cbor_stream_t* stream, cmd_data49_t* cmd_data);
 int cmd_data49_unpack(cbor_stream_t* stream, size_t* offset, cmd_data49_t* cmd_data);
 int cmd_data50_pack(cbor_stream_t* stream, cmd_data50_t* cmd_data);
 int cmd_data50_unpack(cbor_stream_t* stream, size_t* offset, cmd_data50_t* cmd_data);
 int cmd_data54_pack(cbor_stream_t* stream, cmd_data54_t* cmd_data);
 int cmd_data54_unpack(cbor_stream_t* stream, size_t* offset, cmd_data54_t* cmd_data);
 int cmd_data58_pack(cbor_stream_t* stream, cmd_data58_t* cmd_data);
 int cmd_data58_unpack(cbor_stream_t* stream, size_t* offset, cmd_data58_t* cmd_data);
 int cmd_data60_pack(cbor_stream_t* stream, cmd_data60_t* cmd_data);
 int cmd_data60_unpack(cbor_stream_t* stream, size_t* offset, cmd_data60_t* cmd_data);
 int cmd_data61_pack(cbor_stream_t* stream, cmd_data61_t* cmd_data);
 int cmd_data61_unpack(cbor_stream_t* stream, size_t* offset, cmd_data61_t* cmd_data);
 int cmd_data65_pack(cbor_stream_t* stream, cmd_data65_t* cmd_data);
 int cmd_data65_unpack(cbor_stream_t* stream, size_t* offset, cmd_data65_t* cmd_data);
 int cmd_data69_pack(cbor_stream_t* stream, cmd_data69_t* cmd_data);
 int cmd_data69_unpack(cbor_stream_t* stream, size_t* offset, cmd_data69_t* cmd_data);
 int cmd_data71_pack(cbor_stream_t* stream, cmd_data71_t* cmd_data);
 int cmd_data71_unpack(cbor_stream_t* stream, size_t* offset, cmd_data71_t* cmd_data);
 int cmd_data78_pack(cbor_stream_t* stream, cmd_data78_t* cmd_data);
 int cmd_data78_unpack(cbor_stream_t* stream, size_t* offset, cmd_data78_t* cmd_data);
 int cmd_data82_pack(cbor_stream_t* stream, cmd_data82_t* cmd_data);
 int cmd_data82_unpack(cbor_stream_t* stream, size_t* offset, cmd_data82_t* cmd_data);
 int cmd_data86_pack(cbor_stream_t* stream, cmd_data86_t* cmd_data);
 int cmd_data86_unpack(cbor_stream_t* stream, size_t* offset, cmd_data86_t* cmd_data);
 int cmd_data89_pack(cbor_stream_t* stream, cmd_data89_t* cmd_data);
 int cmd_data89_unpack(cbor_stream_t* stream, size_t* offset, cmd_data89_t* cmd_data);
 int cmd_data92_pack(cbor_stream_t* stream, cmd_data92_t* cmd_data);
 int cmd_data92_unpack(cbor_stream_t* stream, size_t* offset, cmd_data92_t* cmd_data);
 int cmd_data95_pack(cbor_stream_t* stream, cmd_data95_t* cmd_data);
 int cmd_data95_unpack(cbor_stream_t* stream, size_t* offset, cmd_data95_t* cmd_data);
 int cmd_data96_pack(cbor_stream_t* stream, cmd_data96_t* cmd_data);
 int cmd_data96_unpack(cbor_stream_t* stream, size_t* offset, cmd_data96_t* cmd_data);
 int cmd_data99_pack(cbor_stream_t* stream, cmd_data99_t* cmd_data);
 int cmd_data99_unpack(cbor_stream_t* stream, size_t* offset, cmd_data99_t* cmd_data);
 int cmd_data101_pack(cbor_stream_t* stream, cmd_data101_t* cmd_data);
 int cmd_data101_unpack(cbor_stream_t* stream, size_t* offset, cmd_data101_t* cmd_data);
 int cmd_data102_pack(cbor_stream_t* stream, cmd_data102_t* cmd_data);
 int cmd_data102_unpack(cbor_stream_t* stream, size_t* offset, cmd_data102_t* cmd_data);
 int cmd_data104_pack(cbor_stream_t* stream, cmd_data104_t* cmd_data);
 int cmd_data104_unpack(cbor_stream_t* stream, size_t* offset, cmd_data104_t* cmd_data);
 int cmd_data107_pack(cbor_stream_t* stream, cmd_data107_t* cmd_data);
 int cmd_data107_unpack(cbor_stream_t* stream, size_t* offset, cmd_data107_t* cmd_data);
 int cmd_data110_pack(cbor_stream_t* stream, cmd_data110_t* cmd_data);
 int cmd_data110_unpack(cbor_stream_t* stream, size_t* offset, cmd_data110_t* cmd_data);
 int cmd_data111_pack(cbor_stream_t* stream, cmd_data111_t* cmd_data);
 int cmd_data111_unpack(cbor_stream_t* stream, size_t* offset, cmd_data111_t* cmd_data);
 int cmd_data114_pack(cbor_stream_t* stream, cmd_data114_t* cmd_data);
 int cmd_data114_unpack(cbor_stream_t* stream, size_t* offset, cmd_data114_t* cmd_data);
 int cmd_data117_pack(cbor_stream_t* stream, cmd_data117_t* cmd_data);
 int cmd_data117_unpack(cbor_stream_t* stream, size_t* offset, cmd_data117_t* cmd_data);
 int cmd_data118_pack(cbor_stream_t* stream, cmd_data118_t* cmd_data);
 int cmd_data118_unpack(cbor_stream_t* stream, size_t* offset, cmd_data118_t* cmd_data);
 int cmd_data121_pack(cbor_stream_t* stream, cmd_data121_t* cmd_data);
 int cmd_data121_unpack(cbor_stream_t* stream, size_t* offset, cmd_data121_t* cmd_data);
 int cmd_data124_pack(cbor_stream_t* stream, cmd_data124_t* cmd_data);
 int cmd_data124_unpack(cbor_stream_t* stream, size_t* offset, cmd_data124_t* cmd_data);
 int cmd_data125_pack(cbor_stream_t* stream, cmd_data125_t* cmd_data);
 int cmd_data125_unpack(cbor_stream_t* stream, size_t* offset, cmd_data125_t* cmd_data);
 int cmd_data129_pack(cbor_stream_t* stream, cmd_data129_t* cmd_data);
 int cmd_data129_unpack(cbor_stream_t* stream, size_t* offset, cmd_data129_t* cmd_data);
 int cmd_data130_pack(cbor_stream_t* stream, cmd_data130_t* cmd_data);
 int cmd_data130_unpack(cbor_stream_t* stream, size_t* offset, cmd_data130_t* cmd_data);
 int cmd_data132_pack(cbor_stream_t* stream, cmd_data132_t* cmd_data);
 int cmd_data132_unpack(cbor_stream_t* stream, size_t* offset, cmd_data132_t* cmd_data);
 int cmd_data135_pack(cbor_stream_t* stream, cmd_data135_t* cmd_data);
 int cmd_data135_unpack(cbor_stream_t* stream, size_t* offset, cmd_data135_t* cmd_data);
 int cmd_data136_pack(cbor_stream_t* stream, cmd_data136_t* cmd_data);
 int cmd_data136_unpack(cbor_stream_t* stream, size_t* offset, cmd_data136_t* cmd_data);
 int cmd_data140_pack(cbor_stream_t* stream, cmd_data140_t* cmd_data);
 int cmd_data140_unpack(cbor_stream_t* stream, size_t* offset, cmd_data140_t* cmd_data);
 int cmd_data142_pack(cbor_stream_t* stream, cmd_data142_t* cmd_data);
 int cmd_data142_unpack(cbor_stream_t* stream, size_t* offset, cmd_data142_t* cmd_data);
 int cmd_data143_pack(cbor_stream_t* stream, cmd_data143_t* cmd_data);
 int cmd_data143_unpack(cbor_stream_t* stream, size_t* offset, cmd_data143_t* cmd_data);
 int cmd_data145_pack(cbor_stream_t* stream, cmd_data145_t* cmd_data);
 int cmd_data145_unpack(cbor_stream_t* stream, size_t* offset, cmd_data145_t* cmd_data);
 int cmd_data146_pack(cbor_stream_t* stream, cmd_data146_t* cmd_data);
 int cmd_data146_unpack(cbor_stream_t* stream, size_t* offset, cmd_data146_t* cmd_data);
 int cmd_data147_pack(cbor_stream_t* stream, cmd_data147_t* cmd_data);
 int cmd_data147_unpack(cbor_stream_t* stream, size_t* offset, cmd_data147_t* cmd_data);
 int cmd_data151_pack(cbor_stream_t* stream, cmd_data151_t* cmd_data);
 int cmd_data151_unpack(cbor_stream_t* stream, size_t* offset, cmd_data151_t* cmd_data);
 int cmd_data152_pack(cbor_stream_t* stream, cmd_data152_t* cmd_data);
 int cmd_data152_unpack(cbor_stream_t* stream, size_t* offset, cmd_data152_t* cmd_data);
 int cmd_data154_pack(cbor_stream_t* stream, cmd_data154_t* cmd_data);
 int cmd_data154_unpack(cbor_stream_t* stream, size_t* offset, cmd_data154_t* cmd_data);
 int cmd_data155_pack(cbor_stream_t* stream, cmd_data155_t* cmd_data);
 int cmd_data155_unpack(cbor_stream_t* stream, size_t* offset, cmd_data155_t* cmd_data);
 int cmd_data156_pack(cbor_stream_t* stream, cmd_data156_t* cmd_data);
 int cmd_data156_unpack(cbor_stream_t* stream, size_t* offset, cmd_data156_t* cmd_data);
 int cmd_data160_pack(cbor_stream_t* stream, cmd_data160_t* cmd_data);
 int cmd_data160_unpack(cbor_stream_t* stream, size_t* offset, cmd_data160_t* cmd_data);
 int cmd_data161_pack(cbor_stream_t* stream, cmd_data161_t* cmd_data);
 int cmd_data161_unpack(cbor_stream_t* stream, size_t* offset, cmd_data161_t* cmd_data);
 int cmd_data163_pack(cbor_stream_t* stream, cmd_data163_t* cmd_data);
 int cmd_data163_unpack(cbor_stream_t* stream, size_t* offset, cmd_data163_t* cmd_data);
 int cmd_data165_pack(cbor_stream_t* stream, cmd_data165_t* cmd_data);
 int cmd_data165_unpack(cbor_stream_t* stream, size_t* offset, cmd_data165_t* cmd_data);
 int cmd_data168_pack(cbor_stream_t* stream, cmd_data168_t* cmd_data);
 int cmd_data168_unpack(cbor_stream_t* stream, size_t* offset, cmd_data168_t* cmd_data);
 int cmd_data172_pack(cbor_stream_t* stream, cmd_data172_t* cmd_data);
 int cmd_data172_unpack(cbor_stream_t* stream, size_t* offset, cmd_data172_t* cmd_data);
 int cmd_data174_pack(cbor_stream_t* stream, cmd_data174_t* cmd_data);
 int cmd_data174_unpack(cbor_stream_t* stream, size_t* offset, cmd_data174_t* cmd_data);
 int cmd_data175_pack(cbor_stream_t* stream, cmd_data175_t* cmd_data);
 int cmd_data175_unpack(cbor_stream_t* stream, size_t* offset, cmd_data175_t* cmd_data);
 int cmd_data176_pack(cbor_stream_t* stream, cmd_data176_t* cmd_data);
 int cmd_data176_unpack(cbor_stream_t* stream, size_t* offset, cmd_data176_t* cmd_data);
 int cmd_data177_pack(cbor_stream_t* stream, cmd_data177_t* cmd_data);
 int cmd_data177_unpack(cbor_stream_t* stream, size_t* offset, cmd_data177_t* cmd_data);
 int cmd_data178_pack(cbor_stream_t* stream, cmd_data178_t* cmd_data);
 int cmd_data178_unpack(cbor_stream_t* stream, size_t* offset, cmd_data178_t* cmd_data);
 int cmd_data179_pack(cbor_stream_t* stream, cmd_data179_t* cmd_data);
 int cmd_data179_unpack(cbor_stream_t* stream, size_t* offset, cmd_data179_t* cmd_data);
 int cmd_data180_pack(cbor_stream_t* stream, cmd_data180_t* cmd_data);
 int cmd_data180_unpack(cbor_stream_t* stream, size_t* offset, cmd_data180_t* cmd_data);
 int cmd_data181_pack(cbor_stream_t* stream, cmd_data181_t* cmd_data);
 int cmd_data181_unpack(cbor_stream_t* stream, size_t* offset, cmd_data181_t* cmd_data);
 int cmd_data182_pack(cbor_stream_t* stream, cmd_data182_t* cmd_data);
 int cmd_data182_unpack(cbor_stream_t* stream, size_t* offset, cmd_data182_t* cmd_data);
 int cmd_data183_pack(cbor_stream_t* stream, cmd_data183_t* cmd_data);
 int cmd_data183_unpack(cbor_stream_t* stream, size_t* offset, cmd_data183_t* cmd_data);
 int cmd_data187_pack(cbor_stream_t* stream, cmd_data187_t* cmd_data);
 int cmd_data187_unpack(cbor_stream_t* stream, size_t* offset, cmd_data187_t* cmd_data);
 int cmd_data189_pack(cbor_stream_t* stream, cmd_data189_t* cmd_data);
 int cmd_data189_unpack(cbor_stream_t* stream, size_t* offset, cmd_data189_t* cmd_data);
 int cmd_data191_pack(cbor_stream_t* stream, cmd_data191_t* cmd_data);
 int cmd_data191_unpack(cbor_stream_t* stream, size_t* offset, cmd_data191_t* cmd_data);
 int cmd_data192_pack(cbor_stream_t* stream, cmd_data192_t* cmd_data);
 int cmd_data192_unpack(cbor_stream_t* stream, size_t* offset, cmd_data192_t* cmd_data);
 int cmd_data194_pack(cbor_stream_t* stream, cmd_data194_t* cmd_data);
 int cmd_data194_unpack(cbor_stream_t* stream, size_t* offset, cmd_data194_t* cmd_data);
*/
#endif


#ifndef __FUNCTIONAL_UNIT_HPP__
#define __FUNCTIONAL_UNIT_HPP__

class Adders;
class Multipliers;

#include "common.hpp"
#include "register_file.hpp"
#include "reservation_stations.hpp"

class Adders {
private:
    bool busy[FUNC_UNIT_ADD_NUM];

public:
    Adders ();
    bool get_busy (int &index_o);
    void run_task (res_sta_assign_task_stream_t &from_res_sta, func_unit_finish_task_stream_t &to_res_sta, Register_file &rf, Reservation_stations &rs);
};

class Multipliers {
private:
    bool busy[FUNC_UNIT_MUL_NUM];

public:
    Multipliers ();
    bool get_busy (int &index_o);
    void run_task (res_sta_assign_task_stream_t &from_res_sta, func_unit_finish_task_stream_t &to_res_sta, Register_file &rf, Reservation_stations &rs);
};

#endif

#ifndef TEST_DATA_H
#define TEST_DATA_H

#include "clustering.h"


static DataPoint simple_test_data[] = {
    {{1.0, 1.0}}, {{1.1, 1.0}}, {{1.0, 1.1}}, {{1.1, 1.1}},
    {{4.0, 4.0}}, {{4.1, 4.0}}, {{4.0, 4.1}}, {{4.1, 4.1}},
    {{8.0, 8.0}}, {{8.1, 8.0}}, {{8.0, 8.1}}
};

static const uint32_t simple_test_data_count = sizeof(simple_test_data) / sizeof(DataPoint);


static DataPoint high_dim_test_data[] = {
    {{1.0, 2.0, 1.0, 2.0}}, {{1.1, 2.1, 1.1, 2.1}},
    {{5.0, 5.0, 5.0, 5.0}}, {{5.1, 5.1, 5.1, 5.1}},
    {{9.0, 9.0, 9.0, 9.0}}, {{9.1, 9.1, 9.1, 9.1}}
};

static const uint32_t high_dim_test_data_count = sizeof(high_dim_test_data) / sizeof(DataPoint);

#endif

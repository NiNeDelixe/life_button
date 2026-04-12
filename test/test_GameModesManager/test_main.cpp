//#include "stm32l1xx_hal.h"
#include <unity.h>

//extern void initialise_monitor_handles(void);

void setUp(void) {}
void tearDown(void) {}

void test_dummy(void)
{
    TEST_ASSERT_EQUAL(1, 1);
}

int main()
{
    //initialise_monitor_handles();

    UNITY_BEGIN();
    RUN_TEST(test_dummy);
    UNITY_END(); // stop unit testing

    while (1)
    {
    }
}

void SysTick_Handler(void)
{
    //HAL_IncTick();
}
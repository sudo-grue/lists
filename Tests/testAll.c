#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
// #include <CUnit/Console.h>

int
main(void)
{
    extern CU_SuiteInfo llistSuite;
    extern CU_SuiteInfo dllistSuite;
    extern CU_SuiteInfo cllistSuite;

    CU_SuiteInfo suites[] = {
        llistSuite,
        dllistSuite,
        cllistSuite,
        CU_SUITE_INFO_NULL
    };

    CU_initialize_registry();

    // Add all suites listed to registry
    CU_register_suites(suites);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    // CU_console_run_tests();
    CU_basic_run_tests();
    CU_cleanup_registry();
}

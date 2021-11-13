
/*********************************************************/
To build and run FSM project, use command:
make target

Once target executable is created, run ./target to run the program
/*********************************************************/


/*********************************************************/
To clean object files, use command:
make clean

/*********************************************************/


/*********************************************************/
There are 4 test-cases implemented in the main function:
1. simple_test_case() : simple producer and subscriber workflow
2. error_test_case1() : invalid event error handling
3. error_test_case2() : invalid state error handling
4. complex_test_case() : A complex case with multiple producers and subscribers

By default, complex_test_case() is enabled in main. One can simply uncomment the other test_case(s) to see their outputs as well.

A workflow diagram is also attached to better describe the workflow and responsibilities of different components involved.

/*********************************************************/
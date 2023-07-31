// Project 3 Part 1 Test File for Creating Circular Buffer in User Space.
#include <stdlib.h>
#include <stdio.h>

#include "buffer.h"

int testNumber = 0;
int testsPassed = 0;
int testsFailed = 0;

// *******************************************************************************************************************************************
// The Definition of Function "void assertEqual(int expectedValue, int actualValue, const char* message)" is that the                        *
// Function "void assertEqual(int expectedValue, int actualValue, const char* message)" determines if the Actual Value                       *
// meets the Value that is Expected. Therefore, in the Function "void assertEqual(int expectedValue, int actualValue, const char* message)", *
// if the Actual Value does meet the Value that is Expected, then it does output a passed statement. However, in the                         *
// Function "void assertEqual(int expectedValue, int actualValue, const char* message)", if the Expected Value does not equal                *
// to the Actual Value, then the Function "void assertEqual(int expectedValue, int actualValue, const char* message)" outputs a failed       *
// statement.                                                                                                                                *
// *******************************************************************************************************************************************
void assertEqual(int expectedValue, int actualValue, const char* message)
{
	if(expectedValue != actualValue)
	{
		fprintf(stderr, "Test %d Failed: expected %d but was %d - %s\n", ++testNumber, expectedValue, actualValue, message);
		testsFailed++;
		return;
	}

	fprintf(stdout, "Test %d Passed: %s\n", testNumber++, message);
	testsPassed++;
}

// ******************************************************************************************************************************************
// The Definition of Function "void printAssertStatementResults()" is that the Function "void printAssertStatementResults()" prints out, in *
// other words displays, the results of the Assert Statements.                                                                              *
// ******************************************************************************************************************************************
void printAssertStatementResults()
{
	fprintf(stdout, "Ran %d asserts.\nHave %d passes and %d failures\n%.2f %% pass rate\n", testNumber, testsPassed, testsFailed, (testsPassed/(float)testNumber)*100);
}

int main()
{
        // Test 1 and do Inserting before Initialization.
        assertEqual(-1, insert_buffer_421(1), "Insert before Initialization");
        assertEqual(-1, print_buffer_421(), "Print Ring Buffer that is the Circular Buffer before Initialization");
        assertEqual(-1, delete_buffer_421(), "Delete the Ring Buffer that is the Circular Buffer before Initialization");

        // Initialize the buffer.
        assertEqual(0, init_buffer_421(), "Initializing Buffer");
        assertEqual(-1, init_buffer_421(), "Initializing Buffer that has already been Initialized");

        // Assign Values 1 to 20 to the buffer.
        int i = 1;
        while(i <= SIZE_OF_BUFFER)
        {
                char buffer[128];
                sprintf(buffer, "Produce %d", i);
                assertEqual(0, insert_buffer_421(i), buffer);
                i++;
        }

        assertEqual(-1, insert_buffer_421(21), "Inserting Buffer Past the Buffer Size Limit");

        // Print Out the Ring Buffer that is the Circular Buffer.
        assertEqual(0, print_buffer_421(), "Printing Ring Buffer that is the Circular Buffer");

	 // Delete the Ring Buffer that is the Circular Buffer.
        assertEqual(0, delete_buffer_421(), "Deleting Ring Buffer that is the Circular Buffer");
        assertEqual(-1, delete_buffer_421(), "Deleting Ring Buffer that is the Circular Buffer after it has been deleted");

        // Print Out the Ring Buffer that is the Circular Buffer to ensure everything is deleted.
        assertEqual(-1, print_buffer_421(), "Printing Ring Buffer that is the Circular Buffer After Deletion");

        // Call for the printAssertStatementResults() Function.
        printAssertStatementResults();

        return 0;
}

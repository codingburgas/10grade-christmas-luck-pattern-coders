/*
 * Executes all tests in the program and reports the results
 * Parameters:
 * -- None
 * Returns:
 * -- int: 0 if all tests pass, 1 if any test fails
 */
int test();


/*
 * Prints the result of test execution
 * Parameters:
 * -- code: exit code of the test
 * -- failed: pointer to a boolean that tracks if any test has failed
 * Returns:
 * -- None
 */
void printResult(int code, bool *failed);

/*
 * Tests the getTagData function
 * Parameters:
 * -- None
 * Returns:
 * -- int: 0 if all tests pass, 1 if any test fails
 */
int test_getTagData();

/*
 * Tests the select function
 * Parameters:
 * -- None
 * Returns:
 * -- int: 0 if all tests pass, 1 if any test fails
 */
int test_select();


/*
 * Tests the sortWords function by comparing sorted results to expected outputs
 * Parameters:
 * -- None
 * Returns:
 * -- int: 0 if all tests pass, 1 if any test fails
 */
int test_sortWords();


/*
 * Tests the leaveWordsWithSpecificPart function by filtering words with specific properties
 * Parameters:
 * -- None
 * Returns:
 * -- int: 0 if all tests pass, 1 if any test fails
 */
int test_leaveWordsWithSpecificPart();

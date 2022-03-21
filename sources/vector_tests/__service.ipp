#pragma once
#include "../system/lib.hpp"
#include VECTOR

template <class T>
int run_vector_unit_test(std::string test_name, std::vector<int> (func1)(std::vector<T>), std::vector<int> (func2)(_vector<T>)) {
    int    result;
    int    leaks;
    time_t t1;
    time_t t2;
    std::vector<int > res1;
    std::vector<int > res2;
    std::vector<int> vector;
    _vector<int> my_vector;

	printElement(test_name);
	res1 = func1(vector);
	res2 = func2(my_vector);
	if (res1 == res2) {
	    printElement("OK");
	    result = 0;
	}
	else {
		std::ofstream ofs("../../vector_failed.log", std::ios::out | std::ios::app);
		ofs << "[[vector/" << test_name << "]]" << std::endl;
		ofs << "EXPECTED: " << std::endl;
		for (std::vector<int>::iterator it = res1.begin(); it != res1.end(); ++it)
			ofs << " " << *it << std::endl;
		ofs << "YOUR RESULT: " << std::endl;
		for (std::vector<int>::iterator it = res2.begin(); it != res2.end(); ++it)
			ofs << " " << *it << std::endl;
		ofs << std::endl;
	    printElement("FAILED");
	    result = 1;
	}
	t1 = g_end1 - g_start1, t2 = g_end2 - g_start2;
	(t1 >= t2) ? printElement(GREEN + std::to_string(t2) + "ms" + RESET) : printElement(REDD + std::to_string(t2) + "ms" + RESET);
	(t1 > t2) ? printElement(REDD + std::to_string(t1) + "ms" + RESET) : printElement(GREEN + std::to_string(t1) + "ms" + RESET);
	leaks = leaks_test(test_name, getpid());
	cout << endl;

	return !(!result && !leaks);
}

template <class T, class A>
int run_vector_allocator_unit_test(std::string test_name, void (func)(_vector<T, A>)) {
    _vector<T, A> my_vector;

    printElement(test_name);
    func(my_vector);
    if (_allocator_used) {
        printElement("OK");
        cout << endl;
        return (0);
    }
    else {
        printElement("FAILED");
        cout << endl;
        return (1);
    }
}

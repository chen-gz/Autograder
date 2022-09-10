#include <iostream>
#include <string>
using namespace std;

/**
 * This program is the 'key' for assignment 2 and will produce
 * the correct output. We'll parse this output and the student's output,
 * then compare.
 */
int main() {
	
	// Step 1
	cout << "ECE 0301 Propositional Logic Example\n" << endl;
	
	// Step 2
	string p1s = "Pigs can fly.";
	string p2s = "Earth is flat.";
	string p3s = "The moon is cheese.\n";
	cout << "P1: " << p1s << endl;
	cout << "P2: " << p2s << endl;
	cout << "P3: " << p3s << endl;
    bool p1, p2, p3;
    
    // Step 3
    cout << "Enter P1 truth value: ";
    cin >> p1;
    cout << "Enter P2 truth value: ";
    cin >> p2;
    cout << "Enter P3 truth value: ";
    cin >> p3;

	// Step 4
    cout << "\nYou entered: P1 = " << boolalpha << p1;
    cout << ", P2 = " << boolalpha << p2;
    cout << ", P3 = " << boolalpha << p3 << "." << endl;

	// Step 5
    bool p4 = p1 && (!p2) && p3;

    cout << "Truth table:" << endl;
    cout << "Proposition\tTruth Value" << endl;
    cout << "-----------\t-----------" << endl;
    cout << "P1\t\t" << boolalpha << p1 << endl;
    cout << "P2\t\t" << boolalpha << p2 << endl;
    cout << "P3\t\t" << boolalpha << p3 << endl;
    cout << "P4\t\t" << boolalpha << p4 << endl;

	// Step 6
    bool p5 = (!p1) || p2 || p3;

    cout << "P5\t\t" << boolalpha << p5 << endl;

	// Step 7
    bool p6 = (p1 && (!p2) && (!p3)) || ((!p1) && p2 && (!p3)) || ((!p1) && (!p2) && p3);
    cout << "P6\t\t" << boolalpha << p6 << endl;

	// Step 8
    bool p7 = !(p1 || p2 || p3);
    cout << "P7\t\t" << boolalpha << p7 << endl;

	// Step 9
    bool p8 = (p1 && p2) || (p2 && p3) || (p1 && p3);
    cout << "P8\t\t" << boolalpha << p8 << endl;

	// Step 10
    bool p9 = (!p1) && ((p2 || p3) && !(p2 && p3));
    cout << "P9\t\t" << boolalpha << p9 << endl;
    
    return 0;
}

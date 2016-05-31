// File:        a1simpledriver.cpp
// Author:      (your name here) / Geoffrey Tien
// Date:        2016-05021
// Description: Basic test driver for CPSC 221 assignment #2
//              This file tests some functions of the CCQueue and LinkedList classes of assignment #2.
//              Note that only functions which are called will be compiled, therefore you must
//                ensure that every function in your classes is called at least once.
//              Not all special cases have been tested; you will be responsible for adding
//                your own test code and function calls to this file in order to thoroughly
//                test all general and boundary cases for your functions.
//              In general, please ensure that you test:
//               1. invalid parameter(s)
//               2. valid parameter(s), boundary case
//               3. valid parameter(s), general case

#include <cstdlib>
#include <iostream>
#include <string>

#include "ccqueue.h"
#include "linkedlist.h"
#include "ticket.h"

using namespace std;

// forward function declarations
void LLTest();
void CCQTest();

// program entry point
int main()
{
  cout << "Entering LinkedList test function... " << endl;
  LLTest();
  cout << "... LinkedList test function complete!\n" << endl;

  cout << "Entering CCQueue test function... " << endl;
  CCQTest();
  cout << "... CCQueue test function complete!\n" << endl;

#ifdef _WIN32
  system("pause");
#endif
  return 0;
}

void LLTest()
{
	// default constructor, InsertFront, InsertBack, ElementAt
	LinkedList<int> lla;
	lla.InsertFront(5);
	lla.InsertBack(10);
	lla.InsertFront(2);
	lla.InsertBack(15);


	cout << "lla contains " << lla.Size() << " items." << endl;
	cout << "lla contains " << lla.ElementAt(0) << " at index 0." << endl;
	cout << "lla contains " << lla.ElementAt(1) << " at index 1." << endl;
	cout << "lla contains " << lla.ElementAt(2) << " at index 2." << endl;
	cout << "lla contains " << lla.ElementAt(3) << " at index 3." << endl;


	// copy constructor, InsertAt, RemoveAt (with exception)
	LinkedList<int> llb(lla);
	llb.InsertAt(7, 1);
	llb.InsertAt(3, 0);
	try
	{
		int temp = llb.RemoveAt(12345);
		cout << temp << endl;
	}
	catch (std::out_of_range e)
	{
		cout << "Exception in RemoveAt(): " << e.what() << endl;
	}
	cout << "llb contains " << llb.Size() << " items." << endl;
	cout << "llb contains " << llb.ElementAt(0) << " at index 0." << endl;
	cout << "llb contains " << llb.ElementAt(1) << " at index 1." << endl;
	cout << "llb contains " << llb.ElementAt(2) << " at index 2." << endl;
	cout << "llb contains " << llb.ElementAt(3) << " at index 3." << endl;

	int temp1 = llb.RemoveAt(0);
	int temp2 = llb.RemoveAt(2);
	cout << "llb contains " << llb.Size() << " items." << endl;
	cout << "llb contains " << llb.ElementAt(0) << " at index 0." << endl;
	cout << "llb contains " << llb.ElementAt(1) << " at index 1." << endl;

	llb.InsertAt(4, 2);
	cout << "llb contains " << llb.Size() << " items." << endl;
	cout << "llb contains " << llb.ElementAt(0) << " at index 0." << endl;
	cout << "llb contains " << llb.ElementAt(1) << " at index 1." << endl;
	cout << "llb contains " << llb.ElementAt(2) << " at index 2." << endl;

	int temp3 = llb.RemoveAt(1);
	cout << "llb contains " << llb.Size() << " items." << endl;
	cout << "llb contains " << llb.ElementAt(0) << " at index 0." << endl;
	cout << "llb contains " << llb.ElementAt(1) << " at index 1." << endl;

	// assignment operator, IsEmpty, Size, RemoveDuplicates, Contains
	LinkedList<int> llc;
	if (llc.IsEmpty())
		cout << "llc is empty." << endl;
	else
		cout << "llc is not empty." << endl;

	llc = lla;

	if (llc.IsEmpty())
		cout << "llc is empty." << endl;
	else
		cout << "llc is not empty." << endl;
	llc.InsertBack(13);
	llc.InsertBack(13);
	llc.InsertBack(13);
	cout << "llc contains " << llc.Size() << " items." << endl;
	cout << "llc contains " << llc.ElementAt(0) << " at index 0." << endl;
	cout << "llc contains " << llc.ElementAt(1) << " at index 1." << endl;
	cout << "llc contains " << llc.ElementAt(2) << " at index 2." << endl;
	cout << "llc contains " << llc.ElementAt(3) << " at index 3." << endl;
	cout << "llc contains " << llc.ElementAt(4) << " at index 4." << endl;
	llc.RemoveDuplicates();

	cout << "after removing duplicates, llc contains " << llc.Size() << " items." << endl;
	cout << "llc contains " << llc.ElementAt(0) << " at index 0." << endl;
	cout << "llc contains " << llc.ElementAt(1) << " at index 1." << endl;
	cout << "llc contains " << llc.ElementAt(2) << " at index 2." << endl;

	if (llc.Contains(10))
		cout << "10 found in llc." << endl;
	else
		cout << "10 not found in llc." << endl;
	if (llc.Contains(13))
		cout << "13 found in llc." << endl;
	else
		cout << "13 not found in llc." << endl;

	cout << "Before appending lla onto llb:" << endl;
	cout << "lla contains " << lla.Size() << " items, "
		<< "llb contains " << llb.Size() << " items." << endl;
	cout << "lla contains " << lla.ElementAt(0) << " at index 0." << endl;
	cout << "lla contains " << lla.ElementAt(1) << " at index 1." << endl;
	cout << "llb contains " << llb.ElementAt(0) << " at index 0." << endl;
	cout << "llb contains " << llb.ElementAt(1) << " at index 1." << endl;

	llb.Append(lla);
	cout << "After appending lla onto llb:" << endl;
	cout << "lla contains " << lla.Size() << " items, "
		<< "llb contains " << llb.Size() << " items." << endl;

	cout << "lla contains " << lla.ElementAt(0) << " at index 0." << endl;
	cout << "lla contains " << lla.ElementAt(1) << " at index 1." << endl;
	cout << "lla contains " << lla.ElementAt(2) << " at index 2." << endl;
	cout << "lla contains " << lla.ElementAt(3) << " at index 3." << endl;
	cout << "  " << endl;
	cout << "llb contains " << llb.ElementAt(0) << " at index 0." << endl;
	cout << "llb contains " << llb.ElementAt(1) << " at index 1." << endl;
	cout << "llb contains " << llb.ElementAt(2) << " at index 2." << endl;
	cout << "llb contains " << llb.ElementAt(3) << " at index 3." << endl;
	cout << "llb contains " << llb.ElementAt(4) << " at index 4." << endl;
	cout << "llb contains " << llb.ElementAt(5) << " at index 5." << endl;
	cout << "llb contains " << llb.ElementAt(6) << " at index 6." << endl;
	cout << "llb contains " << llb.ElementAt(7) << " at index 7." << endl;

	cout << "deleting 1 of 4 elements in lla" << endl;
	lla.RemoveAt(0);
	cout << "deleting 2 of 4 elements in lla" << endl;
	lla.RemoveAt(0);
	cout << "deleting 3 of 4 elements in lla" << endl;
	lla.RemoveAt(0);
	cout << "deleting 4 of 4 elements in lla" << endl;
	lla.RemoveAt(0);
	cout << "completed deleting" << endl;
}

void CCQTest()
{
	CCQueue ccq;
	ccq.Add("Alrikr", "Video card smoked");
	ccq.Add("Bjornstjerne", "Cable is wrong colour, computer not colour coordinated. Worst day ever");
	ccq.Add("Cyprianus", "Still lost game after consuming energy drink");
	ccq.Add("Dietrich", "Order not received");
	ccq.Add("Elisaeus", "Box says 1TB, only 931GB formatted");
	cout << "Size of ticket queue: " << ccq.Size() << endl;
	cout << "Moving down index 0" << endl;
	ccq.MoveDown(0);
	cout << ccq.PrintStatus() << endl;
	cout << "Moving up index 4 (last item)" << endl;
	ccq.MoveUp(4);
	cout << ccq.PrintStatus() << endl;
	cout << " " << endl;

	ccq.Service();
	ccq.MoveUp(3);
	ccq.MoveUp(2);
	ccq.MoveDown(2);
	cout << ccq.PrintStatus() << endl;
	ccq.Service();
	ccq.Service();
	ccq.Service();
	ccq.Service();
	cout << ccq.PrintStatus() << endl;
	ccq.Add("Alrikr", "Video card smoked");
	cout << ccq.PrintStatus() << endl;
}

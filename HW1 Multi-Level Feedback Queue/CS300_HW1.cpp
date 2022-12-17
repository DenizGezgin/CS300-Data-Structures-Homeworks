/*
Deniz Can Gezgin 27992
Date: 27.01.2021
CS301 Homework-1

Program has an implimataion of MLFQ and runs a similiton of it using some data provived with text files.
In the end output is given as a text file in the specified directiory.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Queue.h"

using namespace std;

//runs to next process while making the neccesary queue arregemnts
void runNext(vector<Queue*>& MLFQ, int numQueues, vector<string>& processFiles, int& remaningProcesses, const int sizeS, ofstream& outputFile)
{
	static int timeTick = 0; //counts time in order to determine when next S is reached
	static int proccesID, newQueuetoPrint;
	static char currentTime; //keeps track of how much time current process will take
	bool finished = false; //keeps track of when process is finished
	//scan each queue from high to low priority
	for (int i = numQueues-1; !finished && i >= 0; i--)
	{
		//when you find an nonempty queue enterv it
		if (!(MLFQ[i]->isEmpty()))
		{
			proccesID = MLFQ[i]->dequeue(); //get ID of next procces to be run

			//get the first info from file contents
			currentTime = processFiles[proccesID - 1][0];
			processFiles[proccesID - 1].erase(0, 1); //remove read chr POSSIBLE BUG! starts with -

			//if at this point next char in fileString is - process is done
			if (processFiles[proccesID - 1][0] == '-')
			{
				outputFile << "E, PC" << proccesID << ", QX" << endl;
				timeTick++; 
				remaningProcesses--; //one more process done
			}
			else //else run and queue as usual
			{
				if (currentTime == '0')
				{
					(MLFQ[i]->enqueue(proccesID)); //put in same level
					newQueuetoPrint = i + 1;
				}
				else if (currentTime == '1')
				{
					if (i - 1 == -1)
					{
						(MLFQ[i]->enqueue(proccesID)); //dont change if already at lowest level
						newQueuetoPrint = 1;
					}
					else
					{
						(MLFQ[i-1]->enqueue(proccesID)); //put in lower level
						newQueuetoPrint = i;
					}

				}
				timeTick++;
				outputFile << currentTime << ", PC" << proccesID << ", Q" << newQueuetoPrint << endl;
			}
			finished = true;

			//check if enough time passed to move all process to top
			if (timeTick == sizeS)
			{
				//dequqe then enqeue to topmost for all proceses
				for (int j = numQueues - 2; j >= 0; j--) //-2 since we cant move from topmost queue to topmost queue
				{
					if (!(MLFQ[j]->isEmpty())) //when found a nonempty queue
					{
						proccesID = MLFQ[j]->dequeue();
						MLFQ[numQueues - 1]->enqueue(proccesID);
						outputFile << "B, PC" << proccesID << ", Q" << numQueues << endl;
						j++; //increase j to check same level again
					}
				}
				timeTick = 0;
			}
		}
	}
	
}


int main()
{
	//getting folder name
	string folderName, filePath;
	cout << "Please enter the process folder name: ";
	cin >> folderName;
	cout << "When all processes are completed, you can find execution sequence in \"" << folderName << "\\output.txt\"" << endl;
	//reading Configuration File
	ifstream file;
	string line;
	filePath = folderName + "\\configuration.txt";

	file.open(filePath); //file oppened
	int numQueues, numProcesses, sizeS;
	//numQueues
	getline(file, line); 
	istringstream lineContent(line);
	lineContent >> numQueues;
	//numProcesses
	getline(file, line);
	istringstream lineContent1(line);
	lineContent1 >> numProcesses;
	//sizeS
	getline(file, line);
	istringstream lineContent2(line);
	lineContent2 >> sizeS;
	
	file.close(); //file closed


	//r value l value dynamic variablel class
	vector<Queue*> MLFQ;
	for (int i = 0; i < numQueues; i++)
	{
		Queue* x = new Queue(numProcesses);
		MLFQ.push_back(x); //each are capable of holding all proceses
	}


	
	//turn file contetns in to a one line string and store them in an vector
	vector<string> processFiles;
	for (int i = 1; i <= numProcesses; i++)
	{
		string currentContents, temp;
		filePath = folderName + "\\p" + to_string(i) + ".txt";
		file.open(filePath);
		while (getline(file, line))
		{
			istringstream lineContent(line);
			lineContent >> temp;
			currentContents += temp;
		}
		processFiles.push_back(currentContents);
		file.close();
	}

	//all proceseses appened to highest level to START
	//process stored as intager IDs
	for (int i = 1; i <= numProcesses; i++)
	{
		MLFQ[numQueues - 1]->enqueue(i);
	}

	int remaingProceses = numProcesses;
	ofstream outputFile;
	filePath = folderName + "\\output.txt"; //end result will be here
	outputFile.open(filePath);
	while (remaingProceses != 0)
	{
		runNext(MLFQ, numQueues, processFiles, remaingProceses, sizeS, outputFile);
	}
	
	outputFile.close();

	//free the dynamic memories
	for (int i = 0; i < numQueues; i++)
	{
		delete MLFQ[i];
	}

	return 0;
}



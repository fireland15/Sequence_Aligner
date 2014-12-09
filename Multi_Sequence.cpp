// Class: MultiSequence Code
// Forrest Ireland
// Dec. 3, 2014

#include "Multi_Sequence.h"

MultiSequence::MultiSequence(Sequence s) {
	setFirstSequence(s);
}

MultiSequence::~MultiSequence() {

}

/************************************************/
/* OPERATOR FUNCTIONS                           */
/************************************************/

VC MultiSequence::operator[](int a) {
	VC c;
	for (unsigned int i = 0; i < multiSequence.size(); i++) {
		c.push_back(multiSequence[i][a]);
	}
	return c;
}


void MultiSequence::operator()(int a, VC& c) {
	c.clear();
	for (unsigned int i = 0; i < multiSequence.size(); i++) {
		c.push_back(multiSequence[i][a]);
	}
}

void MultiSequence::push_back(VC& c) {
	for (unsigned int i = 0; i < multiSequence.size(); i++) {
		multiSequence[i].push_back(c[i]);
	}
}

void MultiSequence::push_back(char c) {
	for (unsigned int i = 0; i < multiSequence.size(); i++) {
		multiSequence[i].push_back(c);
	}
}

void MultiSequence::setNumSequences(int num) {
	for (int i = 0; i < num; i++) {
		multiSequence.push_back(Sequence());
	}
}

void MultiSequence::setFirstSequence(Sequence &seq) {
	if (!multiSequence.empty()) {
		std::cout << "Sequence has been set. Cannot set another one." << std::endl;
		return;
	}
	setNumSequences(1);
	char c;
	for (int i = 0; i < seq.Length(); i++) {
		c = seq[i];
		push_back(c);
	}
	std::vector<int> ID;
	ID.push_back(seq.getAccessionNum());
	setSequenceIDs(ID);
}

void MultiSequence::setSequenceIDs(std::vector<int>& id) {
	for (unsigned int i = 0; i < multiSequence.size(); i++) {
		multiSequence[i].setAccessionNum(id[i]);
	}
}

/************************************************/
/* GET FUNCTIONS                                */
/************************************************/

void MultiSequence::WriteMultiSequenceToFile(std::string filename) {
	std::ofstream output;
	output.open(filename);
	if (output.is_open()) {
		for (unsigned int i = 0; i < multiSequence.size(); i++) {
			output << multiSequence[i].getAccessionNum() << "\t";
			for (int j = 0; j < multiSequence[i].Length(); j++) {
				output << multiSequence[i][j];
			}
			output << std::endl;
		}
		output.close();
	}
	else {
		std::cout << "Error: Unable to open - " << filename << std::endl;
	}
}

int MultiSequence::numSequences() {
	return multiSequence.size();
}

int MultiSequence::Length() {
	return multiSequence[0].Length();
}

int MultiSequence::getSequenceIDs(int index) {
	return multiSequence[index].getAccessionNum();
}

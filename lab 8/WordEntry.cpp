#include "WordEntry.h"
#include "WordEntry.h"

WordEntry::WordEntry(const string &text, int score)
 : word(text), numAppearances(1), totalScore(score) {
	 
}

void WordEntry::addNewAppearance(int s) {
	totalScore += s;
	++numAppearances;
}

const string & WordEntry::getWord() const {
    return word;
}
double WordEntry::getAverage() const {
	return static_cast<double>(totalScore) / numAppearances;
}

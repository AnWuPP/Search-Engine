#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <vector>
#include <future>
#include <iterator>
#include <fstream>
#include <iostream>

struct Entry {
	int docId;
	int count;
	bool operator ==(const Entry& other) const {
		return (docId == other.docId &&
			count == other.count);
	}
};

using freqType = std::map<std::string, std::vector<Entry>>;

class InvertedIndex {
public:
	InvertedIndex() = default;
	void updateDocumentBase(std::vector<std::string> inputDocs);
	std::vector<Entry> getWordCount(const std::string& word) const;
	freqType getFreqDict();

private:
	freqType getWords(std::string filepath, int idDoc) const;
	std::vector<std::string> docs;
	freqType freqDict;
};
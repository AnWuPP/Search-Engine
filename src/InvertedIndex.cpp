#include "InvertedIndex.h"
#include "Exceptions.h"
#include <future>
#include <iterator>
#include <fstream>
#include <iostream>

void InvertedIndex::updateDocumentBase(std::vector<std::string> inputDocs) {
	std::vector<std::future<freqType>> res;
	for (int i = 0, ie = inputDocs.size(); i != ie; ++i) {
		res.push_back(std::async(&InvertedIndex::getWordsInFile, this, inputDocs[i], i));
	}
}

freqType InvertedIndex::getWordsInFile(std::string filepath, int idDoc) {
	try {
		if (!std::filesystem::exists(filepath))
			throw ExceptionFileNotFound();
	}
	catch (ExceptionFileNotFound e) {
		std::cerr << e.what() << std::endl;
		return freqType();
	}
	freqType res;
	std::ifstream file(filepath);
	std::istream_iterator<std::string> it(file);
	while (it != std::istream_iterator<std::string>()) {
		std::string word = *it;
		if (res.find(word) == res.end()) {
			res[word].emplace_back();
			res[word][0].docId = idDoc;
		}
		res[word][0].count++;
		it++;
	}
	file.close();
	return res;
}
#include <vector>
#include <string>
#include <unordered_map>
#include <regex>

struct Document {
    std::string uri;
    std::string text;
};

using Corpus = std::vector<Document>;

class CorpusIndex {
public:
    CorpusIndex(Corpus corpus) {
        for (const auto& doc : corpus) {
            indexDocument(doc);
        }
    }

    std::vector<const Document*> find(std::string_view word) {
        std::vector<const Document*> result;
        auto it = invertedIndex.find(std::string(word));
        if (it != invertedIndex.end()) {
            result = it->second;
            std::sort(result.begin(), result.end(), [](const Document* a, const Document* b) {
                if (a->text == b->text) {
                    return a->uri < b->uri;
                }
                return a->text > b->text;
            });
        }
        return result;
    }

private:
    std::unordered_map<std::string, std::vector<const Document*>> invertedIndex;

    void indexDocument(const Document& doc) {
        std::string lowercaseText = doc.text;
        std::transform(lowercaseText.begin(), lowercaseText.end(), lowercaseText.begin(), [](unsigned char c) {
            return std::tolower(c);
        });

        std::regex wordRegex("\\w+");
        std::sregex_iterator wordIterator(lowercaseText.begin(), lowercaseText.end(), wordRegex);
        std::sregex_iterator endIterator;

        while (wordIterator != endIterator) {
            std::string word = wordIterator->str();
            invertedIndex[word].push_back(&doc);
            ++wordIterator;
        }
    }
};

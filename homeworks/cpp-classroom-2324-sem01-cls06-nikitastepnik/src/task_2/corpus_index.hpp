#include <vector>
#include <string>

// namespace (?)

struct Document {
    std::string uri;
    std::string text;
};

using Corpus = std::vector<Document>;

class CorpusIndex {
    CorpusIndex() = delete;
    CorpusIndex(const CorpusIndex&) = delete;
    CorpusIndex& operator=(const CorpusIndex&) = delete;

    CorpusIndex(Corpus corpus);

    // возвращает отранжированный список документов (указатели на них)
    //
    // доки в результате отсортированы по частоте вхождения слова в текст
    // если частоты совпадают — применяется сортировка по uri
    std::vector<const Document*> find(std::string_view word);

    /* дополняйте класс */
};

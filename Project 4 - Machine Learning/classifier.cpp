#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <fstream>
#include <map>
#include <cmath>
#include "csvstream.hpp"
using namespace std;


class Classifier {
  private:
    bool TRAIN_ONLY_MODE = false;
    

    map<string/*tag*/, map<string/*word in post*/, int/*occurences*/>> countWordLabel;
    int numUniqueWords = 0; //Vocabulary Size
    //For each word w, the number of posts in the entire training set that contain w
    map<string /*word w*/, int/*num Posts with w*/> uniqueWordSet; 
    int numPosts = 0;
    //the number of posts with each tag
    map<string /*tag*/, /*numPostsWithTag*/ int> tagOccurences; 

    vector<pair<string,set<string>>> readFileThenConvertToSet(const string& input)  {
      csvstream ifs(input);
      if (!ifs) {  
        cout << "Error opening file: " << input << endl;
        return {}; 
      }

      vector<pair<string,set<string>>> values;
      map<string, string> test;
      while(ifs >> test){
        //cout << "Tag: " << test["tag"] << ", Content: " << test["content"] << endl;
        values.push_back(pair<string, set<string>>(test["tag"],
         unique_words(test["content"])));
        tagOccurences[test["tag"]]++;
        numPosts++;
      }

      return values;

    }

    vector<pair<string, string>> readFileThenConvertToOriginal(const string& input)  {
      csvstream ifs(input);
      if (!ifs) {  
        cout << "Error opening file: " << input << endl;
        return {}; 
      }

      vector<pair<string, string>> values;
      map<string, string> test;
      while(ifs >> test){
        values.push_back(pair<string, string>(test["tag"], test["content"]));
        tagOccurences[test["tag"]]++;
        numPosts++;
      }

      return values;
    }

    set<string> unique_words(const string &str) const {
      istringstream source(str);
      set<string> words;
      string word;
      while (source >> word) {
        words.insert(word);
      }
      return words;
    }


    // void organizeAllTags(const vector<pair<string,set<string>>> args){
    //   for (const auto &input : args){
    //     for (string s : input.second){
    //       countWordLabel[input.first][s]++;
    //       uniqueWordSet[s]++;
    //     }
    //   }
    //   numUniqueWords = uniqueWordSet.size();
      

    // }

    void organizeAllTags(const vector<pair<string, string>> args){
      for (const auto &input : args){
        set<string> uniqueWordsInPost = unique_words(input.second);
        for (const string& word : uniqueWordsInPost) {
          countWordLabel[input.first][word]++;
          uniqueWordSet[word]++;
        }
      }
      numUniqueWords = uniqueWordSet.size();
    }

    void probabilityCalc(const string& newPiazzaPost, 
                    const string& correctLabel, 
                    int& correctPredictions, 
                    int& totalPredictions) const {
      const set<string> setOfWordsInPiazzaPost = unique_words(newPiazzaPost);
      pair <string, double> lowestScore("SENTINEL_VALUE", -INFINITY);
      //cout << "trained on " << numPosts << " examples\n";
      for (const auto& tags : tagOccurences) {
        double tagProbability = calculateTagProbability(tags, setOfWordsInPiazzaPost);
        if (tagProbability > lowestScore.second)
          lowestScore = pair<string,double>(tags.first, tagProbability);
        //cout << "TAG: " << tags.first << " PROBSCORE : " << tagProbability << endl;
      }
      
      cout << "  correct = " << correctLabel << ", predicted = "
       << lowestScore.first  << ", log-probability score = " <<
        lowestScore.second << endl;
      cout << "  content = " << newPiazzaPost << endl << endl;

      totalPredictions++;
      if (lowestScore.first == correctLabel) {
        correctPredictions++;
      }
      
    }

    double calculateTagProbability(const pair<const string /*tag*/, 
                          int /*num Posts w/ tag*/> tags, 
                          const set<string>& setOfWordsInPiazzaPost) const{
      //Log-Prior Probability
      double logPriorProb = log(tags.second * 1.00/numPosts);

      //Log-likelihood Probability
      double logLikeProb = 0;
      for (string word : setOfWordsInPiazzaPost){
        if (uniqueWordSet.find(word) == uniqueWordSet.end()){
          logLikeProb += log(1.0/numPosts);
        } else 
        if (countWordLabel.at(tags.first).find(word) == 
          countWordLabel.at(tags.first).end()){
          logLikeProb += log(uniqueWordSet.at(word) * 1.0/numPosts);
        } else {
          logLikeProb += log(countWordLabel.at(tags.first).at(word) * 1.0 /tags.second);
        }
      }
      return logPriorProb + logLikeProb;

    }

    vector<pair<string, string>> getTestData(const string& input){
      csvstream ifs(input);
      if (!ifs) {  
        cout << "Error opening file: " << input << endl;
        return {}; 
      }
      
      vector<pair<string, string>> values;
      map<string, string> test;
      while(ifs >> test){
        values.push_back(pair<string,string>(test["tag"], test["content"]));
      }
      return values;
    }

  void printTrainingSummary() const {
    cout << "trained on " << numPosts << " examples\n";
    cout << "vocabulary size = " << numUniqueWords << "\n\n";
    cout << "classes:\n";

    int totalTags = tagOccurences.size();
    int currentTag = 0;
    for (const auto& tag : tagOccurences) {
      double logPrior = log(tag.second * 1.0 / numPosts);
      cout << "  " << tag.first << ", " << tag.second 
      << " examples, log-prior = " << logPrior;
      if (++currentTag < totalTags) {
        cout << "\n"; 
      }
    }
    cout << "\nclassifier parameters:\n";
    for (const auto& tag : countWordLabel) {
        //cout ":\n";
      for (const auto& wordCount : tag.second) {
        double logLikelihood = log(wordCount.second * 1.0 / tagOccurences.at(tag.first));
        cout<< "  " << tag.first << ":" << wordCount.first 
        << ", count = " << wordCount.second << 
        ", log-likelihood = " << logLikelihood  << endl;
      }
    }
  cout << endl;
}


  public:
    void classify(int argc, char* argv[]){
      if (argc == 2){
        TRAIN_ONLY_MODE = true;
      }

      vector<pair<string, string>> trainData = readFileThenConvertToOriginal(argv[1]);
      organizeAllTags(trainData);

      if (TRAIN_ONLY_MODE) {
        cout << "training data:" << endl;
        for (const auto& entry : trainData) {
          cout << "  label = " << entry.first << ", content = " << entry.second << endl;
        }
        printTrainingSummary();
        return;
      }

      cout << "trained on " << numPosts << " examples" << endl << endl;
      cout << "test data:" << endl;

      //5 training requirements now stored
      int correctPredictions = 0;
      int totalPredictions = 0;
      //cout << "test data:" << endl;
      for (const auto &testSentence : getTestData(argv[2])){
        probabilityCalc(testSentence.second, testSentence.first,
        correctPredictions, totalPredictions);
      }
      cout << "performance: " << correctPredictions << " / " 
      << totalPredictions << " posts predicted correctly" << endl;
    }


};

int main(int argc, char* argv[]){
  if (!(argc == 3 || argc == 2)){
    cout << "Usage: classifier.exe TRAIN_FILE [TEST_FILE]" << endl;
    return 1;
  }
  cout.precision(3);
  Classifier classifier;
  classifier.classify(argc, argv); 
  
}





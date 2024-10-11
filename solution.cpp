#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using std::cin, std::cout, std::string, std::vector, std::istringstream, std::unordered_map, std::pair;

struct Node {
  vector<int> to;
  string word = "";

  Node(string str) : to(26, -1), word(str) {}
};

string text;
string text1 = "Program operation reminder:\n";
string text2 = "To add new words please type '@' and then press enter\n";
string text3 = "To find a word for prefix please type '?' and then press enter\n";
string text4 = "To add new symbols to your previous prefix please type '+' and then press enter\n";
string text5 = "To clear your dictionary please type '#' and then press enter\n";
string text6 = "To finish the learning process please type '!' and then press enter\n\n";

vector<Node> bor;
unordered_map<string, int> dict_count;
unordered_map<string, bool> dict_add;

void Add(const string& str) {
  int new_count = dict_count[str];
  int old_count;
  int ind_v = 0;
  for (int i = 0; i < str.size(); ++i) {
    if (bor[ind_v].to[str[i] - 'a'] == -1) {
      bor[ind_v].to[str[i] - 'a'] = bor.size();
      bor.push_back(Node(str));
    } else {
      old_count = dict_count[bor[bor[ind_v].to[str[i] - 'a']].word];
      bool for_if = (old_count == new_count && str < bor[bor[ind_v].to[str[i] - 'a']].word);
      if (old_count < new_count || for_if) bor[bor[ind_v].to[str[i] - 'a']].word = str;
    }
    ind_v = bor[ind_v].to[str[i] - 'a'];
  }
}

pair<string, int> Find(const string& str, int index = 0) {
  int ind_v = 0;
  for (int i = 0; i < str.size(); ++i) {
    if (bor[ind_v].to[str[i] - 'a'] == -1) {
      return {"There are no words in the dictionary for this prefix\n", -1};
    }
    ind_v = bor[ind_v].to[str[i] - 'a'];
  }
  return {bor[ind_v].word, ind_v};
}



int main() {
  text = text1 + text2 + text3 + text4 + text5 + text6;

  char sign = ' ';
  string pref_for_search = "";
  int last_index_in_search = -1;
  string chars_to_add = "";
  string line, word, new_word;

  vector<string> all_words;
  vector<string> words_to_add;


  int old_index_in_bor = -1;
  bor.push_back(Node(""));

  cout << "Mrs Jake Sully, welcome to the Na'vi language learning program, enter the symbol '@' to get started\n";
  cin >> sign;

  while (sign != '%') {
    if (sign == '!') {
      cout << "I hope the training was successful. Goodbye\n";
      return 0;
    }

    else if (sign == '?') {
      cout << "Please type your prefix and then press enter: ";
      old_index_in_bor = -1;
      cin >> pref_for_search;
      auto ans = Find(pref_for_search);
      if (ans.second == -1) {
        cout << ans.first;
      } else {
        cout << "The most common word for this prefix is: " << ans.first << '\n';
      }
      old_index_in_bor = ans.second;
    }
    
    else if (sign == '+') {
      cout << "Please type what you want to add to your prefix: ";
      cin >> chars_to_add;
      pref_for_search += chars_to_add;
      auto ans = Find(pref_for_search, old_index_in_bor);
      if (ans.second == -1) {
        cout << ans.first;
      } else {
        cout << "The most common word for this prefix is: " << ans.first << '\n';
      }
      old_index_in_bor = ans.second;
    } 
    
    else if (sign == '#') {
      bor.clear();
      dict_add.clear();
      dict_count.clear();
      cout << "Your dictionary was cleaned. You can start from scratch\n";
    } 
    
    else if (sign == '@') {
      cout << "Enter words to your dictionary (complete input with char '@'): ";
      all_words.clear();
      words_to_add.clear();
      cin >> new_word;
      while (new_word != "@") {
        all_words.push_back(new_word);
        cin >> new_word;
      }
      for (const auto& w : all_words) {
        dict_count[w]++;
        if (!dict_add[w]) words_to_add.push_back(w);
        dict_add[w] = true;
      }
      for (const auto& w : words_to_add) {
        Add(w);
        dict_add[w] = false;
      }
    }

    else {
      cout << "Unforunately, the programm can not understand you, please, follow these instructions:\n"; 
    }

    cout << '\n' << text;
    cin >> sign;
  }
}
